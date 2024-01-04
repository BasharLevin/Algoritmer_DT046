//
// Created by Bashar Levin on 2023-05-30.
//

#ifndef LABB3_BIN_TREE_H
#define LABB3_BIN_TREE_H
#include <vector>

struct t_node{
    int value;
    t_node* left;
    t_node* right;
};
void insert(t_node*& node, int value);
void delete_tree(t_node* node);
t_node* build_balanced_btree(const std::vector<int>& my_vec, int start, int end );
t_node* build_bala_btree(std::vector<int>&my_vec);
int bi_search_tree(t_node* root, int target);
#endif //LABB3_BIN_TREE_H
