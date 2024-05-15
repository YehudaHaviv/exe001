//Graph.hpp

//id: 211997646
//mail: yehuda029974129@gmail.com

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <stdexcept>

namespace ariel
{

    class Graph
    {

    public:
        int edges;
        int vertices;
        bool valueEdgesGraph;
        std::vector<std::vector<int>> graph;

        void loadGraph(std::vector<std::vector<int>> &g);

        void printGraph();
    };
}
#endif

