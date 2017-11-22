#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Struct representing an edge in the graph.
struct Edge
{
	string u; // Starting city.
	string v; // Ending city.
	bool discoveryEdge; // Whether or not edge is a discovery edge.
	int weight; // Distance between the cities.

	// Edge object constructor.
	Edge()
	{
		u = "";
		v = "";
		discoveryEdge = false;
		weight = 0;
	}
};

// Struct representing a vertex in the graph.
struct Vertex
{
	string city; // Name of the city in the vertex.
	bool visited; // Whether or not the vertex has already been visited.
	vector<Edge> edgeList; // List of incident edges.

	// Vertex object constructor.
	Vertex()
	{
		city = "";
		visited = false;
	}
};

// Graph class that uses an adjacency list to store edges.
class Graph
{
public:
	Graph();
	~Graph();

	// Returns true if the graph is empty, else returns false.
	bool empty();

	// Returns the number of vertices in the graph.
	int size();

	// Reads the edges from a text file and adds them to the graph.
	// POST-CONDITION: The graph will be filled with the values in the text file.
	void initializeGraph();

	// Inserts a vertex to the graph with the specified city name.
	// PRE-CONDITIONS:
	// city - City name of new vertex must be defined.
	// POST-CONDITION: A new vertex is added to the graph.
	void insertVertex(string city);

	// Returns the graph index of the specified city.
	// PRE-CONDITIONS:
	// city - Name of city to be searched for must be defined.
	unsigned int findVertex(string city);

	// Adds a new edge to the graph and a new vertex if a vertex with value "u"
	// does not yet exist.
	// PRE-CONDITIONS:
	// u - Starting city must be defined.
	// v - Ending city must be defined.
	// weight - Distance between the cities must be defined.
	// POST-CONDITION: A new edge is added to the edge list of vertex "u".
	void insertEdge(string u, string v, int weight);

	// Returns a list of the vertices in the graph.
	vector<string> vertices();

	// Returns a list of the edges in the graph.
	vector<string> edges();

	// Performs a depth-first search on the graph starting at the indicated city
	// using recursion.
	// PRE-CONDITIONS:
	// startingCity - City where the DFS will begin must be defined.
	// dfs - Vector of city names in the order they were visited during DFS does
	//		 not have to be defined.
	// POST-CONDITION: The list of cities visited in the DFS order is returned.
	int DFS(string startingCity, vector<string> &dfs);

	// Determines the minimum spanning tree of the graph using Prim-Jarnik's
	// Algorithm.
	// PRE-CONDITIONS:
	// startingCity - City where MST will begin must be defined.
	// mst - Vector of city names in the order they were visited during the MST
	// 		 "traversal"
	// POST-CONDITION: The mst vector will contain the names of the cities in
	// 				   the order they were visited in during the MST "traversal"
	int primJarnikMST(string startingCity, vector<string> &mst);

private:
	// Finds the closest vertex to the current vertex and returns its graph index.
	// PRE-CONDITIONS:
	// currVertex - Index of the current vertex must be defined.
	// dfs - Vector of cities visited during DFS must be defined.
	int smallestEdgeDFS(int currVertex, vector<string> &dfs);

	// Finds the smallest edge from all of the previously visited vertices and
	// returns its graph index.
	// PRE-CONDITIONS:
	// mst - Vector of cities visited during MST must be defined.
	// POST-CONDITION: The graph index of the next vertex to be visited is
	//				   returned.
	int smallestEdgeMST(vector<string> &mst);

	// Returns the smallest edge of the indicated vertex.
	// PRE-CONDITION:
	// vertex - Vertex whose smallest edge will be found must be defined.
	int smallestEdge(int vertex);

	int distanceBetween(int v1, int v2);

	// Returns the number of vertices that have been visited.
	unsigned int verticesVisited();

	// Returns the number of edges discovered from the specified vertex.
	// PRE-CONDITIONS:
	// currVertex - Graph index of the current vertex must be defined.
	unsigned int edgesDiscovered(int currVertex);

	vector<Vertex> graph; // Vector of vertices used to represent a graph.

	int dfsDistance; // Distance traveled during DFS.

	int mstDistance;
};

#endif
