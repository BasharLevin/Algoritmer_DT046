//
// Created by Bashar Levin on 2023-05-30.
//

#include "gen_data.h"
#include <random>
void gen_prime(int n, std::vector<int>& primes){
    std::vector<bool>isPrime(n + 1, true);

    for(int p = 2; p * p <= n; p++){
        if(isPrime[p]){
            for (int i = p * p; i <= n; i += p){
                isPrime[i] = false;
            }
        }
    }
    for (int p = 2; p <= n; p++){
        if (isPrime[p]){
            primes.push_back(p);
        }
    }
}

void gen_random(int n, std::vector<int>&my_vec){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, n);
    my_vec.resize(n);
    for (auto i = 0; i < n; i++) {
        my_vec[i] = dis(gen);
    }
}