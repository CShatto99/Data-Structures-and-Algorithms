#include "vertex.h"
Vertex::Vertex(char name, int dist, char path, int indegree) {
	setName(name);
	setKnown(false);
	setDist(dist);
	setPath(path);
	setIndegree(indegree);
}

// Vertex setter implementations
void Vertex::setName(char n) { name = n; }
void Vertex::setAdjList(map<char, int> l) { adj = l; }
void Vertex::setKnown(bool k) { known = k; }
void Vertex::setDist(int d) { dist = d; }
void Vertex::setPath(char p) { path = p; }
void Vertex::setIndegree(int in) { indegree = in; }

// Vertex getter implementations
char Vertex::getName() { return name; }
map<char, int> Vertex::getAdjList() { return adj; }
bool Vertex::getKnown() { return known; }
int Vertex::getDist() { return dist; }
char Vertex::getPath() { return path; }
int Vertex::getIndegree() { return indegree; }
