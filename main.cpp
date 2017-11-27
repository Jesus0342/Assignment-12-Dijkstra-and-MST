/******************************************************************************
 * AUTHORS        : Jesus Sanchez &
 * ASSIGNMENT #12 : Dijkstra and MST
 * CLASS          : CS1D
 * SECTION        : MW: 3:00pm
 * DUE DATE       : 11/29/2017
 *****************************************************************************/

#include "Graph.h"

/******************************************************************************
 * DIJKSTRA AND MST
 * ----------------------------------------------------------------------------
 * This program utilizes a user defined Graph ADT in order to implement
 * Dijkstra's algorithm and determine the MST of the graph. Using Dijkstra's
 * algorithm, the shortest path from Atlanta to every city on the map will be
 * displayed along with the corresponding distance. Then, the MST of the graph
 * will be determined using Prim-Jarnik's algorithm with the edges and total
 * mileage being printed.
 * ----------------------------------------------------------------------------
 * INPUT:
 *    <There is no input.>
 *
 * OUTPUT:
 *	  Dijkstra's - Path to every city from Atlanta & associated mileage.
 *	  MST - Edges & Total Mileage
 *
 *****************************************************************************/
int main()
{
	cout << "***************************************************************\n"
		 << "* NAME           : Jesus Sanchez & \n"
		 << "* ASSIGNMENT #12 : Dijkstra and MST\n"
		 << "* CLASS          : CS1D - MW: 3:00pm\n"
		 << "* DUE DATE       : 11/29/2017\n*\n"
		 << "* DESCRIPTION: This program will implement Dijkstra's algorithm\n"
		 << "* and Prim-Kruskal's algorithm on a user defined Graph ADT. For\n"
		 << "* Dijkstra's algorithm, the shortest path to each city from \n"
		 << "* Atlanta will be printed with the associated mileage. The MST \n"
		 << "* algorithm will display the edges found during its implementation\n"
		 << "* and the total mileage.\n"
		 <<	"***************************************************************\n\n";

	Graph graph; // Graph object.

	cout << "Adding vertices to the graph...\n";

	// Initializes the graph by reading from Map.txt.
	graph.initializeGraph();

	cout << "\n*********************************\n"
			"* PART 1 - DIJKSTRA'S ALGORITHM *\n"
			"*********************************\n\n";

	string startCity = "Atlanta";

	// Vector T containing the vertices that will be visited during Dijkstra's.
	vector<string> T;

	// Arrays of costs and parents used for Dijkstra's.
	int costs[graph.size()];
	int parent[graph.size()];

	// Determines the shortest path from the starting vertex to all other vertices.
	graph.shortestPathsDijkstra(startCity, T, costs, parent);

	cout << "Printing the paths from " << startCity << " to all other cities:\n";
	for(int i = 0; i < graph.size(); i++)
	{
		cout << startCity << " to " << T[i] << endl;

		vector<string> path =  graph.returnPath(startCity, T[i], parent);

		for(int j = 0; j < path.size(); j++)
		{
			cout << path[j];

			if(j + 1 != path.size())
			{
				cout << " -> ";
			}
		}

		cout << "\nTotal Distance: " << costs[graph.findVertex(T[i])] << endl << endl;
	}

	cout << "\n****************\n"
			"* PART 2 - MST *\n"
			"****************\n\n";

	// Vector storing the order that the cities were visited it when determining
	// the MST of the graph.
	vector<string> mst;

	// Sets the starting city for the MST.
	startCity = "Seattle";

	cout << "Determining the MST starting at " << startCity << ".\n\n"
		 << "Printing MST edges:\n";
	int mstDistance = graph.primJarnikMST(startCity, mst);

	cout << "\nTotal Distance : " << mstDistance << endl;

	return 0;
}
