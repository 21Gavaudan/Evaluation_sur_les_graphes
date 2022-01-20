#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <stack>
#include <queue>
#include "edge.h"


class List_Adj
{
    std::unordered_map<std::string, std::vector<edge> > list_adj;

    public:
    List_Adj(std::unordered_map<std::string, std::vector<edge> > list_adj) : list_adj(list_adj){}

    void print();

    int size() const
    {
        return list_adj.size();
    }
    
    std::unordered_map<std::string, std::vector<edge> > get_Dict_List() const{
        return list_adj;
    }

    std::vector<std::string> get_nodes();
    
    std::vector<edge> at(const std::string &s) const
    {
        return list_adj.at(s);
    }

    void indepth_rec(std::string node, std::vector<std::string> &visited); //Question 3
    void indepth_ite(std::string node); //Question 4
    void inbreadth(std::string node, int level); //Question 5
};

std::unordered_map<std::string, int> Index_of_the_keys(std::vector<std::string> Nodes);
//Cette fonction prend en parametre la liste des sommets et donne le dictionnaire qui au nom d'un sommet associe un numéro, son indice