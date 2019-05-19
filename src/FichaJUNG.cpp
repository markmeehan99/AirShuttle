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
	GraphViewer *gv = new GraphViewer(50, 50, false);
	gv->createWindow(600,600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	gv->addNode(0, 0, 0);
	gv->addNode(1, 1, 1);
	gv->addNode(2, 2, 2);
	gv->addNode(3, 3, 3);
	gv->addEdge(0, 0, 1, 1);
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
