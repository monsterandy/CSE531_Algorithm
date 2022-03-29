
// CSE 431/531 (Fall 2022) PA1
// Due Date: Monday, 3/28/2022
// Feng Wei  50428109
// Use Deep-First-Search (DFS) to output the number of 
// the connected componets of an undirected graph G,
// and the size (number of vertices) of the largest component.


#include <iostream>
#include <list>
#include <vector>
using namespace std;

// Vector to store the size of all the connected components in graph G(V,E)
// Largest number of size is 10,000
vector<int> sizeVect(11000,0);
// Vector to store the degress of all the vertices in graph G(V,E)
// Largest number of size is 10,000
vector<int> degreeVect(11000,0);
// A temporary number used to locate the connected components
int temp = 0;

// Graph class to store undirected graph G =(V,E)
class udrGraph {
    public:
    int V; // Number of vertices in the graph
    int E; // Number of edges in the graph
    // Adjancency list that contains the graph
    list<int>* adjList; 
    udrGraph(int V, int E); // Constructor of myGraph class
    ~udrGraph();   // Destructor of myGraph class
    int countNumber; // Number of the connected components
    int largestSize; // Size of the largest connected components 
    int edge(int u, int v);
    // Method to check the connected components in G(V,E)
    int graphProcess();
    // Deep-first-search method
    int  dfSearch(int u, vector<int> &visited);
};
  
// Process the graph to check the connected components 
int udrGraph::graphProcess(){   
    // Mark all the vertices as not visited 0
    vector<int> visited(V,0);
    //Process all vertices from number 1 to number V
    for (int u = 1; u <= V; u++) {
        if (visited[u] == 0) {
            // Number of connected components
            udrGraph::countNumber += 1;
            temp = udrGraph::countNumber;
            dfSearch(u, visited);
        }
    }
    return 0;
}

// Deep-first-search  
int udrGraph::dfSearch(int u, vector<int> &visited){
    // Set vertices v as visited 1 
    visited[u] = 1;
    // cout << v<< " ";
    // Number of the visited vertices in the current compnonent
    sizeVect[temp] +=1;
    // cout << "current size"<<sizeVect[temp]<<"\n";
    
    // Serach all vertices in adjList[u]
    list<int>::iterator ite;
    for (ite = adjList[u].begin(); ite != adjList[u].end(); ++ite)
        if (!visited[*ite]){ 
           dfSearch(*ite, visited);
        }
    if (udrGraph::largestSize < sizeVect[temp]){
        udrGraph::largestSize = sizeVect[temp];
    }
    return 0;
}
  
// The Constructor of myGraph Class
udrGraph::udrGraph(int V, int E){
    udrGraph::V = V;
    udrGraph::E = E;
    // Number of vertices is from 1 to 10,000
    adjList = new list<int>[V+1];
    // Set the initial number of connected components to 0
    udrGraph::countNumber = 0; 
    // Set the initial number of largest size to 0
    udrGraph::largestSize = 0;
}

// The Destructor of myGraph class  
udrGraph::~udrGraph() { 
    delete[] adjList;
}
  
// Add an edge to the graph
int udrGraph::edge(int u, int v){
    // Add vertice v to the list[u]
    adjList[u].push_back(v);
    // Add 1 to the degree of vertice u
    degreeVect[u] += 1;
    // Add vertice v to the list[v]
    adjList[v].push_back(u);
    // Add 1 to the degree of vertice v
    degreeVect[v] += 1;
    return 0;
}
  

int main(int argc, char ** argv){    
    int V; // Number of vertices inside the undirected Graph 
    int E; // Number of edges inside the undirected Graph
    // Input V and E
    cin >> V;
    cin >> E;
    // Create graph G(V,E)  
    udrGraph graph(V,E); 
    // Total number of edges is E
    for (int i = 0; i < E; i++){
        int u, v;
        cin >> u;
        cin >> v;
        // Add the edge (u,v) to the graph
        graph.edge(u,v);
    }

    // Process the graph  
    graph.graphProcess();
    // cout << "Number of connected components \n";
    cout << graph.countNumber;
    cout << "\n";
    // cout << "Size of the largest connected component \n";
    cout << graph.largestSize;
    cout << "\n";
    // cout << "Total number of output: "<<temp<<"\n";
    return 0;
}
