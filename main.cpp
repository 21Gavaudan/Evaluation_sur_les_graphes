#include "Utiles.h"
#include "Dijkstra.h"

int main(int argc, char **argv)
{
    std::string filename = argv[1];

    //Question 2: Lecture d'un fichier représentant un graph et affichage des graphes selon les deux représentations
    std::cout << "Question 2: Lecture d'un fichier représentant un graph et affichage des graphes selon les deux représentations" << std::endl;

    List_Adj l = Readgraph_List(filename);
    l.print();
    Matrix_Adj m = Readgraph_Matrix(filename);
    m.print();

    std::cout << std::endl;


    //Question 1: Classes liste et matrixe d'adjacence et passage d'une représentation à une autre
    std::cout << "Question 1: Classes liste et matrixe d'adjacence et passage d'une représentation à une autre" << std::endl;

    List_Adj list_from_matrix = Matrix2List(m);
    list_from_matrix.print();
    Matrix_Adj matrix_from_list = List2Matrix(l);
    matrix_from_list.print();

    std::cout << std::endl;

    //Question 3:Parcours en profondeur d'un graphe, méthode récursive
    std::cout << "Question 3: Parcours en profondeur d'un graphe, méthode récursive" << std::endl;

    std::vector<std::string> visited;
    l.indepth_rec("a", visited);
    m.indepth_rec("a", visited);

    std::cout <<  std::endl;


    //Question 4: Parcours en profondeur d'un graphe, méthode itérative
    std::cout << "Question 4: Parcours en profondeur d'un graphe, méthode itérative " << std::endl;

    l.indepth_ite("a");
    m.indepth_ite("a");

    std::cout << std::endl;


    //Question 5: Parcours en largeur d'un graphe
    std::cout << "Question 5: Parcours en largeur d'un graphe" << std::endl;

    l.inbreadth("a", 0);
    l.inbreadth("a", 1);
    m.inbreadth("a", 0);
    m.inbreadth("a", 1);

    std::cout << std::endl;

    
    //question 6: Algorithme de Dijkstra
    std::cout << "Question 6: Algorithme de Dijkstra" << std::endl;
   
    std::stack<std::string> chemin1 = Dijkstra(l, "a", "e");
    std::stack<std::string> chemin2 = Dijkstra(l, "b", "e");
    std::stack<std::string> chemin3 = Dijkstra(l, "d", "c");

    std::cout << std::endl;
    
    return 0;
}