#include "List_Representation.h"

std::unordered_map<std::string, int> Index_of_the_keys(std::vector<std::string> Nodes)
{
    //Cette fonction prend en parametre la liste des sommets et donne le dictionnaire qui au nom d'un sommet associe un numéro, son indice
    std::unordered_map<std::string, int> Dict_index;
    for (int i = 0; i < Nodes.size(); i++)
    {
        Dict_index.insert({Nodes[i], i});
    }
    return Dict_index;
}

void List_Adj::print()
{
    for (std::unordered_map<std::string, std::vector<edge> >::iterator it1 = list_adj.begin(); it1 != list_adj.end(); it1++)
    {
        std::cout << it1->first << ": " << std::endl;
        for (std::vector<edge>::iterator it2 = it1->second.begin(); it2 != it1->second.end(); it2++)
        {
            it2->print();
            
        }
    }
}

std::vector<std::string> List_Adj::get_nodes(){
    std::vector<std::string> nodes;
    for( auto& it : this->get_Dict_List()){
        nodes.push_back(it.first);
    }
    return nodes;
}

void List_Adj::indepth_rec(std::string node, std::vector<std::string> &visited){
    visited.push_back(node);
    std::cout << node << " has been visited" << std::endl;
    for(auto& edge : this->at(node)){
        if (find(visited.begin(), visited.end(), edge.next()) == visited.end()){
            edge.print();
            indepth_rec(edge.next(), visited);
        }
    }
}

void List_Adj::indepth_ite(std::string node){
    
    std::unordered_map<std::string, int> node_state; //On initialise l'état de tous les sommets à 0 = pas visité
    std::stack<std::string> pile;                    //On initialise la pile: on met tous les sommets du graph dedans et on met au top le sommet node
    
    for (auto& it : this->get_Dict_List())
    {
        node_state.insert({it.first, 0});
        if(it.first!=node){
            pile.push(it.first);
        }
    }
    pile.push(node);
    node_state.at(node) = 1;
    std::cout << node << " has been visited " << std::endl;

    while (!(pile.empty()))
    {
        bool flag = false;
        for (auto &edge : this->at(pile.top()))
        {
            if( node_state.at(edge.next()) == 0 ){
                flag = true;
                node_state.at(edge.next()) = 1; //1 signifie que l'on a visité le sommet
                edge.print();
                std::cout << edge.next() << " has been visited " << std::endl;
                pile.push(edge.next());
                break;
            }
        }
        if( !flag){
            node_state.at(pile.top()) = 2; //2 signifie que le sommet n'a plus de sommet adjacent non visité
            pile.pop();
        }
    }
}

void List_Adj::inbreadth(std::string node, int level_max){
    std::unordered_map<std::string, int> node_state; //On initialise l'état de tous les sommets à 0 = pas visité
    for (auto &it : this->get_Dict_List())
    {
        node_state.insert({it.first, 0});
    }

    std::queue<std::string> file;
    file.push(node);
    node_state.at(node) = 1;

    int current_level = 0;
    while (!(file.empty()))
    {
        for( auto& edge : this->at(file.front())){
            if( node_state.at(edge.next())==0){
                file.push(edge.next());
                node_state.at(edge.next()) = 1;
                edge.print();
                std::cout << edge.next() << " has been visited " << std::endl;
            }
        }
        node_state.at(file.front()) = 2;
        file.pop();
        current_level += 1;
        if (level_max != 0 && current_level == level_max)
        {
            break;
        }
    }
}