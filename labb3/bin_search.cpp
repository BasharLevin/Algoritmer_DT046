//
// Created by Bashar Levin on 2023-05-30.
//

#include "bin_search.h"
int bin_search(std::vector<int>&my_vec, int target){
    int left = 0;
    int right = my_vec.size() - 1;

    while (left <= right){
        int mid = left + (right - left) / 2;

        if(my_vec[mid] == target){
            return mid;
        }
        else if (my_vec[mid] < target){
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return - 1;

}