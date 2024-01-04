#include <iostream>
#include "gen_data.h"
#include "lin_search.h"
#include "bin_search.h"
#include "bin_tree.h"
#include "hash_table.h"
#include <chrono>
#include <numeric>
#include <iomanip>
#include <fstream>
void measure_search_perf2(const std::string &filename, int (*search_func)(t_node*, int),
                          std::vector<std::vector<int>> &data_to_search_vect);

void measure_search_perf3(const std::string &filename, int (*hash_search)(int),
                          std::vector<std::vector<int>> &data_to_search_vect);


void measure_search_perf1(const std::string &filename, int (*search_func)(std::vector<int> &, int),
                          std::vector<std::vector<int>> &data_to_search_vect);

double calculate_stdev(std::vector<double> data, double mean);



int main() {

    const std::string prfx = "../results/";
    std::vector<int> samples = {1'000, 1'500, 2'000, 2'500, 3'000, 3'500, 4'000, 4'500, 5'000, 10'000, 12'000, 14'000, 16'000,
                                18'000, 20'000, 30'000, 35'000, 40'000, 45'000, 50'000};
    std::vector<std::vector<int>> data(samples.size());
    for (auto i = 0; i < samples.size(); i++) {
        gen_random(samples[i], data[i]);
    }
    //measure_search_perf1(prfx + "bin_search.txt", bin_search, data);
    measure_search_perf1(prfx + "lin_search.txt", linear_search, data);
    measure_search_perf2(prfx + "binary_tree_serach.txt", bi_search_tree, data );
    measure_search_perf3(prfx + "hash_table_search.txt", search_table, data);
    /* int n = 30; // Övre gräns för primtal
     std::vector<int> primeNumbers;
     gen_prime(n, primeNumbers);
     std::cout << "Primtalen upp till " << n << " är: ";
     for (int prime : primeNumbers) {
         std::cout << prime << " ";
     }
     int target = 7;
     int index = bin_search(primeNumbers,target);
     if (index != -1) {
         std::cout << "Målet hittades på index " << index << std::endl;
     } else {
         std::cout << "Målet hittades inte i vektorn." << std::endl;
     }
    /* std::vector<int> random;
     gen_prime(n, primeNumbers);

     std::cout << "Primtalen upp till " << n << " är: ";
     for (int prime : primeNumbers) {
         std::cout << prime << " ";
     }
     std::cout << std::endl;
     gen_random(n,random);
     for (int ramn : random) {
         std::cout << ramn << " ";
     }*/


    return 0;
}
void measure_search_perf2(const std::string &filename, int (*search_func)(t_node*, int),
                          std::vector<std::vector<int>> &data_to_search_vect){
    std::ofstream out_file(filename);
    std::cout << filename << std::endl;
    out_file << std::left << std::setw(15) << "N" << std::setw(15) << "T[ms]" << std::setw(15) << "Stdev[ms]"
             << std::setw(15) << "Samples" << "\n";
    const int samp_num = 50;

    std::vector<double> stdevs;
    std::vector<double> means;
    for (auto vect: data_to_search_vect) {
        std::vector<double> times;
        std::vector<int> primes;
        gen_prime(vect.size(), primes);
        //build_tree(primes);

        t_node *root = nullptr;
        auto tree1 = build_bala_btree(primes);
        //build_tree2(primes);

        for (auto it = 0; it < samp_num; it++) {

            const int num_searches = 1000;
            std::vector<int> results(num_searches);

            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < num_searches; i++) {
                results[i] = search_func(tree1, vect[i]);
            }
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> elapsed = end - start;

            for (int i = 0; i < num_searches; i++) {
                times.push_back(elapsed.count());
            }
            double mean_per_val = elapsed.count() / results.size();
            times.push_back(mean_per_val);

        }
        double mean = std::accumulate(times.begin(), times.end(), 0.0) / times.size();
        double stdev = calculate_stdev(times, mean);
        out_file << std::left << std::setw(15) << vect.size() << std::setw(15) << mean << std::setw(15) << stdev
                 << std::setw(15) << samp_num /*times.size()*/ << std::endl;
        std::cout << "N: " << vect.size() << " mean: " << mean << " stdev: " << stdev << std::endl;

    }
}


void measure_search_perf3(const std::string &filename, int (*hash_search)(int),
                          std::vector<std::vector<int>> &data_to_search_vect) {
    std::ofstream out_file(filename);
    std::cout << filename << std::endl;
    out_file << std::left << std::setw(15) << "N" << std::setw(15) << "T[ms]" << std::setw(15) << "Stdev[ms]"
             << std::setw(15) << "Samples" << "\n";
    const int samp_num = 20;

    std::vector<double> stdevs;
    std::vector<double> means;
    for (auto vect: data_to_search_vect) {
        std::vector<double> times;
        std::vector<int> primes;
        gen_prime(vect.size(), primes);
        //build_tree(primes);


        vect_to_hTable(primes);
        //build_tree2(primes);

        for (auto it = 0; it < samp_num; it++) {

            const int num_searches = 1000;
            std::vector<int> results(num_searches);

            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < num_searches; i++) {
                results[i] = hash_search(vect[i]);
            }
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> elapsed = end - start;

            for (int i = 0; i < num_searches; i++) {
                times.push_back(elapsed.count());
            }
            double mean_per_val = elapsed.count() / results.size();
            times.push_back(mean_per_val);

        }
        double mean = std::accumulate(times.begin(), times.end(), 0.0) / times.size();
        double stdev = calculate_stdev(times, mean);
        out_file << std::left << std::setw(15) << vect.size() << std::setw(15) << mean << std::setw(15) << stdev
                 << std::setw(15) << samp_num /*times.size()*/ << std::endl;
        std::cout << "N: " << vect.size() << " mean: " << mean << " stdev: " << stdev << std::endl;

    }

}


void measure_search_perf1(const std::string &filename, int (*search_func)(std::vector<int> &, int),
                          std::vector<std::vector<int>> &data_to_search_vect) {
    std::ofstream out_file(filename);
    std::cout << filename << std::endl;
    out_file << std::left << std::setw(15) << "N" << std::setw(15) << "T[ms]" << std::setw(15) << "Stdev[ms]"
             << std::setw(15) << "Samples" << "\n";
    const int samp_num = 50;

    std::vector<double> stdevs;
    std::vector<double> means;
    for (auto vect: data_to_search_vect) {
        std::vector<double> times;
        std::vector<int> primes;
        gen_prime(vect.size(), primes);
        for (auto it = 0; it < samp_num; it++) {

            const int num_searches = 1000;
            //std::vector<int> search_values(num_searches);
            std::vector<int> results(num_searches);

/*            // Generate random search values
            for (auto &search_val: search_values) {
                search_val = vect[rand() % vect.size()];
            }*/

            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < num_searches; i++) {
                /*if (search_func(primes, vect[i]) != -1) {
                    results.push_back(search_func(primes, vect[i]));
                }*/
                results[i] = search_func(primes, vect[i]);

            }
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> elapsed = end - start;


            // Store the elapsed time of each search
            for (int i = 0; i < num_searches; i++) {
                times.push_back(elapsed.count());
            }
            double mean_per_val = elapsed.count() / results.size();
            times.push_back(mean_per_val);

        }
        double mean = std::accumulate(times.begin(), times.end(), 0.0) / times.size();
        double stdev = calculate_stdev(times, mean);
        out_file << std::left << std::setw(15) << vect.size() << std::setw(15) << mean << std::setw(15) << stdev
                 << std::setw(15) << samp_num /*times.size()*/ << std::endl;
        std::cout << "N: " << vect.size() << " mean: " << mean << " stdev: " << stdev << std::endl;

    }
}



double calculate_stdev(std::vector<double> data, double mean) {
    double sum = 0;
    for (auto i = 0; i < data.size(); i++) {
        sum += pow(data[i] - mean, 2);
    }
    return sqrt(sum / data.size());
}