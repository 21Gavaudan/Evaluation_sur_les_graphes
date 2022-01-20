#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <stack>
#include <queue>
#include "edge.h"


class Matrix_Adj
{
    std::vector<double> graph;
    std::vector<std::string> Nodes;

public:
    Matrix_Adj(std::vector<double> graph, std::vector<std::string> Nodes): graph(graph), Nodes(Nodes){}

    void print() const;

    std::vector<edge> get_edges(std::string& node); //renvoie les sommets adjacents à node
    

    std::vector<std::string> getNodes() const{
        return Nodes;
    }
    std::vector<double> getGraph() const{
        return graph;
    }

    double at(int i, int j) const{
        return graph[i*Nodes.size()+j];
    }

    void indepth_rec(std::string node, std::vector<std::string>& visited); //Question 3
    void indepth_ite(std::string node); //Question 4
    void inbreadth(std::string node, int level_max); //Question 5
};

std::unordered_map<int, std::string> Keys_of_the_index(std::vector<std::string> Nodes);
//Cette fonction prend en parametre la liste des sommets et donne le dictionnaire qui a l'indice d'un sommet associe son nom