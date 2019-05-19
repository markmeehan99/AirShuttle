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


int main() {
	exercicio1();
	//exercicio2();
	//exercicio3();
	getchar();
	return 0;
}
