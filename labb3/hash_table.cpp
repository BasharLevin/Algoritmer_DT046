//
// Created by Bashar Levin on 2023-05-31.
//

#include "hash_table.h"

std::vector<h_node*> hash_table(reserved_size);

void insert_into_hTable(int value){
    int sz = hash_table.size();
    int hash = hash_function(value);
    auto* new_node = new h_node{value, nullptr};
    if(hash_table[hash] == nullptr){
        hash_table[hash] = new_node;
    }
    else {
        h_node* current = hash_table[hash];
        while (current->next != nullptr){
            current = current->next;
        }
        current->next = new_node;
    }
}

int hash_function(int value){
    return value % hash_table.size();
}

int search_table(int value){
    int hash = hash_function(value);
    h_node* current = hash_table[hash];
    while(current != nullptr){
        if (current->value == value){
            return value;
        }
        current = current->next;
    }
    return - 1;
}

int vect_to_hTable(std::vector<int>& my_vec){
    for (int i : my_vec) {
        insert_into_hTable(i);
    }
    return 0;
}