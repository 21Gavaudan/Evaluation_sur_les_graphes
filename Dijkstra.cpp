#include "Dijkstra.h"

std::stack<std::string> Dijkstra(List_Adj graph, std::string node_dep, std::string node_arr)
{
    std::unordered_map<std::string, double> dist_to_dep = init(graph, node_dep);
    std::vector<std::string> unvisited = graph.get_nodes();
    std::unordered_map<std::string, std::string> predecessor;

    while (unvisited.size() != 0)
    {
        std::string node1 = find_min(unvisited, dist_to_dep);
        std::unordered_map<std::string, int> index = Index_of_the_keys(unvisited);
        unvisited.erase(unvisited.begin() + index[node1]);
        for( auto& edge : graph.at(node1)){
            std::string node2 = edge.next();
            maj_dist(node1, node2, predecessor, dist_to_dep, graph);
        }
    }

    //Puis on crée le chemin à partir de dist_to_dep et predecessor

    std::stack<std::string> chemin;
    std::string node_current = node_arr;
    while(node_current != node_dep){
        chemin.push(node_current);
        node_current = predecessor.at(node_current);
    }
    chemin.push(node_dep);
    print_pile(chemin);

    return chemin;
}

std::unordered_map<std::string, double> init(List_Adj graph, std::string& node_dep){
    std::unordered_map<std::string, double> dist;
    for( auto& it : graph.get_Dict_List()){
        dist.insert({it.first, std::numeric_limits<double>::infinity()});
    }
    dist.at(node_dep) = 0;
    return dist;
}

std::string find_min(std::vector<std::string>& unvisited, std::unordered_map<std::string, double>& dist)
{
    double mini = std::numeric_limits<double>::infinity();
    std::string node_min = "-1";
    for( auto& node : unvisited){
        if( dist.at(node) < mini){
            mini = dist.at(node);
            node_min = node;
        }
    }
    return node_min;
}

void maj_dist(std::string &node1, std::string &node2, std::unordered_map<std::string, std::string> &predecessor, std::unordered_map<std::string, double>& dist, List_Adj graph)
{
    
    if( dist.at(node2) > dist.at(node1) + find_edge_value(node1, node2, graph)){
        dist.at(node2) = dist.at(node1) + find_edge_value(node1, node2, graph);
        predecessor[node2] = node1;
    }
}

double find_edge_value(std::string node1, std::string node2, List_Adj graph)
{
    std::vector<edge> edge_from_1 = graph.at(node1);
    for( auto& edge : edge_from_1){
        if(edge.next() == node2){
            return edge.value();
        }
    }
}

void print_pile(std::stack<std::string> pile){
    int s = pile.size();
    while( pile.size() != 1){
        std::cout << pile.top() << " -> ";
        pile.pop();
    }
    std::cout << pile.top() << std::endl;
}
