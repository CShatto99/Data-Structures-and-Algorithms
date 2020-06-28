#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <map>

using namespace std;

class Vertex {
public:
	Vertex(char name, int dist, char path, int indegree);

	// setters for each Vertex member variable
	void setName(char n);
	void setAdjList(map<char, int> l);
	void setKnown(bool k);
	void setDist(int d);
	void setPath(char p);
	void setIndegree(int in);

	// getters for each Vertex member variable
	char getName();
	map<char, int> getAdjList();
	bool getKnown();
	int getDist();
	char getPath();
	int getIndegree();

private:
	char name;
	map<char, int> adj;
	bool known;
	int dist;
	char path;
	int indegree;
};

#endif
