CPP=clang++ -std=c++20
RM=rm -f

graph : List_Representation.o Matrix_Representation.o edge.o Utiles.o Dijkstra.o main.o
	$(CPP) $^ -o $@

# vérifiez les dépendances
edge.o : edge.cpp edge.h
List_Representation.o : List_Representation.cpp List_Representation.h edge.h
Matrix_Representation.o : Matrix_Representation.cpp Matrix_Representation.h
Utiles.o : Utiles.cpp Utiles.h Matrix_Representation.h List_Representation.h edge.h
Dijkstra.o : Dijkstra.cpp Utiles.h
main.o : main.cpp Utiles.h

%.o:%.cpp
	$(CPP) -o $@ -c $<

clean:
	$(RM) *.o graph

.PHONY: clean
