#include <iostream>
#include <fstream>
#include <chrono>
#include <numeric>
#include <functional>
#include"sort_comp.h"
#include "generate_numbers.h"
#include "timeCalc.h"

const std::string deric = "../Test_results/";
std::string get_title(const std::string &txt_file);
void gen_and_sort(const std::string &filename, void (*sorting_func)(std::vector<int> &),void (*gen_func)(int, std::vector<int> &));

int main() {
    gen_and_sort(deric + "inser_sort_rand.txt", insertion_sort, gen_random);
    gen_and_sort(deric + "inser_sort_const.txt", insertion_sort, gen_constant);
    gen_and_sort(deric + "inser_sort_increas.txt", insertion_sort, gen_increasing);
    gen_and_sort(deric + "inser_sort_decre.txt", insertion_sort, gen_decreasing);

    gen_and_sort(deric + "sele_sort_rand.txt", selection_sort, gen_random);
    gen_and_sort(deric + "sele_sort_const.txt", selection_sort, gen_constant);
    gen_and_sort(deric + "sele_sort_increas.txt", selection_sort, gen_increasing);
    gen_and_sort(deric + "sele_sort_decre.txt", selection_sort, gen_decreasing);

    gen_and_sort(deric + "quick_sort_rand.txt", r_pivot_quick_sort, gen_random);
    gen_and_sort(deric + "quick_sort_const.txt", r_pivot_quick_sort, gen_constant);
    gen_and_sort(deric + "quick_sort_increas.txt", r_pivot_quick_sort, gen_increasing);
    gen_and_sort(deric + "quick_sort_decre.txt", r_pivot_quick_sort, gen_decreasing);

    gen_and_sort(deric + "quick_sort_m3_rand.txt", med3_quick_sort, gen_random);
    gen_and_sort(deric + "quick_sort_m3_const.txt", med3_quick_sort, gen_constant);
    gen_and_sort(deric + "quick_sort_m3_increas.txt", med3_quick_sort, gen_increasing);
    gen_and_sort(deric + "quick_sort_m3_decre.txt", med3_quick_sort, gen_decreasing);

    gen_and_sort(deric + "std_sort_rand.txt", std_sort, gen_random);
    gen_and_sort(deric + "std_sort_const.txt", std_sort, gen_constant);
    gen_and_sort(deric + "std_sort_increas.txt", std_sort, gen_increasing);
    gen_and_sort(deric + "std_sort_decre.txt", std_sort, gen_decreasing);


    return 0;
}


std::string get_title(const std::string &txt_file){
    return txt_file.substr(16, txt_file.size()-20);
}

void gen_and_sort(const std::string &filename, void (*sorting_func)(std::vector<int> &),void (*gen_func)(int, std::vector<int> &)){
    std::ofstream out_file(filename);
    std::string title = get_title(filename);
    out_file <<"sorting preformence - "<<title<<"\n";
    out_file <<std::left <<std::setw(15) << "N" <<std::setw(15) <<"T[ms]"<<std::setw(15)<<"Stdev[ms]"<<std::setw(15) <<"Samples"<<"\n";
    const int samp_num = 10;
    std::vector<int> samples_v{2000, 3000, 4000, 5000, 6000, 7000, 8000, 12'000, 14'000, 16'000};
    for (auto& n : samples_v){
        std::vector<double> times(samp_num);

        for (int j = 0; j < samp_num; j++){
            std::vector<int> v;
            gen_func(n,v);

            auto start_time = std::chrono::high_resolution_clock::now();
            sorting_func(v);
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration_ms = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
            times[j] = duration_ms / static_cast<double>(1000);
        }
        double mean_time_ms = std::accumulate(times.begin(), times.end(), 0.0) / times.size();
        double stdev_ms =  standardavvikelse(times);

        out_file << std::left << std::setw(15) << n << std::setw(15) << mean_time_ms << std::setw(15)
                 << stdev_ms << std::setw(15) << times.size() << "\n";

        std::cout << "n: " << n << ", mean time: " << mean_time_ms << ", stdev: " << stdev_ms << "\n";

        out_file.flush();
    }
    out_file.close();

}
