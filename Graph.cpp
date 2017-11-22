#include "Graph.h"

Graph::Graph()
{
	dfsDistance = 0;

	mstDistance = 0;
}

Graph::~Graph()
{

}

bool Graph::empty()
{
	return graph.empty();
}

int Graph::size()
{
	return graph.size();
}

void Graph::initializeGraph()
{
	fstream fin; // File stream variable.

	// Opens the file.
	fin.open("Map.txt");

	// Reads in the contents of the file.
	while(!fin.eof())
	{
		string u; // Starting city.
		string v; // Ending city.
		int weight; // Distance between the cities.

		getline(fin, u, ',');
		getline(fin, v, ',');
		fin >> weight;
		fin.ignore(1000, '\n');

		// Inserts the edge to the graph.
		insertEdge(u, v, weight);
	}

	fin.close();
}

unsigned int Graph::findVertex(string city)
{
	unsigned int index = 0;
	bool found = false;

	// Searches for the city in the graph and returns the index of the graph it
	// was found, else returns the size of the graph.
	while(index < graph.size() && !found)
	{
		if(graph.at(index).city == city)
		{
			found = true;
		}
		else
		{
			index++;
		}
	}

	return index;
}

void Graph::insertVertex(string city)
{
	// Adds the vertex to the graph if it does not yet exist.
	if(findVertex(city) == graph.size())
	{
		Vertex newVertex;

		newVertex.city = city;
		newVertex.visited = false;

		cout << newVertex.city << endl;

		graph.push_back(newVertex);
	}
}

void Graph::insertEdge(string u, string v, int weight)
{
	// Returns the index of the vertex.
	unsigned int index = findVertex(u);

	// Adds the vertex to the graph if it does not yet exist and performs a
	// recursive call, else adds the edge to the edgeList of the specified vertex.
	if(index == graph.size())
	{
		insertVertex(u);

		insertEdge(u, v, weight);
	}
	else
	{
		Edge newEdge;

		newEdge.u = u;
		newEdge.v = v;
		newEdge.weight = weight;

		graph.at(index).edgeList.push_back(newEdge);
	}
}

vector<string> Graph::vertices()
{
	vector<string> cityNames; // Vector of city names.

	// Adds the names of the cities in the graph to the vector.
	for(unsigned int i = 0; i < graph.size(); i++)
	{
		cityNames.push_back(graph[i].city);
	}

	return cityNames;
}

vector<string> Graph::edges()
{
	vector<string> edgeList; // Vector of edges.

	// Adds the edges in the graph to the vector if the node has edges.
	for(unsigned int i = 0; i < graph.size(); i++)
	{
		if(graph.at(i).edgeList.size() != 0)
		{
			// Pushes the edge pair onto the vector in (u, v) format.
			for(unsigned int j = 0; j < graph.at(i).edgeList.size(); j++)
			{
				edgeList.push_back("(" + graph.at(i).edgeList.at(j).u + ", "
									   + graph.at(i).edgeList.at(j).v + ")");
			}
		}
	}

	return edgeList;
}

unsigned int Graph::verticesVisited()
{
	int numVisited = 0; // Number of vertices visited.

	// Iterator to the first vertex in the graph.
	vector<Vertex>::iterator graphIt = graph.begin();

	// Counts the number of vertices in the graph that are marked as visited.
	while(graphIt != graph.end())
	{
		if(graphIt->visited)
		{
			numVisited++;
		}

		graphIt++;
	}

	return numVisited;
}

unsigned int Graph::edgesDiscovered(int currVertex)
{
	int numVisited = 0; // Number of edges discovered.

	// Counts the number of edges at the current vertex that have been discovered.
	for(unsigned int i = 0; i < graph.at(currVertex).edgeList.size(); i++)
	{
		if(graph.at(findVertex(graph.at(currVertex).edgeList.at(i).v)).visited)
		{
			numVisited++;
		}
	}

	return numVisited;
}

int Graph::primJarnikMST(string startingCity, vector<string> &mst)
{
    // Reset the graph, this should be its own function
    if(verticesVisited() == graph.size())
    {
        for (int i=0; i<graph.size(); i++)
        {
            graph[i].visited = false;

            for (int j=0; j< graph.at(i).edgeList.size(); j++)
            {
                graph[i].edgeList[j].discoveryEdge = false;
            }
        }

        mstDistance = 0;
    }

	// Gets the graph index of the vertex being visited.
	int currVertex = findVertex(startingCity);

	// Visits the vertex.
	graph.at(currVertex).visited = true;

	// Adds the vertex to the MST vector.
	mst.push_back(startingCity);

	// Performs a recursive call on itself to visit all vertices in the graph.
	if(mst.size() != size())
	{
		// Gets the graph index of the next closest city in the graph.
		int nextVertex = smallestEdgeMST(mst);

		// Performs recursive call to visit the next closest city.
		primJarnikMST(graph.at(nextVertex).city, mst);
	}

	return mstDistance;
}

int Graph::smallestEdgeMST(vector<string> &mst)
{
	// Finds the closest city to the root if it is the only vertex in T, else
	// finds the edge with the smallest weight among the edges adjacent to T.
	if(mst.size() == 1)
	{
		// Graph vertex of the city closest to the root.
		int smallestVertex = smallestEdge(findVertex(mst.front()));

		// Accumulates total distance.
		mstDistance += distanceBetween(findVertex(mst.front()), smallestVertex);

		// Prints the edge.
		cout << "(" << mst.front() << ", " << graph[smallestVertex].city << ")\n";

		return smallestEdge(findVertex(mst.front()));
	}
	else
	{
		// MST index of the city with the smallest edge and the index of the
		// city it is being compared to.
		int smallId = 0;
		int compId = smallId + 1;

		// Size of T.
		int size = mst.size();

		// Compares the smallest edge of smallId to all other smallest edges of
		// the cities in T.
		while(compId < size)
		{
			// Graph indexes of the city in MST with the smallest edge and city
			// it is being compared to.
			int smallVer = findVertex(mst[smallId]);
			int compVer = findVertex(mst[compId]);

			// Increments smallId to the next city in MST if all of the edges
			// of smallVer have already been visited, else checks if all the
			// edges of compVer have been visited.
			if(graph[smallVer].edgeList.size() == edgesDiscovered(smallVer))
			{
				smallId++;
			}
			else
			{
				// Compares the smallest edge of smallVer and compVer if compVer's
				// edges have not all been visited.
				if(graph[compVer].edgeList.size() != edgesDiscovered(compVer))
				{
					// Distance between smallVer and its smallest edge.
					int smallDist = distanceBetween(smallVer, smallestEdge(smallVer));

					// Distance between compVer and its smallest edge.
					int compDist =  distanceBetween(compVer, smallestEdge(compVer));

					// Assigns compId to smallId if compVer has a smaller
					// edge than the current smallest vertex.
					if(smallDist > compDist)
					{
						smallId = compId;
					}
				}
			}

			// Increments compId so that it is always at least 1 index ahead of
			// smallId.
			compId++;
		}

		// Accumulates the total MST distance.
		mstDistance += distanceBetween(findVertex(mst[smallId]),
				   	   	   	   	   	   smallestEdge(findVertex(mst[smallId])));

		// Graph index of the city with the closest edge.
		int smallestVertex = findVertex(mst[smallId]);

		// Gets the name of the city that is the closest to the city with the
		// closest edge.
		string nextCity = graph.at(smallestEdge(smallestVertex)).city;

		// Prints the smallest edge (next edge to be visited).
		cout << "(" << mst[smallId] << ", " << nextCity << ")\n";

		// Finds the graph index of the closest city.
		smallId = findVertex(nextCity);

		return smallId;
	}
}

int Graph::smallestEdge(int vertex)
{
	// Edge list vertex of the closest city.
	int smallestIndex = 0;

	// Edge list vertex of the city whose distance is being compared to the
	// city at edgeList.at(smallestIndex).
	int compIndex = smallestIndex + 1;

	// Gets the size of the edgeList for the current vertex.
	int size = graph.at(vertex).edgeList.size();

	// Finds the next closest city that has not been visited yet.
	while(compIndex < size)
	{
		// Gets the graph index of the next closest city.
		int smallestVertex = findVertex(graph.at(vertex).edgeList.at(smallestIndex).v);

		// Gets the graph index of the city in the edge list being comapred
		// to the city at edgeList.at(smallestIndex).
		int compVertex = findVertex(graph.at(vertex).edgeList.at(compIndex).v);

		// If the vertex at graph.at(smallestVertex) has already been visited,
		// increments smallest index and does nothing, else checks if the
		// vertex it is being compared to has been visited.
		if(graph.at(smallestVertex).visited)
		{
			smallestIndex++;
		}
		else
		{
			// If the vertex smallestVertex is being compared to has not been
			// visited, compares their weights, else does nothing.
			if(!(graph.at(compVertex).visited))
			{
				if(graph.at(vertex).edgeList.at(smallestIndex).weight >=
						graph.at(vertex).edgeList.at(compIndex).weight)
				{
					smallestIndex = compIndex;
				}
			}
		}

		// Increments compIndex so that it is always the after smallestIndex.
		compIndex++;
	}

	// Finds the graph index of the closest city.
	smallestIndex = findVertex(graph.at(vertex).edgeList.at(smallestIndex).v);

	return smallestIndex;
}

int Graph::distanceBetween(int v1, int v2)
{
	int i = 0;

	// Finds v2 in v1's edge list.
	while(graph[v1].edgeList[i].v != graph[v2].city)
	{
		i++;
	}

	return graph[v1].edgeList[i].weight;
}
