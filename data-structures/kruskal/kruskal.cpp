#include <iostream>
#include <algorithm>
#include <vector>
#include "adjacencyMatrix.h"
#include "Aresta.h"

using namespace std;


/*
    Poundered graph example

                2
               | \
               |  \
            200|   \650       4      
               |    \       /   \
               |     \ 350 /     \ 250
               |      \   /       \
               |       \ /         \
0 ------------ 1 ------ 3 --------- 5
       280        400   |    600
                        | 
                        | 300
                        |        
                        6
*/


void printVector(vector<Aresta> V){
    for(auto it: V){
        cout << it << endl;
    }
    cout << endl;
}


int find(int *v, int vertice){
    if(v[vertice] == -1){
        return vertice;
    }
    return find(v, v[vertice]);
}


void unite(int *v, int vertice1 , int vertice2){
    int vertice1_set = find(v, vertice1);
    int vertice2_set = find(v, vertice2);
    v[vertice1_set] = vertice2_set;
}



Graph kruskal(vector<Aresta> graph, int vertAmount){
    
    Graph mst(vertAmount);

    // sorting the graph from the smallest wheight to the biggest wheight
    sort(graph.begin(), graph.end());

    // all spaces will be initialized with -1
    int subset[vertAmount];
    for(int i=0;i<vertAmount;i++){
        subset[i] = -1;
    }


    for(int i=0;i<graph.size();i++){

        int returnOfVertice1 = find(subset, graph[i].getVertice1());
        int returnOfVertice2 = find(subset, graph[i].getVertice2());

        // when the 2 vertices are different from each other, it means that this edge doens't make a cicle 
        // when this happens you can call the union algorithm
        if(returnOfVertice1 != returnOfVertice2){
            mst.addEdge(graph[i].getVertice1(), graph[i].getVertice2());
            unite(subset, returnOfVertice1, returnOfVertice2);
        }

    }    

    return mst;
}



int main(){  
    
    const int vertAmount = 7; // number of graph vertices

    Graph cities(vertAmount); 
    cities.addEdge(0, 1);
    cities.addEdge(1, 2);
    cities.addEdge(1, 3);
    cities.addEdge(2, 3);
    cities.addEdge(3, 4);
    cities.addEdge(3, 5);
    cities.addEdge(3, 6);
    cities.addEdge(4, 5);
    cities.printMatrix();
    cout << endl;


    // represents the poundered graph of cities
    vector<Aresta> pounderedGraph;

    pounderedGraph.push_back({0, 1, 280});
    pounderedGraph.push_back({1, 2, 200});
    pounderedGraph.push_back({1, 3, 400});
    pounderedGraph.push_back({2, 3, 650});
    pounderedGraph.push_back({3, 4, 350});
    pounderedGraph.push_back({3, 5, 600});
    pounderedGraph.push_back({3, 6, 300});
    pounderedGraph.push_back({4, 5, 250});

    Graph mst = kruskal(pounderedGraph, vertAmount);
    mst.printMatrix();
    
    
    return 0;
}

