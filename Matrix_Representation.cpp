#include "Matrix_Representation.h"

std::unordered_map<int, std::string> Keys_of_the_index(std::vector<std::string> Nodes)
{
    //Cette fonction prend en parametre la liste des sommets et donne le dictionnaire qui a l'indice d'un sommet associe son nom
    std::unordered_map<int, std::string> Dict_index;
    for (int i = 0; i < Nodes.size(); i++)
    {
        Dict_index.insert({i, Nodes[i]});
    }
    return Dict_index;
}

std::vector<edge> Matrix_Adj::get_edges(std::string& node){
    std::vector<edge> edges;
    std::unordered_map<int, std::string> Dict = Keys_of_the_index(Nodes);
    for (int i = 0; i < Nodes.size(); i++)
    {
        if( Dict.at(i) == node){
            for (int j = 0; j < Nodes.size(); j++){
                if(graph.at(i*Nodes.size() + j) != 0){
                    edge edge(Dict.at(i), Dict.at(j), graph.at(i*Nodes.size() + j));
                    edges.push_back(edge);
                }
            }
        }
    }
    return edges;
}

void Matrix_Adj::print() const{
    std::cout << "The nodes of the graph are:" << " ";
    for (double i=0; i < Nodes.size() ; i++)
    {
        std::cout << Nodes[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "The edges are" << std::endl;
    std::cout << "  ";
    for (double i = 0; i < Nodes.size(); i++)
    {
        std::cout << Nodes[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < Nodes.size(); i++)
    {
        std::cout << Nodes[i] << " ";
        for (int j = 0; j < Nodes.size(); j++)
        {
            std::cout << graph[i*Nodes.size() + j] << " ";
        }
        std::cout << "" << std::endl;
    }
}

void Matrix_Adj::indepth_rec(std::string node, std::vector<std::string>& visited){
    visited.push_back(node);
    std::cout << node << " has been visited" << std::endl;
    for (auto &edge : this->get_edges(node))
    {
        if( find(visited.begin(), visited.end(), edge.next()) == visited.end()){
            edge.print();
            indepth_rec(edge.next(), visited);
        }
    }
}

void Matrix_Adj::indepth_ite(std::string node){
    std::unordered_map<std::string, int> node_state; //On initialise l'état de tous les sommets à 0 = pas visité
    std::stack<std::string> pile;                    //On initialise la pile: on met tous les sommets du graph dedans et on met au top le sommet node

    for (auto &node_i : this->getNodes())
    {
        node_state.insert({node_i, 0});
        if (node_i != node)
        {
            pile.push(node_i);
        }
    }
    pile.push(node);
    node_state.at(node) = 1;
    std::cout << node << " has been visited " << std::endl;

    while (!(pile.empty()))
    {
        bool flag = false;
        for (auto &edge : this->get_edges(pile.top()))
        {
            if (node_state.at(edge.next()) == 0)
            {
                flag = true;
                node_state.at(edge.next()) = 1; //1 signifie que le sommet a été visité
                edge.print();
                std::cout << edge.next() << " has been visited " << std::endl;
                pile.push(edge.next());
                break;
            }
        }
        if (!flag)
        {
            node_state.at(pile.top()) = 2; //2 signifie que le sommet n'a plus de sommet adjacent non visité
            pile.pop();
        }
    }
}

void Matrix_Adj::inbreadth(std::string node, int level_max){
    std::unordered_map<std::string, int> node_state; //On initialise l'état de tous les sommets à 0 = pas visité
    for (auto &node : this->getNodes())
    {
        node_state.insert({node, 0});
    }

    std::queue<std::string> file;
    file.push(node);
    node_state.at(node) = 1;

    int current_level = 0;
    while (!(file.empty()))
    {
        for (auto &edge : this->get_edges(file.front()))
        {
            if (node_state.at(edge.next()) == 0)
            {
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