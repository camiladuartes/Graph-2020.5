#include <vector>
#include <string>
#include <iostream>
#include <exception>

std::ostream& operator<<(std::ostream& os, std::vector<int> adjNodes){
    os << "[ ";
    for(int i=0;i<adjNodes.size();i++){
        os << adjNodes[i] << ",";
    }
    os << "]";
    return os;
}


class Graph{
    int V; //amount of vertices
    //booleans to detect some possible properties of the graph
    bool isDirected;
    bool isWeighted;
    std::vector<std::vector<int>> adjMatrix; //our actual matrix 

    //function to check if the provided indexes of vertices are valid ones.
    bool checkVerticesIndexes(int u, int v){
        bool parametersGreaterThanV = u >= this->V || v >= this->V;
        bool parametersSmallerThanZero = u < 0 || v < 0;

        return !parametersSmallerThanZero && !parametersGreaterThanV;
    }

    public:

        int getAmountVert(){
            return this->V;
        }

        std::vector<std::vector<int>> getAdjMatrix(){
            return this->adjMatrix;
        }

        Graph(int V, bool isDirected = false, bool isWeighted = false){
            //checking to see if the number of vertices is valid 
            if(V <= 0){
                throw std::invalid_argument("Invalid number of vertices. Must be greater than 0.");
            }
            //initializing a temp matrix and assigning our matrix to the temp one 
            std::vector<std::vector<int>> temp(V, std::vector<int>(V, 0));
            
            this->V = V;
            this->isDirected = isDirected;
            this->isWeighted = isWeighted;
            this->adjMatrix = temp;
        }

        //adds an edge to the graph in receiving the terminal vertices as parameters
        //if there is already an edge connecting these two vertices, nothing happens
        void addEdge(int u, int v){
            //check to see if any of the vertices is bigger than the number of actual vertices.
            const bool paramsAreValid = checkVerticesIndexes(u, v);
            if(!paramsAreValid){
                throw std::invalid_argument("Indexes must be greater than zero and smaller than the amount of vertices.");
            }
            this->adjMatrix[u][v] = 1;
            //if our graph is directed, then we can't also set adjMatrix[v][u] to 1
            //because the order in this case matters
            if(!this->isDirected){
                this->adjMatrix[v][u] = 1;
            }
        }
        //adding the edge to a weighted graph. we need to provide the weight of the edge.
        void addEdge(int u, int v, int weight){
            const bool paramsAreValid = checkVerticesIndexes(u,v);
            if(!paramsAreValid){
                throw std::invalid_argument("Indexes must be greater than zero and smaller than the amount of vertices.");
            }
            if(!this->isWeighted){
                throw "Cannot inform weight of an edge on an unweighted graph!";
            }
            this->adjMatrix[u][v] = weight;
            if(!this->isDirected){
                this->adjMatrix[v][u] = weight;
            }
        }
        //a method that checks if two vertices are adjacent or not.
        bool areAdjacent(int u, int v){
            const bool paramsAreValid = checkVerticesIndexes(u,v);
            if(!paramsAreValid){
                throw std::invalid_argument("Indexes must be greater than zero and smaller than the amount of vertices.");
            }
            return this->adjMatrix[u][v] == 1;
        }
        //a method that returns the indexes of all nodes that are adjacecnt to a specific vertex.
        std::vector<int> getAdjacentNodes(int u){
            if(u < 0 || u >= this->V){
                throw std::invalid_argument("Index of vertex is out of range. Must be greater then zero and smaller than the amount of vertices");
            }
            std::vector<int> adjNodes;
            for(int i = 0; i < this->V; i++){
                if(this->adjMatrix[u][i] == 1){
                    adjNodes.push_back(i);
                }
            }
            return adjNodes;
        }





        //removes an edge to the graph by receiving its two endpoints
        //if there isn't any edge connecting these two vertices, nothing happens 
        void removeEdge(int u, int v){
            const bool paramsAreValid = checkVerticesIndexes(u,v);
            if(!paramsAreValid){
                throw std::invalid_argument("Indexes must be greater than zero and smaller than the amount of vertices.");
            }
            this->adjMatrix[u][v] = 0;
            //we can only do both ways if the graph isn't directed.
            if(!this->isDirected){
                this->adjMatrix[v][u] = 0;
            }
        }
        void printMatrix(){
            for(int i = 0; i < this->V; i++){
                std::cout << "[";
                for(int j = 0; j < this->V; j++){
                    std::cout << this->adjMatrix[i][j];
                    if(j != this->V - 1)
                        std::cout << ", ";
                }
                std::cout << "]";
                if(i != this->V - 1)
                    std::cout << '\n';
            }
            std::cout << "\n";
        }

};



//int main() {
//    Graph teste(3);
//    teste.addEdge(0,1);
//    teste.addEdge(0,2);
//    teste.printMatrix();
//    auto x = teste.getAdjacentNodes(0);
//    for(int i = 0; i < x.size(); i++){
//        std::cout << x[i] << " ";
//    }
//}
