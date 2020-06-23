#include <iostream>
#include "adjacencyMatrix.h"

using namespace std;

class Pruffer{
    private:
        vector<int> code;
        vector<int> nodeDegrees;

    public:

        const vector<int> &getCode() const { return code;}
        const vector<int> &getNodeDegrees() const { return nodeDegrees;}


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
            }
        }



        void findNodeDegrees(){
            auto nodeDegreesSize = this->code.size() + 2; // the size os this list will be the code size + 2
            auto counter = 0;

            for(int i=0;i<nodeDegreesSize;i++){
                counter = 0;
                for(int j=0;j<code.size();j++){
                    if(code[j] == i){
                        counter++;
                    }
                }
                nodeDegrees.push_back(counter + 1); // the degree will be the number of times i can find [i] in the code list + 1
            }
        }



        // this method will find the vortex with the minor label with degree 1
        int findMinorLabel(vector<int> nodeDegrees){
            for(int i=0;i<nodeDegrees.size();i++){
                if(nodeDegrees[i] == 1){
                    return i;
                }
            }
        }



        void decode(Graph *graph){
            int vortex1;
            int vortex2;
            vector<int> lastVortexes;

            // here i'll have to take a number from puffer code and then increment in the vector
            // in the nodeDegrees vector i'll have to find a degree 1 vertex with the smallest label
            for(int i=0;i<this->code.size();i++){
                vortex1 = code[i];
                vortex2 = findMinorLabel(this->nodeDegrees);

                nodeDegrees[vortex1]--;
                nodeDegrees[vortex2]--;

                graph->addEdge(vortex1, vortex2);
            }

            // after go through all the code vector it will last two indexes with degree 1
            for(int i=0;i<nodeDegrees.size();i++){
                if(nodeDegrees[i] == 1){
                    lastVortexes.push_back(i);
                    nodeDegrees[i]--;
                }
            }
            graph->addEdge(lastVortexes[0], lastVortexes[1]);

        }



};


int main(){

    Graph *graph = new Graph(8);
    graph->addEdge(0, 1);
    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(3, 6);
    graph->addEdge(2, 5);
    graph->addEdge(2, 4);
    graph->addEdge(4, 7);
    graph->printMatrix();

    cout << endl << endl;

    Pruffer *pruffer = new Pruffer();
    pruffer->encode(graph);
    graph->printMatrix();

    cout << "Pruffer code vector: " << pruffer->getCode() << endl;
    pruffer->findNodeDegrees();
    cout << "Node degrees vector: " << pruffer->getNodeDegrees() << endl << endl;

    pruffer->decode(graph);

    graph->printMatrix();


    return 0;
}