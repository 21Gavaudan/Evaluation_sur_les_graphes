#include "Utiles.h"

std::stack<std::string> Dijkstra(List_Adj graph, std::string node_dep, std::string node_arr);




std::unordered_map<std::string, double> init(List_Adj graph, std::string &node_dep);

std::string find_min(std::vector<std::string> &unvisited, std::unordered_map<std::string, double> &dist);

void maj_dist(std::string &node1, std::string &node2, std::unordered_map<std::string, std::string> &predecessor, std::unordered_map<std::string, double> &dist, List_Adj graph);

double find_edge_value(std::string node1, std::string node2, List_Adj graph);

void print_pile(std::stack<std::string> pile);