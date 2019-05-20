#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>

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

void importTest() {
	ifstream file;
	file.open("nos.txt");
	if(!file.is_open()) {
		cout << "nos.txt nao abriu\n";
		return;
	}
	else cout << "nos.txt abriu\n";

	// first line needs to be read

	// (id, x, y) -> line
	string line;
	while(getline(file, line)) {
		istringstream ss(line);
		int id, x, y;
		char garbageChar;
		ss >> garbageChar; 	// '('
		ss >> id; 			// id
		ss >> garbageChar;	// ','
		ss >> x;			// x
		ss >> garbageChar;	// ','
		ss >> y;			// y

		//graph.addNode(new Node(id, x, y);
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
	string line;
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
	exercicio1();
	//exercicio2();
	//exercicio3();

	//importTest();
	getchar();
	return 0;
}
