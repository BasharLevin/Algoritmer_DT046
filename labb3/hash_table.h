//
// Created by Bashar Levin on 2023-05-31.
//

#ifndef LABB3_HASH_TABLE_H
#define LABB3_HASH_TABLE_H
#include <vector>

const int reserved_size = 100'000;

struct h_node{
    int value;
    h_node* next;
};

void insert_into_hTable(int value);

int hash_function(int value);

int search_table(int value);

int vect_to_hTable(std::vector<int>& my_vec);
#endif //LABB3_HASH_TABLE_H
