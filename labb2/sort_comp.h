//
// Created by Bashar Levin on 2023-05-15.
//

#ifndef LABB2_SORT_COMP_H
#define LABB2_SORT_COMP_H
#include <iostream>
#include <vector>

void insertion_sort(std::vector<int>& my_vec);
void selection_sort(std::vector<int>& my_vec);
int partition(std::vector<int>& my_vec, int low, int high);
int partition_m3(std::vector<int>& my_vec, int low, int high, int pivot);
int med_of3(int a, int b, int c);
void quick_sort(std::vector<int>& my_vec, int left, int right);
void quick_sort_m3(std::vector<int>& my_vec, int low, int high);
void r_pivot_quick_sort(std::vector<int> &my_vec);
void med3_quick_sort(std::vector<int> &vect_in);
void std_sort(std::vector<int> &vect_in);
#endif //LABB2_SORT_COMP_H
