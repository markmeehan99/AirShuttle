#pragma once

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <algorithm>    // std::reverse
#include "MutablePriorityQueue.h"
#include "Vertex.h"
#include "graphviewer.h"

using namespace std;

#define INF std::numeric_limits<double>::max()


class Graph {
	vector<Vertex *> vertexSet;    // vertex set

public:
	GraphViewer *gv;
	Graph();
	Vertex *findVertex(int in) const;
	bool addVertex(const int &in);
	bool addVertex(const int &in, int x, int y);
	bool addEdge(const int &sourc, const int &dest, double w);
	int getNumVertex() const;
	vector<Vertex *> getVertexSet() const;

	Vertex * initSingleSource(const int &origin);
	bool relax(Vertex *v, Vertex *w, double weight);


	// Fp05 - single source
	void dijkstraShortestPath(int s, int d);
	void dijkstraShortestPathOld(const int &s);
	void unweightedShortestPath(const int &s);
	void bellmanFordShortestPath(const int &s);
	vector<int> getPath(const int &origin, const int &dest) const;

	// Fp05 - all pairs
	void floydWarshallShortestPath();
	vector<int> getfloydWarshallPath(const int &origin, const int &dest) const;

};

Graph::Graph() {
	this->vertexSet = {};
	gv = new GraphViewer(50, 50, false);
	gv->defineEdgeCurved(false);
	gv->createWindow(600, 600);
}


int Graph::getNumVertex() const {
	return vertexSet.size();
}


vector<Vertex *> Graph::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */

Vertex * Graph::findVertex(int in) const {
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

bool Graph::addVertex(const int &in, int x, int y) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex(in, x, y));
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

Vertex * Graph::initSingleSource(const int &origin) {
	for (auto v : vertexSet) {
		v->dist = INF;
		v->path = nullptr;
	}
	auto s = findVertex(origin);
	s->dist = 0;
	return s;
}

bool Graph::relax(Vertex *v, Vertex *w, double weight) {
	if (v->dist + weight < w->dist) {
		w->dist = v->dist + weight;
		w->path = v;
		return true;
	}
	else return false;
}


/**************** Single Source Shortest Path algorithms ************/


void Graph::dijkstraShortestPath(int origin, int dest) {

	auto startNode = initSingleSource(origin);
	auto endNode = findVertex(dest);

	MutablePriorityQueue q;
	q.insert(startNode);

	while ( ! q.empty() ) {
		auto v = q.extractMin();

		for (auto e : v->adj) {
			auto oldDist = e.dest->dist;

			if (v == endNode) {
				cout << "Found destination!" << endl;
				break;
			}

			if (relax(v, e.dest, e.weight)) {
				if (oldDist == INF) {
					q.insert(e.dest);
				}
				else {
					q.decreaseKey(e.dest);
				}
			}
		}
	}
}


vector<int> Graph::getPath(const int &origin, const int &dest) const{

	vector<int> res;
	auto v = findVertex(dest);
	if (v == nullptr || v->dist == INF) // missing or disconnected
	{
		cout << "Nulo\n";
		return res;
	}
	for ( ; v != nullptr; v = v->path)
		res.push_back(v->info);
	reverse(res.begin(), res.end());
	return res;

}


void Graph::unweightedShortestPath(const int &orig) {
	auto s = initSingleSource(orig);
	queue< Vertex* > q;
	q.push(s);
	while( ! q.empty() ) {
		auto v = q.front();
		q.pop();
		for(auto e: v->adj)
			if (relax(v, e.dest, 1))
				q.push(e.dest);
	}
}


void Graph::bellmanFordShortestPath(const int &orig) {
	initSingleSource(orig);
	for (unsigned i = 1; i < vertexSet.size(); i++)
		for (auto v: vertexSet)
			for (auto e: v->adj)
				relax(v, e.dest, e.weight);
	for (auto v: vertexSet)
		for (auto e: v->adj)
			if (relax(v, e.dest, e.weight))
				cout << "Negative cycle!" << endl;
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

