#include <iostream>
#include <exception>
#include <vector>
using namespace std;

/*! Implementing an Incidence Matrix to represent
 * a Graph.
 */
class Graph{
    //=== Private data.
    private:
        int V; //!< Number of vertices.
        bool isDirected; //!< Bool to tell us if it is a directed graph.
        std::vector<std::vector<int>> incMatrix; //!< Our Incidence Matrix.

        /// Function to check if the given vertices are valid.
        bool checkVerticesIndexes(int u, int v){
            bool parametersGreatherThanV = u >= this->V or v >= this->V;
            bool parametersSmallerThanZero = u < 0 or v < 0;

            return !parametersGreatherThanV and !parametersSmallerThanZero;
        }

    //=== Public interface.
    public:
        /// Constructor.
        Graph(int V, bool isDirected = false){
            // Checking if the number of vertices is valid
            if(V <= 0){
                throw std::invalid_argument("Invalid number of vertices. Must be greater than 0.");
            }
            
            this->V = V;
            this->isDirected = isDirected;
        }

        /// Function to add an edge to the Graph through vertices received as parameters.
        void addEdge(int u, int v){
            // Check if vertices u or v are bigger than the number of vertices instantiated.
            const bool paramsAreValid = checkVerticesIndexes(u, v);
            if(!paramsAreValid){
                throw std::invalid_argument("Indexes must be greater than zero and smaller than the amount of vertices.");
            }

            // Adding the new edge, at first filled with zeros.
            vector<int> newEdge(V, 0);
            newEdge[u] = 1;
            // If our graph is directed.
            if(this->isDirected)
                newEdge[v] = -1;
            // Otherwize.
            else
                newEdge[v] = 1;
            this->incMatrix.push_back(newEdge);
        }

        /// Function to remove an edge of the Graph through vertices(two endpoints) received as parameters.
        void removeEdge(int u, int v){
            const bool paramsAreValid = checkVerticesIndexes(u, v);
            if(!paramsAreValid){
                throw std::invalid_argument("Indexes must be greater than zero and smaller than the amount of vertices.");
            }

            for(auto it = this->incMatrix.begin(); it != this->incMatrix.end(); it++){
                if(it->at(u) != 0 and it->at(v) != 0){
                    this->incMatrix.erase(it);
                    break;
                }
            }
        }

        /// Function to print our Incidence Matrix.
        void printMatrix(){
            for(int i = 0; i < this->incMatrix.size(); i++){
                for(int j = 0; j < this->incMatrix[i].size(); j++){
                    cout << incMatrix[i][j] << " ";
                }
                cout << endl;
            }
        }
};

int main(){
    cout << ">>> Simple Graph Example: " << endl;
    Graph graph(3);
    graph.addEdge(0,1);
    graph.addEdge(0,2);
    graph.removeEdge(0,2);
    graph.printMatrix();

    cout << endl;

    cout << ">>> Directed Graph Example: " << endl;
    Graph direcGraph(3, true);
    direcGraph.addEdge(0,1);
    direcGraph.addEdge(0,2);
    direcGraph.printMatrix();

    return 0;
}