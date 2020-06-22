#include <iostream>
#include <list>
#include <exception>

class Graph{
	private:
		struct link{
			int vertex;
			int Weight;

			link(int v, int w = 1)
			:vertex{v}, Weight{w}
			{/*empty*/}

		};
		int V;
		std::list<link> *adjList;

		//function to check if the provided indexes of vertices are valid ones.
    	bool checkVerticesIndexes(int u, int v)
    	{
        	bool parametersGreaterThanV = u >= this->V || v >= this->V;
        	bool parametersSmallerThanZero = u < 0 || v < 0;

        	return !parametersSmallerThanZero && !parametersGreaterThanV;
    	}

	public:
		Graph(int vertices)
		{
			V = vertices;
			adjList = new std::list<link>[V];
		}

		void addEdge(int v1, int v2, int weight = 1)
		{
			//check to see if any of the vertices is bigger than the number of actual vertices.
           	const bool paramsAreValid = checkVerticesIndexes(v1, v2);
           	if(!paramsAreValid){
            	throw std::invalid_argument("Indexes must be greater than zero and smaller than the amount of vertices.");
            }

            link adj = link(v2, weight);
            adjList[v1].push_back(adj);
		}

		void removeEdge(int v1, int v2)
		{
			//check to see if any of the vertices is bigger than the number of actual vertices.
           	const bool paramsAreValid = checkVerticesIndexes(v1, v2);
           	if(!paramsAreValid){
            	throw std::invalid_argument("Indexes must be greater than zero and smaller than the amount of vertices.");
            }

            for(std::list<link>::iterator it=adjList[v1].begin(); it != adjList[v1].end(); ++it){
            	if(it->vertex == v2)
            		adjList[v1].erase(it);
            }

		}

		void printList()
		{
			for(int i = 0; i < V; i++){ 
				auto it = adjList[i].cbegin();
				std::cout << i << ": [ " << it->vertex;
				while( it != adjList[i].cend() )
				{
					it++;
					std::cout<< ", "<< it->vertex;
				}
				std::cout << "]" << std::endl ;
			}
		}

};

int main() {
    Graph teste(3);
    teste.addEdge(0,1);
    teste.addEdge(0,2);
    teste.printList();
}