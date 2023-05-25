//
// Created by Bashar Levin on 2023-05-13.
//

#ifndef LAB1_READER_H
#define LAB1_READER_H
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>

using node_id_t = int;
using weight_t = double;
using meta_t = std::map<node_id_t,std::string>;
const int NOT_VISITED = 0;
const int VISITED = 1;
const int NOT_CONNECTED = -1;

struct edge{
    node_id_t n1;
    node_id_t n2;
    weight_t weight;
    std::string descrip;
};

struct node{
    node_id_t n1 = 0;
    node_id_t prev = 0;
    double weight = 0;
    bool visited = false;
};

using edge_list_t = std::vector<edge>;
using adjacency_list_t = std::pair<meta_t, edge_list_t>;
using node_pair_t = std::pair<node_id_t, node_id_t>;
adjacency_list_t parse_file(std::string filename);
std::vector<int> dfs(int node, adjacency_list_t &adj_list);
std::vector<int> bfs(int node, const adjacency_list_t &adj_list);
double dijkstras(int start, int end, const adjacency_list_t &adj_list);
std::vector<int> dijkstras_path(int start, int end, const adjacency_list_t& adj_list);


#endif //LAB1_READER_H
