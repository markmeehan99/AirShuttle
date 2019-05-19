#pragma once

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"
#include "Vertex.h"

using namespace std;

#define INF std::numeric_limits<double>::max()


class Graph {
	vector<Vertex *> vertexSet;    // vertex set

public:
	Vertex *findVertex(const int &in) const;
	bool addVertex(const int &in);
	bool addEdge(const int &sourc, const int &dest, double w);
	int getNumVertex() const;
	vector<Vertex *> getVertexSet() const;

	// Fp05 - single source
	void dijkstraShortestPath(const int &s);
	void dijkstraShortestPathOld(const int &s);
	void unweightedShortestPath(const int &s);
	void bellmanFordShortestPath(const int &s);
	vector<int> getPath(const int &origin, const int &dest) const;

	// Fp05 - all pairs
	void floydWarshallShortestPath();
	vector<int> getfloydWarshallPath(const int &origin, const int &dest) const;

};


int Graph::getNumVertex() const {
	return vertexSet.size();
}


vector<Vertex *> Graph::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */

Vertex * Graph::findVertex(const int &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */

bool Graph::addVertex(const int &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */

bool Graph::addEdge(const int &sourc, const int &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/


void Graph::dijkstraShortestPath(const int &origin) {
	// TODO
}


vector<int> Graph::getPath(const int &origin, const int &dest) const{
	vector<int> res;
	// TODO
	return res;
}


void Graph::unweightedShortestPath(const int &orig) {
	// TODO
}


void Graph::bellmanFordShortestPath(const int &orig) {
	// TODO
}


/**************** All Pairs Shortest Path  ***************/

void Graph::floydWarshallShortestPath() {
	// TODO
}


vector<int> Graph ::getfloydWarshallPath(const int &orig, const int &dest) const{
	vector<int> res;
	// TODO
	return res;
}

