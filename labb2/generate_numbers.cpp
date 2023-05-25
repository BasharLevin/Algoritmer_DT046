//
// Created by Bashar Levin on 2023-05-15.
//

#include "generate_numbers.h"
void gen_random(int n, std::vector<int>&my_vec){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, n);
    for (auto i = 0; i < n; i++) {
        my_vec.push_back(dis(gen));
    }
}
void gen_decreasing(int n, std::vector<int> &vect_out) {
    for (auto i = n; i > 0; i--) {
        vect_out.push_back(i);
    }
}

void gen_increasing(int t, std::vector<int>&my_vec){
    for (auto i = 0; i < t; i++) {
        my_vec.push_back(i);
    }
}
void gen_constant(int t, std::vector<int>&my_vec){
    for (auto i = 0; i < t; i++) {
        my_vec.push_back(0);
    }
}
