#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Graph.h"

void exercicio1();
void exercicio2();
void exercicio3();


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
	file.open("T06_nodes_X_Y_Maia.txt");

	if(!file.is_open()) {
		cout << "nos.txt nao abriu\n";
		return;
	}


	// (id, x, y) -> line
	// first line needs to be read
	string line;
	int counter = 1;
	int id, x, y;
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
		else cout << "Added vertex " << counter << endl;

		counter ++;
	}

	file.close();

	file.open("arestas.txt");

	if(!file.is_open()) {
		cout << "arestas.txt nao abriu\n";
		return;
	}
	else cout << "arestas.txt abriu\n";

	// first line needs to be read

	// (srcNode, destNode) -> line
	while(getline(file, line)) {
		istringstream ss(line);
		int idSrc, idDest;
		char garbageChar;
		ss >> garbageChar;	// '('
		ss >> idSrc;		// src
		ss >> garbageChar;	// ','
		ss >> idDest;		// dest

		// Node src = graph.find(idSrc);
		// Node dest = graph.find(idDest);

		// Edge *edge = new Edge(src, dest);
		// src.addEdge(*edge);
		// graph.addEdge(*edge);
	}
	file.close();
}

int main() {

	GraphViewer *gv = new GraphViewer(50, 50, true);
	gv->createWindow(600, 600);

	Graph *graph = new Graph();

	importTest(graph);

	for (auto v: graph->getVertexSet()) {
		gv->addNode(v->getInfo());
	}

	gv->rearrange();

	getchar();
	return 0;
}
