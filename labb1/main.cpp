#include <iostream>
#include "reader.h"
bool is_graph_connected(const std::vector<int> &visited) {
    for (int i = 0; i < visited.size(); i++) {
        if (visited[i] == NOT_VISITED) {
            return false;
        }
    }
    return true;
}

void print_disconnected_nodes(const std::vector<int>& visited) {
    for (int i = 0; i < visited.size(); i++) {
        if (visited[i] == NOT_VISITED) {
            std::cout << "Node " << i << " is not visited." << std::endl;
        }
    }
}


int main() {
  // Read file and create edge list from it
 auto file_data = parse_file("../edges.txt");


  // DFS
  std::cout<<"###############################"<<std::endl;
  std::cout << "DFS:" << std::endl;
  auto visited_graph_dfs = dfs(0, file_data);

  if (is_graph_connected(visited_graph_dfs)) {
      std::cout << "The graph is connected." << std::endl;
  } else {
      std::cout << "The graph is not connected." << std::endl;
      print_disconnected_nodes(visited_graph_dfs);
  }

  // BFS

  std::cout<<"###############################"<<std::endl;
  std::cout << "BFS:" << std::endl;
  auto visited_graph_bfs = bfs(0, file_data);
  // Check if graph is connected
  if (is_graph_connected(visited_graph_bfs)) {
      std::cout << "The graph is connected." << std::endl;
  } else {
      std::cout << "The Graph is not connected." << std::endl;
      print_disconnected_nodes(visited_graph_bfs);
  }

  // Dijkstra's algorithm
  std::cout<<"###############################"<<std::endl;
  std::cout << "Dijkstra's algorithm:" << std::endl;
  auto start_n = 24;
  auto end_n = 37;
  auto distance = dijkstras(start_n, end_n, file_data);
  std::cout << "Från Nackstavägen till Förrådet" << std::endl;
  std::cout << "Avståndet från " << start_n << " till " << end_n << ": " << distance << std::endl;
  auto path = dijkstras_path(start_n, end_n, file_data);
  std::cout << "Path: ";
  for (int i = 0; i < path.size(); i++) {
      std::cout << path[i] << " ";
  }
  std::cout << std::endl;

  auto L319 = 46;
  auto D025 = 47;
  auto distance2 = dijkstras(L319, D025, file_data);
  std::cout << "Avståndet från " << L319 << " till " << D025 << ": " << distance2 << std::endl;

  auto bite_line = 19;
  auto uni = 20;
  auto distance3 = dijkstras(bite_line, uni, file_data);
  std::cout << "Distance from " << uni << " to " << bite_line << ": " << distance3 << std::endl;



    return 0;
}