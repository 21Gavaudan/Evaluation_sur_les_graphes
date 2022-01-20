#include "Utiles.h"
#include <fstream>
#include <sstream>

//Fonction permettant de passer de la représentation list à la représentation matrice
Matrix_Adj List2Matrix(const List_Adj &list)
{

    std::vector<double> graph_matrix;
    std::vector<std::string> Nodes;

    //Commencons par remplir les noms des sommets: on parcourt à la liste en récupérant les keys du dictionnaire et on les ajoute au vecteurs Nodes
    std::unordered_map<std::string, std::vector<edge> > Dict = list.get_Dict_List();
    for (std::unordered_map<std::string, std::vector<edge> >::iterator it = Dict.begin(); it != Dict.end(); it++)
    {
        Nodes.push_back(it->first);
    }
    //On crée également le dictionnaire qui a un sommet associe son indice dans la matrice
    std::unordered_map<std::string, int> dict_indexNodes = Index_of_the_keys(Nodes);

    //Construisons désormais notre liste vector graph

    //On commence par l'initialiser avec des 0
    int dim = list.size();

    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            graph_matrix.push_back(0.);
        }
    }
    //Puis lorsque edge existe entre s_i et s_j on y met la valeur du edge
    for (int k = 0; k < dim; k++)
    {
        std::vector<edge> list_edges = list.at(Nodes[k]);
        for (int l = 0; l < list_edges.size(); l++)
        {
            edge edge = list_edges[l];
            graph_matrix.at(dict_indexNodes.at(edge.previous()) * dim + dict_indexNodes.at(edge.next())) = edge.value();
        }
    }
    Matrix_Adj mat(graph_matrix, Nodes);
    return mat;
}



//Fonction permettant de passer de la représentation matrice à la représentation liste
List_Adj Matrix2List(const Matrix_Adj &matrix)
{
    std::unordered_map<std::string, std::vector<edge> > list_adj;

    std::vector<std::string> Nodes = matrix.getNodes();
    std::vector<double> graph = matrix.getGraph();

    std::unordered_map<int, std::string> Dict_indexNodes = Keys_of_the_index(Nodes);

    int dim = Nodes.size();
    for (int i = 0; i < dim; i++)
    {
        list_adj.insert({Dict_indexNodes.at(i), {}}); //on insere le sommet associé à l'indice i, puis on va parcourir la ligne de la matrice associé à ce sommet pour voir ses sommets adjacents
        for (int j = 0; j < dim; j++)
        {
            if (matrix.at(i, j) != 0)
            {
                edge edge(Dict_indexNodes.at(i), Dict_indexNodes.at(j), matrix.at(i, j));
                list_adj.at(Dict_indexNodes.at(i)).push_back(edge);
            }
        }
    }

    return list_adj;
}



//Fonction permettant de lire un fichier graph et en donner la représentation liste
List_Adj Readgraph_List(std::string filename){
    std::ifstream input_file(filename);
    // si problème d'ouverture de fichier on s'en va
    if (!input_file.is_open())
    {
        std::cerr << "cannot open file '" << filename << "'" << std::endl;
    }
    if (!(filename.find(".graph")))
    {
        std::cerr << "files must be a .graph" << std::endl;
    }

    std::string line;
    std::unordered_map<std::string, std::vector<edge> > list_adj;
    std::vector<std::string> Nodes;

    // on lit la ligne et on met son contenu dans la variable line
    while (getline(input_file, line))
    {
        std::istringstream iss(line);

        //On récupère les données sur la ligne
        std::string previous;
        iss >> previous;
        std::string next;
        iss >> next;
        double value;
        iss >> value;

        edge edge(previous, next, value);

        //Maintenant qu'on a récupérer le données de la ligne, il faut construire la représentation

        if (find(Nodes.begin(), Nodes.end(), edge.previous()) == Nodes.end())
        { //si le sommet previous n'est pas encore dans la liste des sommets, on le rajoute à la liste sommets et on le rajoute à la liste d'adjacence avec l'arête dont il est l'origine
            Nodes.push_back(edge.previous());
            list_adj.insert({edge.previous(), {edge}});
        }
        else
        {// sinon on ajoute le edge au sommet déjà visité
            list_adj.at(edge.previous()).push_back(edge);
        }
        if (find(Nodes.begin(), Nodes.end(), edge.next()) == Nodes.end())
        { //si le sommet next n'est pas encore dans la liste des sommets, on le rajoute à la liste sommets et on le rajoute à la liste d'adjacence
            Nodes.push_back(edge.next());
            list_adj.insert({edge.next(), {}});
        }
        //On n'ajoute pas de edge à sa loste d'adjacence car ici c'est une arete qui arrive vers le sommet, il n'est donc pas dans la liste d'adjacence de ce sommet
    }

    List_Adj res(list_adj);
    return res;
}



//Fonction permettant de lire un fichier graph et en donner la représentation matrice
Matrix_Adj Readgraph_Matrix(std::string filename){

    std::ifstream input_file(filename);
    // si problème d'ouverture de fichier on s'en va
    if (!input_file.is_open())
    {
    std::cerr << "cannot open file '" << filename << "'" << std::endl;
    }
    if (!(filename.find(".graph")))
    {
        std::cerr << "files must be a .graph" << std::endl;
    }

    std::string line;
    std::vector<double> graph;
    std::vector<std::string> Nodes;
    std::vector<edge> edges;

    //Commencons par remplit la liste des sommets et recuperer l'ensemble des arêtes dans la liste edges
    while (getline(input_file, line))
    {
        std::istringstream iss(line);

        std::string previous;
        iss >> previous;
        std::string next;
        iss >> next;
        double value;
        iss >> value;

        edge edge(previous, next, value);
        edges.push_back(edge);

        if (find(Nodes.begin(), Nodes.end(), previous) == Nodes.end())
        {
            Nodes.push_back(previous);
        }
        if (find(Nodes.begin(), Nodes.end(), next) == Nodes.end())
        {
            Nodes.push_back(next);
        }
    }

    std::unordered_map<std::string, int> index = Index_of_the_keys(Nodes);
    int dim = Nodes.size();
    //On initialise le graph
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            graph.push_back(0.);
        }
    }


    //on le remplit avec les values des aretes
    for (std::vector<edge>::iterator it = edges.begin(); it != edges.end(); it++)
    {
        graph.at(index.at(it->previous()) * dim + index.at(it->next())) = it->value();
    }

    Matrix_Adj res(graph, Nodes);
    return res;
}


