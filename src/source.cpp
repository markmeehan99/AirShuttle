#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Graph.h"
#include <map>

void exercicio1();
void exercicio2();
void exercicio3();

#define PORTO_NODES "T06_nodes_X_Y_Porto.txt"
#define MAIA_NODES "T06_nodes_X_Y_Maia.txt"
#define PORTO_EDGES "T06_edges_Porto.txt"
#define MAIA_EDGES "T06_edges_Maia.txt"
#define PORTO_HOTELS "T06_hotels_Porto.txt"
#define MAIA_HOTELS "T06_hotels_Maia.txt"

map<string,int> hotels;

struct struct_loaded {
	bool mapPorto = false;
	bool mapMaia = false;
	bool hotelsPorto = false;
	bool hotelsMaia = false;
} loaded;

enum cityOptions{ PORTO, MAIA };

void displayHotels() {
	for(auto h: hotels) {
		cout << h.first << " -> "<< h.second << endl;
	}
}

void loadHotels(string city) {
	ifstream file;
	string line;
	string hotelName;
	int id;
	char garbageChar;

	if (city == "Porto") {
		file.open(PORTO_HOTELS);

		if(!file.is_open()) {
			cout << "Porto hotels file did not open.\n";
			return;
		}

		cout << "Loading hotels...\n";

		while(getline(file, line)) {
			istringstream ss(line);
			string token;

			int pos = line.find(',');

			line.substr(1);
			line.replace(0,1,"");

			hotelName = line.substr(0, pos-1); //hotelName

		    line.erase(0, pos + 1);
		    id = stoi(line.substr(0, pos)); //id


			hotels.insert(pair<string, int>(hotelName, id));
		}

		loaded.hotelsPorto = true;
	}
	else if (city == "Maia") {
		file.open(MAIA_HOTELS);

		if(!file.is_open()) {
			cout << "Maia hotels file did not open.\n";
			return;
		}

		cout << "Loading hotels...\n";

		while(getline(file, line)) {

			istringstream ss(line);
			string token;

			int pos = line.find(',');

			line.substr(1);
			line.replace(0,1,"");

			hotelName = line.substr(0, pos-1); //hotelName

		    line.erase(0, pos + 1);
		    id = stoi(line.substr(0, pos)); //id


			hotels.insert(pair<string, int>(hotelName, id));
		}

		loaded.hotelsMaia = true;
	}
}


void loadMap(Graph *graph, string city) {
	ifstream file;

	if (city == "Porto")
		file.open(PORTO_NODES);
	else if (city == "Maia")
		file.open(MAIA_NODES);
	else {
		cout << "We do not operate in that city.\n";
		return;
	}

	if(!file.is_open()) {
		cout << city << " node file did not open\n";
		return;
	}

	// first line needs to be read
	string line;
	int counter = 1;
	int id;
	double x, y;
	char garbageChar;

	getline(file, line); //Gets number os nodes, discards it

	int startingX, startingY;

	cout << "Loading map...\n";

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

		counter ++;
	}

	file.close();

	if (city == "Porto")
		file.open(PORTO_EDGES);
	else if (city == "Maia")
		file.open(MAIA_EDGES);
	else {
		cout << "We do not operate in that city.\n";
		return;
	}

	if(!file.is_open()) {
		cout << city << " edge file did not open\n";
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

	loaded.mapPorto = true;
}

void displayMap(Graph *graph, GraphViewer *gv) {

	int edgeCounter = 0;

	for (auto v: graph->getVertexSet()) {
		gv->addNode(v->getInfo(), v->getX(), v->getY());
		gv->setVertexLabel(v->getInfo(), ".");
		//gv->rearrange();

		for (auto e: v->getAdj()) {
			gv->addEdge(edgeCounter, v->getInfo(), e.getDest()->getInfo(), 0);
			edgeCounter++;
			//cout << "Added edge " << edgeCounter << endl;
		}
	}

	for (auto h: hotels) {
		gv->setVertexColor(h.second, "RED");
		gv->setVertexLabel(h.second, h.first);
		gv->rearrange();
	}

	gv->rearrange();
}

void mainMenu() {
	cout << "*******************************************************************" << endl;
	cout << "Welcome to AirShuttle! Please select the city you wish to travel to" << endl;
	cout << "1 - Porto" << endl;
	cout << "2 - Maia" << endl;


}


int menu() {
	cout << "*************************************************" << endl;
	cout << "What would you like to do" << endl;
	cout << "1 - View Map" << endl;
	cout << "2 - View Hotels" << endl;
	cout << "3 - Exit" << endl;
	cout << "*************************************************" << endl;

	int option;

	cin >> option;

	return option;
}


int main() {

	Graph *graph = new Graph();

	bool quit = false;

	string city = "Porto";

	while(!quit) {
		switch (menu()) {
		case 1:
			loadHotels(city);
			loadMap(graph, city);
			displayMap(graph, graph->gv);
			break;
		case 2:
			displayHotels();
			break;
		case 3:
			quit = true;
			break;
		default:
			break;
		}
	}

	graph->gv->closeWindow();
	return 0;
}


