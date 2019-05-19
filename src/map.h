#pragma once
#include "graphviewer.h"
#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include <vector>


class Map {
private:
	GraphViewer *gv;
	vector <Vertex> nodes;
	vector <Edge> edges;
public:
	Map();
};
