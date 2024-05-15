//Algorithms.hpp

//id: 211998646
//mail: yehuda029974129@gmail.com

#ifndef ALGO_HPP
#define ALGO_HPP

#include "Graph.hpp"
#include <string>

namespace ariel{

    class Algorithms
    {
        public:
            static std::vector<std::pair<std::string, size_t>> bfsSreach(const Graph& g, size_t start);

            static std::vector<std::pair<std::string, int>> bellmanFord(const Graph& g, size_t start);

            static int isConnected(const Graph& g);

            static std::string shortestPath(const Graph& g, int start, int end);

            static std::string isContainsCycle(const Graph& g);

            static std::string isBipartite(const Graph& g);

            static std::string negativeCycle(const Graph& g);
    };
}
#endif

