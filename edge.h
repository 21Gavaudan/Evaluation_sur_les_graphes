#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <vector>


class edge {
    std::string Previous_Node;
    std::string Next_Node;
    double Value_Edge;

    public:
    edge(std::string Previous_Node, std::string Next_Node, double Value_Edge) : Previous_Node(Previous_Node), Next_Node(Next_Node), Value_Edge(Value_Edge){}

    void print() const{
        std::cout << Previous_Node << " -> " << Next_Node << " " << Value_Edge << std::endl;
    }

    std::string previous(){
        return Previous_Node;
    }

    std::string next(){
        return Next_Node;
    }

    double value(){
        return Value_Edge;
    }
};
