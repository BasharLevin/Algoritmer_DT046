//
// Created by Bashar Levin on 2023-05-13.
//
#include "reader.h"
#include <set>
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>
#include <unordered_set>

enum token{
    COMMENT, META, EDGE, END_OF_FILE
};

token get_line_type(std::istream& is){
    switch(is.peek()){
        case std::istream::traits_type::eof():      return END_OF_FILE;
        case '#' :                                  return COMMENT;
        case 'M' :                                  return META;
    };
    return EDGE;
}
meta_t meta;

edge read_edge(std::istream& is){
    edge e;
    is >> e.n1 >> e.n2 >> e.weight;
    std::getline(is, e.descrip);
    return e;
}

void read_meta(std::istream& is){
    char disc;
    node_id_t vert_id;
    std::string name;
    is >> disc >> vert_id;
    std::getline(is, name);
    meta[vert_id] = name;
}

adjacency_list_t parse_file(std::string filename){
    std::ifstream in(filename);
    token l;
    edge_list_t edge_list;
    while((l = get_line_type(in)) != END_OF_FILE){
        edge e;
        switch(l){
            case token::EDGE:
                e = read_edge(in);
                edge_list.push_back(e);
                break;
            case token::META:
                read_meta(in);
                break;
            default:
                std::string comment;
                std::getline(in, comment);
        }
    }
    return adjacency_list_t{meta, edge_list};
}
//O(N+E)
std::vector<int> dfs(int node, adjacency_list_t& adj_list) {
    std::vector<int> handled_nodes_v(adj_list.first.size(), NOT_VISITED);
    std::stack<int> nodes_s;
    nodes_s.push(node);
    while (!nodes_s.empty()) {
        int current = nodes_s.top();
        nodes_s.pop();
        if (handled_nodes_v[current] == NOT_VISITED) {
            handled_nodes_v[current] = VISITED;
            for (const auto& edge : adj_list.second) {
                int neighbor = edge.n2;
                double weight = edge.weight;
                if (edge.n1 == current && weight != NOT_CONNECTED) {
                    nodes_s.push(neighbor);
                }
            }
        }
    }
    return handled_nodes_v;
}


const double INF = std::numeric_limits<double>::infinity();
double dijkstras(int start, int end, const adjacency_list_t& adj_list) {
    std::vector<double> dist(adj_list.first.size(), INF);
    std::unordered_set<int> handledNodes;
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> paths_pq;
    dist[start] = 0;
    paths_pq.push({0, start});
    while (!paths_pq.empty()) {
        const int curr = paths_pq.top().second;
        paths_pq.pop();
        if (handledNodes.count(curr)) continue;
        handledNodes.insert(curr);
        if (curr == end){
            return dist[end];
        }
        for (const auto& edge : adj_list.second) {
            if (edge.n1 != curr) continue;

            const double new_dist = dist[curr] + edge.weight;
            if (dist[edge.n2] <= new_dist) continue;

            dist[edge.n2] = new_dist;
            paths_pq.push({dist[edge.n2], edge.n2});
        }
    }

    return NOT_CONNECTED;
}

std::vector<int> dijkstras_path(int start, int end, const adjacency_list_t &adj_list) {
    std::vector<double> dist(adj_list.first.size(), INF);
    std::unordered_set<int> visited;

    std::vector<int> prev(adj_list.first.size(), -1);
    prev[start] = start;
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> paths_pq;
    dist[start] = 0;
    paths_pq.push({0, start});
    while (!paths_pq.empty()) {
        const int curr = paths_pq.top().second;
        paths_pq.pop();

        if (visited.count(curr)) continue;
        visited.insert(curr);
        if (curr == end) {
            std::vector<int> path;
            int node = end;
            while (node != start) {
                path.push_back(node);
                node = prev[node];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }
        for (const auto& edge : adj_list.second) {
            if (edge.n1 != curr) continue;

            const double new_dist = dist[curr] + edge.weight;
            if (dist[edge.n2] <= new_dist) continue;

            dist[edge.n2] = new_dist;
            prev[edge.n2] = curr;
            paths_pq.push({dist[edge.n2], edge.n2});
        }
    }

    return {};
}
//O(n*log(n))
std::vector<int> bfs(int node, const adjacency_list_t &adj_list) {
    std::vector<int> handled_nodes_v(adj_list.first.size(), NOT_VISITED);
    std::queue<int> nodes_q;
    nodes_q.push(node);
    while (!nodes_q.empty()) {
        int current = nodes_q.front();
        nodes_q.pop();
        if (handled_nodes_v[current] == NOT_VISITED) {
            handled_nodes_v[current] = VISITED;
            for (const auto &edge: adj_list.second) {
                int neighbor = edge.n2;
                double weight = edge.weight;
                if (edge.n1 == current && weight != NOT_CONNECTED) {
                    nodes_q.push(neighbor);
                }
            }
        }
    }
    return handled_nodes_v;
}