#include <iostream>
#include "adjacencyMatrix.h"

using namespace std;

class Pruffer{
    private:
        vector<int> code;
    public:

        const vector<int> &getCode() const {
            return code;
        }

    //  will check if the vertex is a leaf
        bool isLeaf(Graph graph, int vertexVal){
            int adjacentVertexesCounter = 0;

            // verifying the number of adjacent vortexes from this vortex
            for(int j=0;j<graph.getAmountVert();j++) {
                adjacentVertexesCounter += graph.getAdjMatrix()[vertexVal][j];
            }

            return adjacentVertexesCounter == 1;

        }


        void removeLeaf(Graph *graph){
            // verificar em todos os vertices se ele sao leafs ou n
            for(int i=0;i<graph->getAmountVert();i++){
                if(isLeaf(*graph, i)){
                    cout << i << " is leaf" << endl;
                    cout <<"adjacente ao " << i << " : " << graph->getAdjacentNodes(i) << endl;
                    this->code.push_back(graph->getAdjacentNodes(i)[0]); // if its a leaf node, it has only 1 adjacent node and it's in position 0
                    graph->removeEdge(i, graph->getAdjacentNodes(i)[0]);
                    break;
                }
            }
        }

        // this process will be repeated n-2 times
        void encode(Graph *graph){
            for(int i=0;i<graph->getAmountVert()-2;i++){
                removeLeaf(graph);
                graph->printMatrix();
            }
        }


};


int main(){
    Graph *graph = new Graph(5);
    graph->addEdge(0, 1);
    graph->addEdge(0, 2);
    graph->addEdge(2, 3);
    graph->addEdge(3, 4);
    graph->printMatrix();

    Pruffer *pruffer = new Pruffer();

    pruffer->encode(graph);

    cout << pruffer->getCode();
    return 0;
}