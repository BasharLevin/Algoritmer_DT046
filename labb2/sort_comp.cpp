//
// Created by Bashar Levin on 2023-05-15.
//

#include "sort_comp.h"
void insertion_sort(std::vector<int>& vec){
    for (int curr_index = 1; curr_index < vec.size(); curr_index++) {
        int curr_val = vec[curr_index];
        int prev_idx = curr_index - 1;
        while (prev_idx >= 0 && vec[prev_idx] > curr_val) {
            vec[prev_idx + 1] = vec[prev_idx];
            prev_idx--;
        }
        vec[prev_idx + 1] = curr_val;
    }
}

void selection_sort(std::vector<int>& vec){
    for (int curr_index = 0; curr_index < vec.size() - 1; curr_index++) {
        int min_index = curr_index;
        for (int j = curr_index + 1; j < vec.size(); j++)
            if (vec[j] < vec[min_index])
                min_index = j;
        std::swap(vec[curr_index], vec[min_index]);
    }
}
int partition(std::vector<int>&my_vec, int low, int high){
    int pivot = my_vec[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++){
        if (my_vec[j] < pivot ){
            i++;
            std::swap(my_vec[i], my_vec[j]);
        }
    }
    std::swap(my_vec[i + 1], my_vec[high]);
    return i + 1;
}


void quick_sort(std::vector<int>& my_vec, int left, int right){
    if (left < right) {
        int pivot_idx = partition(my_vec, left, right);

        quick_sort(my_vec, left, pivot_idx - 1);
        quick_sort(my_vec, pivot_idx + 1, right);
    }
}

int partition_m3(std::vector<int>& my_vec, int low, int high, int pivot){
    int i = low - 1, j = high + 1;
    while (true) {
        do {
            i++;
        } while (my_vec[i] < pivot);
        do {
            j--;
        } while (my_vec[j] > pivot);
        if (i >= j) {
            return j;
        }
        std::swap(my_vec[i], my_vec[j]);
    }
}

int med_of3(int a, int b, int c) {
    if (a <= b && b <= c) return b;
    if (c <= b && b <= a) {
        std::swap(a, c);
        return b;
    }
    if (b <= a && a <= c) {
        std::swap(a, b);
        return b;
    }
    if (c <= a && a <= b) {
        std::swap(a, c);
        std::swap(b, c);
        return b;
    }
    std::swap(a, b);
    if (c <= b) {
        std::swap(b, c);
        if (a <= b) {
            return b;
        }
        std::swap(a, b);
        return b;
    }
    return b;
}

void quick_sort_m3(std::vector<int>&my_vec, int low, int high){
    if (low < high) {
        int mid = (low + high) / 2;
        int pivot = med_of3(my_vec[low], my_vec[mid], my_vec[high]);

        int piv = partition_m3(my_vec, low, high, pivot);

        quick_sort_m3(my_vec, low, piv);
        quick_sort_m3(my_vec, piv + 1, high);
    }
}


void r_pivot_quick_sort(std::vector<int> &my_vec) {
    quick_sort(my_vec, 0, my_vec.size() - 1);
}
void med3_quick_sort(std::vector<int> &my_vec) {
    quick_sort_m3(my_vec, 0, my_vec.size() - 1);
}
void std_sort(std::vector<int> &my_vec) {
    std::sort(my_vec.begin(),my_vec.end());
}