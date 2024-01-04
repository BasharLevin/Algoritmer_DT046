//
// Created by Bashar Levin on 2023-05-30.
//
#include <vector>
#include "lin_search.h"

int linear_search(std::vector<int>&my_vec, int target){
    for (int i = 0; i < my_vec.size(); i++) {
        if(my_vec[i] == target)
            return i;
    }
    return -1;
}


