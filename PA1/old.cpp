// CSE 431/531 (Fall 2022) PA1
// Due Date: Monday, 3/28/2022
// Feng Wei  50428109
// Use Deep-First-Search (DFS) to output the number of 
// the connected componets of an undirected graph G,
// and the size (number of vertices) of the largest component.


#include <iostream>
#include <list>
#include<vector>
using namespace std;
int temp = 0;
int n = 0;
vector<int> sizeVect(11000,0);
vector<int> degreeVect(11000,0);
// Graph class represents a undirected graph
// using adjacency list representation
class myGraph {
    int V; // No. of vertices
    // Pointer to an array containing adjacency lists
    list<int>* adjList;
  
    // A function used by DFS
    int DFSUtil(int v, bool visited[]);
  
public:
    myGraph(int V); // Constructor of Grapu Class
    ~myGraph();   // Destructor
    int count; // Number of the connected components
    int largestSize; // Size of the largest connected components 
    void edge(int u, int v);
    void countConnected();
};
  
// Method to print connected components in an
// undirected graph
void myGraph::countConnected()
{   
    // Mark all the vertices as not visited
    bool* visited = new bool[V];
    for (int v = 1; v <= V; v++){
        // cout <<"test v: "<<v <<" ";
        visited[v] = false;
    }
    for (int v = 1; v <= V; v++) {
        if (visited[v] == false) {
            // number of visited number vertices for the new loop
            // print all reachable vertices
            // from v
            myGraph::count +=1;
            temp =myGraph::count;
            DFSUtil(v, visited);
        }
    }
    //delete[] visited;
}
  
int myGraph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;
    // cout << v<< " ";
    // number of the visited vertices in the current compnonent
    sizeVect[temp] +=1;
    // cout << "current size"<<sizeVect[temp]<<"\n";
    // Recur for all the vertices
    // adjacent to this vertex

    list<int>::iterator i;
    for (i = adjList[v].begin(); i != adjList[v].end(); ++i)
        if (!visited[*i]){ 
           DFSUtil(*i, visited);
        }
    if (myGraph::largestSize < sizeVect[temp]){
        myGraph::largestSize = sizeVect[temp];
    }
    return n;
}
  
myGraph::myGraph(int V)
{
    myGraph::V = V;
    adjList = new list<int>[V+1];
    myGraph::count = 0;
    // number of vertices is from 1 to 10,000
    myGraph::largestSize = 1;
}
  
myGraph::~myGraph() { delete[] adjList; }
  
// add an undirected edge by adding u to list of v and v to list of u
void myGraph::edge(int u, int v)
{
    adjList[u].push_back(v);
    degreeVect[u] += 1;
    adjList[v].push_back(u);
    degreeVect[v] += 1;
}
  

int main(int argc, char ** argv)
{    
    int V; // Number of vertices inside the undirected Graph 
    int E; // Number of edges inside the undirected Graph
    cin >> V;
    myGraph graph(V); 
    cin >> E;  
    for (int i = 0; i < E; i++){
        int u, v;
        cin >> u;
        cin >> v;
        graph.edge(u,v);
    }
      
    graph.countConnected();
    // cout << "Number of connected components \n";
    cout << graph.count;
    cout << "\n";
    // cout << "Size of the largest connected component \n";
    cout << graph.largestSize;
    cout << "\n";
    // cout << "total number of output: "<<temp<<"\n";
    return 0;
}
