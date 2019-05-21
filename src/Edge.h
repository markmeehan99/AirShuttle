#pragma once

class Vertex;

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"
#include "Vertex.h"
#include "Graph.h"

using namespace std;

#define INF std::numeric_limits<double>::max()

class Edge {
	Vertex * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex *d, double w);
	friend class Graph;
	friend class Vertex;
	Vertex *getDest();
};


Edge::Edge(Vertex *d, double w): dest(d), weight(w) {}


Vertex *Edge::getDest() { return this->dest; }

