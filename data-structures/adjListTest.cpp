#include <iostream>
#include <list>
#include <vector>
#include <exception>

class Graph{
	private:
	// a struct created to be able to insert a possible weight of an edge
	//if we have 0 -> {1, 3}, then the edge that connects 0 to 1 has a weight of 3
		struct link{
			int vertex;
			int Weight;

			link(int v, int w = 1)
			:vertex{v}, Weight{w}
			{/*empty*/}
		};
		//a boolean to see if our graph is directed or not.
		bool isDirected;
		//our amount of vertices.
		int V;
		//this is our adjList. Each element of the list is another list.
		std::vector<std::vector<link>> adjList;

		//function to check if the provided indexes of vertices are valid ones.
    	bool checkVerticesIndexes(int u, int v)
    	{
        	bool parametersGreaterThanV = u >= this->V || v >= this->V;
        	bool parametersSmallerThanZero = u < 0 || v < 0;

        	return !parametersSmallerThanZero && !parametersGreaterThanV;
    	}

	public:
		Graph(int vertices, bool isDirected = false)
		{
			V = vertices;
			std::vector<std::vector<link>> temp(this->V, std::vector<link>(0));
			adjList = temp;
			this->isDirected = isDirected;
		}

		bool areAdjacent(int u, int v){
			for(int i = 0; i < this->adjList[u].size(); i++){
				if(this->adjList[u][i].vertex == v){
					return true;
				}
			}
			if(this->isDirected){
				return false;
			}

			for(int i = 0; i < this->adjList[v].size(); i++){
				if(this->adjList[v][i].vertex == u){
					return true;
				}
			}
			return false;
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
			//we can only add the same edge "both ways" if our graph isn't directed.
			if(!this->isDirected){
				link adj2 = link(v1, weight);
				adjList[v2].push_back(adj2);
			}
		}

		void removeEdge(int v1, int v2)
		{
			//check to see if any of the vertices is bigger than the number of actual vertices.
           	const bool paramsAreValid = checkVerticesIndexes(v1, v2);
           	if(!paramsAreValid){
            	throw std::invalid_argument("Indexes must be greater than zero and smaller than the amount of vertices.");
            }
            for(std::vector<link>::iterator it=adjList[v1].begin(); it != adjList[v1].end(); ++it){
            	if(it->vertex == v2)
            		adjList[v1].erase(it);
            }
			//if our graph isn't directed, then we also need to updated v2's list. 
			//That is, remove the v1 value from it.
			if(!this->isDirected){
				for(std::vector<link>::iterator it=adjList[v2].begin(); it != adjList[v2].end(); ++it){
					if(it->vertex == v1)
						adjList[v2].erase(it);
				}
			}

		}

		void printList()
		{
			for(int i = 0; i < V; i++){ 
				auto it = adjList[i].cbegin();
				std::cout << i << ": [";
				if(adjList[i].size() > 0){
					std::cout << it->vertex;
					while( it != --adjList[i].cend())
					{
						it++;
						std::cout<< ", "<< it->vertex;
					}
				}
				std::cout << "]" << std::endl ;
			}
		}

};

int main() {
    Graph teste(3, true);
	teste.addEdge(0,1);
	teste.addEdge(0,2);
    teste.printList();
}