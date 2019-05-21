#pragma once

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"
#include "Edge.h"

using namespace std;

#define INF std::numeric_limits<double>::max()


/************************* Vertex  **************************/

class Vertex {
	int info;   // contents
	double x;
	double y;
	bool isAirport;
	bool isHotel;
	vector<Edge> adj;  // outgoing edges
	bool visited;          // auxiliary field
	double dist = 0;
	Vertex *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool processing = false;
	void addEdge(Vertex *dest, double w);

public:
	Vertex(int in);
	Vertex(int in, int x, int y);
	vector<Edge> getAdj();
	double getX();
	double getY();
	bool getIsAirport();
	bool getIsHotel();
	void setIsAirport();
	void setIsHotel();
	bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue
	int getInfo() const;
	double getDist() const;
	Vertex *getPath() const;
	friend class Graph;
	friend class MutablePriorityQueue;
};


Vertex::Vertex(int in): info(in), isHotel(false), isAirport(false) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */


Vertex::Vertex(int in, int x, int y): info(in), x(x), y(y), isHotel(false), isAirport(false){}


double Vertex::getX() { return this->x; }

double Vertex::getY() { return this->y; }

bool Vertex::getIsAirport() { return this->isAirport; }

bool Vertex::getIsHotel() { return this->isHotel; }

void Vertex::setIsAirport() {
	this->isAirport = true;
}

void Vertex::setIsHotel() {
	this->isHotel = true;
}

vector<Edge> Vertex::getAdj() { return this->adj; }


void Vertex::addEdge(Vertex *d, double w) {
	adj.push_back(Edge(d, w));
}


bool Vertex::operator<(Vertex & vertex) const {
	return this->dist < vertex.dist;
}


int Vertex::getInfo() const {
	return this->info;
}


double Vertex::getDist() const {
	return this->dist;
}


Vertex *Vertex::getPath() const {
	return this->path;
}


