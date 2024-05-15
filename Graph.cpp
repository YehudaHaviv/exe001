//Graph.cpp

//id:211998646
//mail: yehuda029974129@gmail.com

#include "Graph.hpp"


using namespace std;

    void ariel::Graph::loadGraph(vector<vector<int>> &g){
        
        //check g is valid and not NULL or empty
        if(g.empty()) {
            throw std::invalid_argument("Invalid graph: The graph is empty.");    
        }
        bool isDirections = false;

        //check matrix is square then put the numbers in there place in the graph
        size_t rows = g.size();
        for(size_t i=0; i<rows; i++) {

            const auto& row_vector = g[i];
            if(row_vector.size() != rows) {
                throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
            }
            if(g[i][i]!=0) {
                throw std::invalid_argument("Invalid graph: cant be edge for ver from him self.");
            }
        }

        this->edges = 0;
        this->vertices = 0;
        this->valueEdgesGraph = false;

        this->graph.resize(rows, vector<int> (rows));
        for(size_t i=0; i<rows; i++){
            for(size_t j=0; j<rows; j++) {
                if(g[i][j]!=0&&g[i][j]!=1) {this->valueEdgesGraph=true;}
                if(g[i][j] != g[j][i]) {isDirections = true;} 
                
                this->graph[i][j] = g[i][j];
                if(g[i][j] != 0) {this->edges++;}
            }
        }

        if(!isDirections) {this->edges /= 2;}
        this->vertices = (int)rows;
    }

    void ariel::Graph::printGraph() {
        cout << "Graph with " << to_string(this->vertices) << " vertices and " << to_string(this->edges) << " edges." << '\n';
    }

