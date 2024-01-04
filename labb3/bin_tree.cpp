//
// Created by Bashar Levin on 2023-05-30.
//

#include "bin_tree.h"

void insert(t_node*& node, int value){
    if (node == nullptr){
        node = new t_node;
        node->value = value;
        node->right = nullptr;
        node->left = nullptr;
        return;
    }
    if(value < node->value){
        insert(node->left, value);
    }
    else if (value > node->value)
        insert(node->right, value);
}



void delete_tree(t_node* node){
    if (node == nullptr){
        return;
    }
    delete_tree(node->left);
    delete_tree(node->right);
    delete node;
}


int bi_search_tree(t_node* root, int target){
    if (root == nullptr){
        return -1;
    }
    if (root->value == target){
        return root->value;
    }
    else if (target < root->value){
        return bi_search_tree(root->left, target);
    }
    else{
        return bi_search_tree(root->right, target);
    }
}


t_node* build_balanced_btree(const std::vector<int>& my_vec, int start, int end ){
    if(start > end){
        return nullptr;
    }
    int mid = (start + end) / 2;
    t_node* my_node = new t_node;
    my_node->value = mid;
    my_node->right = build_balanced_btree(my_vec, mid + 1 , end);
    my_node->left = build_balanced_btree(my_vec, start, mid - 1);
    return my_node;
}


t_node* build_bala_btree(std::vector<int>&my_vec){
    return build_balanced_btree(my_vec, 0,  my_vec.size() - 1 );
}