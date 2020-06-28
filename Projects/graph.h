#include "vertex.h"
#include <vector>
#include <queue>
#include <string>

using namespace std;

class Graph {
public:
	Graph(map<char, Vertex> vt) {
		vertices = vt;
	}

	// prints the adjacency list
	void printAdjList() {
		// for every vertex in the graph
		for (pair<char, Vertex> v : vertices) {
			// print the initial vertex
			cout << v.first << " : ";
			// print all of the vertices that are adjacent to v
			map<char, int> adjList = v.second.getAdjList();
			for(pair<char, int> vertex : adjList)
				cout << "->(" << vertex.first << "," << vertex.second << ")";
			cout << endl;
		}
	}

	// find the shortest path of the graph using Dijkstra's algorithm
	void shortestPath(Vertex s) {
		// create a copy of the graph
		map<char, Vertex> verticesCopy = vertices;

		// set all of the vertices to have no path and a distance of INFINITY
		for (pair<char, Vertex> v : verticesCopy) {
			verticesCopy.at(v.first).setPath(' ');
			verticesCopy.at(v.first).setDist(INT32_MAX);
		}

		// set the distance of the source vertex to 0
		verticesCopy.at(s.getName()).setDist(0);
		
		while(1) {
			// get the smallest unvisited distance vertex 
			Vertex v = smallestUnknownDist(s, verticesCopy);

			// if there are know more vertices to visit, the algorithm is done
			if (v.getName() == ' ')
				break;

			// set vertex v to visited
			verticesCopy.at(v.getName()).setKnown(true);

			// for every vertex w adjacent to v
			for (pair<char, int> w : verticesCopy.at(v.getName()).getAdjList()) {
				// if w is unvisited
				if (verticesCopy.at(w.first).getKnown() == false) {
					// "vDist" is the dist val of vertex v and "cvw" is the dist val between vertices v and w
					int vDist = verticesCopy.at(v.getName()).getDist();
					int cvw = w.second;

					// if the current dist is smaller than the known dist of w
					if (vDist + cvw < verticesCopy.at(w.first).getDist()) {
						// decrease w's dist to the smaller dist (vDist + cvw)
						verticesCopy.at(w.first).setDist(vDist + cvw);
						verticesCopy.at(w.first).setPath(v.getName());
					}
				}
			}
		}
		// display the shortest paths
		displayPaths(s, verticesCopy);
	}

	// finds the smallest unknown adjacent Vertex distance 
	Vertex smallestUnknownDist(Vertex s, map<char, Vertex> verticesCopy) {
		// "min" will hold the minimum dist and "minKey" (initially ' ') will hold the vertex char associated with the minimum dist
		int min = INT32_MAX;
		char minKey = ' ';

		// for every vertex adjacent to the source s
		for (pair<char, int> vertex : s.getAdjList()) {
			// if vertex's dist is less than the min and vertex is unvisited
			if (vertex.second < min && verticesCopy.at(vertex.first).getKnown() == false) {
				// update the min to vertex's dist and the minKey to vertex's name
				min = vertex.second;
				minKey = vertex.first;
			}
		}

		// if the source's dist is less than the min and the source is unvisited, return the source vertex
		if (verticesCopy.at(s.getName()).getDist() < min && verticesCopy.at(s.getName()).getKnown() == false)
			return verticesCopy.at(s.getName());

		// if the minKey was never assigned, return a dummy vertex that will end the algorithm
		if (minKey == ' ')
			return Vertex{ minKey, INT32_MAX, ' ', 0 };

		// return the vertex associated with minKey
		return verticesCopy.at(minKey);
	}

	// displays the shortest paths from source Vertex s to every other vertex
	void displayPaths(Vertex s, map<char, Vertex> verts) {
		// for every vertex in the graph
		for (pair<char, Vertex> vertex : verts) {
			// if vertex's path is empty and vertex is not the source, it is unreachable
			if (vertex.second.getPath() == ' ' && vertex.first != s.getName())
				cout << "Warning: Not All Vertices May Be Reached.\n";
			// else if vertex's path (parnet) is the source or vertex's name is the source, display the source, vertex's name, and the dist from s to vertex
			else if(vertex.second.getPath() == s.getName() || vertex.first == s.getName())
				cout << s.getName() << " -> " << vertex.first << " : " << vertex.second.getDist() << endl;
			// else, the path from the source to "vertex" consists of more than two vertices
			else {
				cout << s.getName();

				// "currVertex" is the current vertex in the path and "path" is the path that will be displayed
				Vertex currVertex = verts.at(vertex.first);
				string path = "";

				// while there are still vertices in the path to traverse
				while (currVertex.getName() != s.getName()) {
					// append currVertex's + ">-" to the path
					path = path + currVertex.getName() + " >- ";
					// updated currVertex to it's parent vertex
					currVertex = verts.at(currVertex.getPath());
				}
				// reverse and print out the path and it's distance from s to vertex. Ex: reverseStr(E >- D >- A) = A -> D -> E
				path = reverseStr(path);
				cout << path << " : " << vertex.second.getDist() << endl;
			}
		}
	}

	// reverses a string s
	string reverseStr(string s) {
		// swap 2 character using XOR swap
		for (int i = 0; i < s.length() / 2; i++) {
			s[i] = s[i] ^ s[s.length() - i - 1];
			s[s.length() - i - 1] = s[i] ^ s[s.length() - i - 1];
			s[i] = s[i] ^ s[s.length() - i - 1];
		}
		return s;
	}

	

	// prints the vertex indegrees of the graph
	void vertexIndegrees() {
		// for every vertex v in the graph, print out v's name and v's indegree
		for (pair<char, Vertex> v : vertices)
			cout << v.first << " : " << v.second.getIndegree() << endl;
	}

	// perform a topological sort on the graph
	void topologicalSort() {
		// "verticesCopy" is a copy of the graph, "g" will be the queue of vertices, and "counter" will keep track of how many vertices are visited
		map<char, Vertex> verticesCopy = vertices;
		queue<Vertex> q;
		int counter = 0;

		// store all vertices of indegree 0 in the queue
		for (pair<char, Vertex> v : verticesCopy)
			if (v.second.getIndegree() == 0)
				q.push(v.second);

		while (!q.empty()) {
			// store and remove the next vertex to be processed
			Vertex v = q.front();
			q.pop();

			// if v is not the last vertex, print " -> "
			if(counter < vertices.size()-1) cout << v.getName() << " -> ";
			// otherwise, do not print " -> "
			else cout << v.getName() << endl;

			counter++;
			
			// for every vertex w adjacent to v
			map<char, int> adjList = v.getAdjList();
			for (pair<char, int> w : adjList) {
				// "vert" a copy of the current vertex w and "newIndegree" is the updated indegree
				Vertex vert = verticesCopy.at(w.first);
				int newIndegree = vert.getIndegree() - 1;
				verticesCopy.at(w.first).setIndegree(newIndegree);

				// if the newIndegree of w is 0, add it to the queue
				if (newIndegree == 0)
					q.push(verticesCopy.at(w.first));
			}
		}

		// if the number of nodes visited does not equal the number of vertices in the graph, the graph contains a cycle
		if (counter != vertices.size())
			cout << "Error: graph contains a cycle.\n";
	}

private:
	// "vertices" all of the graph information
	map<char, Vertex> vertices;
};
