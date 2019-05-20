#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Graph.h"

void exercicio1();
void exercicio2();
void exercicio3();

#define PORTO_NODES "T06_nodes_X_Y_Porto.txt"
#define MAIA_NODES "T06_nodes_X_Y_Maia.txt"
#define PORTO_EDGES "T06_edges_Porto.txt"
#define MAIA_EDGES "T06_edges_Maia.txt"


void exercicio1()
{
	GraphViewer *gv = new GraphViewer(10, 10, true);
	gv->createWindow(600,600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");


	gv->addNode(0);
	gv->addNode(1);
	gv->addEdge(101, 0, 1, EdgeType::UNDIRECTED);
	gv->rearrange();
}

void exercicio2()
{

}

void exercicio3()
{

}

void importTest(Graph *graph) {
	ifstream file;
	file.open(PORTO_NODES);

	if(!file.is_open()) {
		cout << "nos.txt nao abriu\n";
		return;
	}


	// (id, x, y) -> line
	// first line needs to be read
	string line;
	int counter = 1;
	int id;
	double x, y;
	char garbageChar;

	getline(file, line); //Gets number os nodes, discards it

	int startingX, startingY;

	while(getline(file, line)) {
		istringstream ss(line);

		ss >> garbageChar; 	// '('
		ss >> id; 			// id
		ss >> garbageChar;	// ','
		ss >> x;			// x
		ss >> garbageChar;	// ','
		ss >> y;			// y

		if (counter == 1) {
			startingX = x;
			startingY = y;
		}

		if (!graph->addVertex(id, x - startingX, y - startingY)) cout << "Could not add Vertex\n";
		//else cout << "Added vertex " << counter << endl;

		counter ++;
	}

	file.close();

	file.open(PORTO_EDGES);

	if(!file.is_open()) {
		cout << "arestas.txt nao abriu\n";
		return;
	}

	// first line needs to be read
	getline(file, line);

	// (srcNode, destNode) -> line
	while(getline(file, line)) {
		istringstream ss(line);
		int idSrc, idDest;
		char garbageChar;
		ss >> garbageChar;	// '('
		ss >> idSrc;		// src
		ss >> garbageChar;	// ','
		ss >> idDest;		// dest

		Vertex *src = graph->findVertex(idSrc);
		Vertex *dest = graph->findVertex(idDest);

		Edge *edge = new Edge(dest, 0);
		graph->addEdge(src->getInfo(), dest->getInfo(), 0);

	}
	file.close();
}

int main() {

	GraphViewer *gv = new GraphViewer(50, 50, false);

	Graph *graph = new Graph();
	gv->createWindow(600, 600);

	int edgeCounter = 0;

	importTest(graph);

	for (auto v: graph->getVertexSet()) {
		gv->addNode(v->getInfo(), v->getX(), v->getY());
		gv->setVertexLabel(v->getInfo(), "");

		for (auto e: v->getAdj()) {
			gv->addEdge(edgeCounter, v->getInfo(), e.getDest()->getInfo(), 0);
			edgeCounter++;
			//cout << "Added edge " << edgeCounter << endl;
		}
	}

	gv->rearrange();

	getchar();
	return 0;
}
