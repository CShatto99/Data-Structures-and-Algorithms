/*
	Name: Cameron Shatto
	Course Section: CSCE 3110.021
	Date: 6/21/2020
	Description: This program implements a weighted directed  graph data structure that is capable of printing the adjacency list of the graph, 
	finding the shortest path in the graph, printing the vertex indegrees of the graph, and performing a topological sort on the graph
*/

//#include "stdafx.h"
#include "graph.h"
#include <fstream>

using namespace std;

// name dist path indegree
int main() {
	
	// "vertices" stores all unique Vertex objects.
	map<char, Vertex> vertices;
	// "fileName" is the input file, "line" stores the current line being read from fileName, and "option" stores the user menu option
	string fileName, line, option;

	// get the input file name and create the ifstream object
	cout << "Enter the name of the input file: ";
	cin >> fileName;
	ifstream file (fileName);

	// if the file exists
	if (file.is_open()) {
		// while the end of file is not reached
		while (getline(file, line)) {
			// if the vertex (line[0]) is not in the map, add it to the map
			if (vertices.count(line[0]) == 0) {
				Vertex v{ line[0], INT32_MAX, ' ', 0 };
				vertices.insert(pair<char, Vertex>(line[0], v));
			}

			// "adjList" holds the vertices that are adjacent to Vertex v
			map<char, int> adjList;

			// while there are still chars left to parse in the current file line
			int i = 2;
			while (i < line.size()) {
				// if the current char is 0-9 and the next char is a-z or A-Z
				if (isdigit(line[i]) && isalpha(line[i + 2])) {
					// if the vertex is already in the map
					if (vertices.count(line[i + 2]) > 0) {
						// save a copy of the vertex and remove it from the map
						Vertex v = vertices.at(line[i + 2]);
						vertices.erase(v.getName());

						// increment the vertex's indegree, increase the vertex's distance, and insert it back into the map
						v.setIndegree(v.getIndegree() + 1);
						v.setDist(v.getDist() + line[i] - '0');
						vertices.insert(pair<char, Vertex>(v.getName(), v));
					}
					// otherwise the vertex is not in the map
					else {
						// create a new vertex object and insert it into the map
						Vertex v{ line[i + 2], line[i]-'0', line[0], 1 };
						vertices.insert(pair<char, Vertex>(line[i + 2], v));
					}
					
					// insert the adjacent vertex into the adjacency list
					adjList.insert(pair<char, int>(line[i + 2], line[i] - '0'));
					
					// move the index to the next adjacent vertex
					i += 4;
				}
			}

			// if the vertex (line[0]) is in the map
			if (vertices.count(line[0]) > 0) {
				// save a copy of the vertex and remove it from the map
				Vertex v = vertices.at(line[0]);
				vertices.erase(line[0]);

				// update the adjacency list of v and insert v back into the map
				v.setAdjList(adjList);
				vertices.insert(pair<char, Vertex>(line[0], v));
			}
		}
		file.close();
		cout << "File " << fileName << " successfully loaded into graph.\n";
	}
	// the input file failed to open
	else {
		cout << "File " << fileName << " UNsuccessfully loaded into graph.\n";
		return -1; 
	}

	// insert the vertices map into an instance of the Graph class
	Graph g{ vertices };
		
	while (1) {
		// print the user menu while the user selects an incorrect option
		do {
			cout << "Enter option choice 1 - 5:\n";
			cout << "(1) Print Adjacency List\n";
			cout << "(2) Print Single-Source Shortest Path\n";
			cout << "(3) Print Indegree of Each Vertex\n";
			cout << "(4) Print Topological Sort of Graph\n";
			cout << "(5) Exit Program\n";
			cin >> option;
		} while (option[0] < '1' || option[0] > '5');

		// print the adjacency list of the graph
		if (option[0] == '1') {
			cout << "Adjacency List:\n";
			g.printAdjList();
		}
		// print the single-source shortest path
		else if (option[0] == '2') {
			string vertex;
			do {
				cout << "Enter Source Vertex (char) for Shortest Path: ";
				cin >> vertex;
			} while (vertices.count(vertex[0]) == 0);

			cout << "Single-Source Shortest Path from " << vertex[0] << ":\n";
			g.shortestPath(vertices.at(vertex[0]));
		}
		// print the indegree of each vertex in the graph
		else if (option[0] == '3') {
			cout << "Indegree of Each Vertex:\n";
			g.vertexIndegrees();
		}
		// print the topological sort of the graph
		else if (option[0] == '4') {
			cout << "Topological Sort of Graph:\n";
			g.topologicalSort();
		}
		// terminate the program
		else {
			cout << "Terminating Program...\n";
			return 0;
		}
	}
    return 0;
}
