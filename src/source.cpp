#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <algorithm>    // std::sort
#include <sstream>
#include "Graph.h"
#include "user.h"
#include <map>
#include <cmath>

#define PORTO_NODES "T06_nodes_X_Y_Porto.txt"
#define MAIA_NODES "T06_nodes_X_Y_Maia.txt"
#define PORTO_EDGES "T06_edges_Porto.txt"
#define MAIA_EDGES "T06_edges_Maia.txt"
#define PORTO_HOTELS "T06_hotels_Porto.txt"
#define MAIA_HOTELS "T06_hotels_Maia.txt"

map<string, int> hotels;
string city = "Porto";
vector<int> paintGreen;
vector<User*> usersRequested;

struct struct_loaded
{
	bool mapPorto = false;
	bool mapMaia = false;
	bool hotelsPorto = false;
	bool hotelsMaia = false;
} loaded;

enum cityOptions
{
	PORTO,
	MAIA
};

vector<int> requests;

void displayRequests()
{
	for (auto r : usersRequested)
	{
		cout << r->getHotelId() << endl;
	}
}

int getHotelId(string hotel)
{
	for (auto h : hotels)
	{
		if (h.first == hotel)
			return h.second;
	}
	return 0;
}

void loadHotels()
{

	ifstream file;
	string line;
	string hotelName;
	int id;

	if (city == "Porto")
	{

		if (loaded.hotelsPorto)
		{
			return;
		}

		file.open(PORTO_HOTELS);

		if (!file.is_open())
		{
			cout << "Porto hotels file did not open.\n";
			return;
		}

		cout << "Loading hotels...\n";

		while (getline(file, line))
		{
			istringstream ss(line);
			string token;

			int pos = line.find(',');

			line.substr(1);
			line.replace(0, 1, "");

			hotelName = line.substr(0, pos - 1); //hotelName

			line.erase(0, pos + 1);
			id = stoi(line.substr(0, pos)); //id

			hotels.insert(pair<string, int>(hotelName, id));
		}

		loaded.hotelsPorto = true;
	}
	else if (city == "Maia")
	{

		if (loaded.hotelsMaia)
		{
			cout << "Maia hotels already loaded\n";
			return;
		}

		file.open(MAIA_HOTELS);

		if (!file.is_open())
		{
			cout << "Maia hotels file did not open.\n";
			return;
		}

		cout << "Loading hotels...\n";

		while (getline(file, line))
		{

			istringstream ss(line);
			string token;

			int pos = line.find(',');

			line.substr(1);
			line.replace(0, 1, "");

			hotelName = line.substr(0, pos - 1); //hotelName

			line.erase(0, pos + 1);
			id = stoi(line.substr(0, pos)); //id

			hotels.insert(pair<string, int>(hotelName, id));
		}
		loaded.hotelsMaia = true;
	}
	else
		cout << "We dont seem to operate in that city\n";
}

void displayHotels()
{
	loadHotels();
	loaded.hotelsPorto = true;
	for (auto h : hotels)
	{
		cout << h.first << " -> " << h.second << endl;
	}
}

void requestTrip()
{
	cout << "What hotel would you like to travel to?\n";
	displayHotels();
	string hotel;
	int hotelId;
	int hour, minutes;

	getchar(); //eats \n left by previous menu option
	getline(cin, hotel);

	if ((hotelId = getHotelId(hotel)) == 0)
	{
		cout << "That hotel was not found!\n";
		return;
	}
	cout << "What time would you like to leave the airport? [HH MM]\n";
	cin >> hour >> minutes;


	usersRequested.push_back(new User(0, hour, minutes));
}

void loadMap(Graph *graph, string city)
{
	ifstream file;

	if ((city == "Porto" && loaded.mapPorto) || ((city == "Maia" && loaded.mapMaia)))
		return;

	if (city == "Porto")
		file.open(PORTO_NODES);
	else if (city == "Maia")
		file.open(MAIA_NODES);
	else
	{
		cout << "We do not operate in that city.\n";
		return;
	}

	if (!file.is_open())
	{
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

	while (getline(file, line))
	{
		istringstream ss(line);

		ss >> garbageChar; // '('
		ss >> id;		   // id
		ss >> garbageChar; // ','
		ss >> x;		   // x
		ss >> garbageChar; // ','
		ss >> y;		   // y

		if (counter == 1)
		{
			startingX = x;
			startingY = y;
		}

		if (!graph->addVertex(id, x - startingX, y - startingY))
			cout << "Could not add Vertex\n";

		counter++;
	}

	file.close();

	if (city == "Porto")
		file.open(PORTO_EDGES);
	else if (city == "Maia")
		file.open(MAIA_EDGES);
	else
	{
		cout << "We do not operate in that city.\n";
		return;
	}

	if (!file.is_open())
	{
		cout << city << " edge file did not open\n";
		return;
	}

	// first line needs to be read
	getline(file, line);

	// (srcNode, destNode) -> line
	while (getline(file, line))
	{
		istringstream ss(line);
		int idSrc, idDest;
		char garbageChar;
		ss >> garbageChar; // '('
		ss >> idSrc;	   // src
		ss >> garbageChar; // ','
		ss >> idDest;	  // dest

		Vertex *src = graph->findVertex(idSrc);
		Vertex *dest = graph->findVertex(idDest);

		double weight = (double)sqrt(
			(double)pow(src->getX() - dest->getX(), 2) +
			(double)pow(src->getY() - dest->getY(), 2));

		//Edge *edge1 = new Edge(dest, weight);
		graph->addEdge(src->getInfo(), dest->getInfo(), weight);
		graph->addEdge(dest->getInfo(), src->getInfo(), weight);
	}

	file.close();

	loaded.mapPorto = true;
}

void displayMap(Graph *graph)
{

	int edgeCounter = 0;

	for (auto v : graph->getVertexSet())
	{
		graph->gv->addNode(v->getInfo(), v->getX(), v->getY());
		graph->gv->setVertexLabel(v->getInfo(), ".");
		//gv->rearrange();

		for (auto e : v->getAdj())
		{
			graph->gv->addEdge(edgeCounter, v->getInfo(), e.getDest()->getInfo(), 0);
			edgeCounter++;
			//cout << "Added edge " << edgeCounter << endl;
		}
	}

	for (auto h : hotels)
	{
		graph->gv->setVertexColor(h.second, "RED");
		graph->gv->setVertexLabel(h.second, h.first);
		graph->gv->rearrange();
	}

	cout << "paintGreen size: " << paintGreen.size() << endl;

	for (auto cenas : paintGreen)
	{
		graph->gv->setVertexColor(cenas, "GREEN");
		graph->gv->rearrange();
	}

	//Calcular shortestPath entre Ibis e StarInn

	//graph->dijkstraShortestPath(474789325, 111447974);
	//vector<int> path = graph->getPath(474789325, 111447974);
	/*
	for (auto v: path) {
		graph->gv->setVertexColor(v, "GREEN");
	}
*/
	//gv->rearrange();
}

bool func(User *u1, User *u2) {
	return ((*u1) < (*u2));
}

vector<User*> choosePassangers() {
	vector<User*> aux;

	sort(usersRequested.begin(), usersRequested.end(), func);
	for (int i=0; i < 2; i++) {
		aux.push_back(usersRequested.at(i));
	}

	return aux;
}

User* findUser(int id, vector<User*> v) {
	for(auto u: v) {
		if(u->getHotelId() == id)
			return u;
	}
	return NULL;
}

void planTrip(Graph *graph)
{
	vector<User*> aux = choosePassangers();

	loadMap(graph, city);

	Vertex *airport = graph->findVertex(299611392);
	if (airport == NULL)
	{
		cout << "Could not find airport\n";
		return;
	}

	paintGreen = {};

	vector<double> distances;

	// first source is airport
	int src = airport->getInfo();

	while (!aux.empty())
	{
		// first "found" destination has a distance of infinite
		// int is the id, double is the distance
		pair<int, double> auxDest = make_pair(0, INF);

		for (auto h : aux)
		{
			cout << "ready to calculate\n";
			Vertex *dest = graph->findVertex(h->getHotelId());
			//calculates dijkstra from src to h (one of the requests)
			graph->dijkstraShortestPath(src, dest->getInfo());
			distances.push_back(dest->getDist());
			cout << "Calculated path to hotel " << h->getHotelId() << endl;
			if (dest->getDist() < auxDest.second)
				auxDest = make_pair(dest->getInfo(), dest->getDist());
		}

		// adding path to Vertexes to become GREEN
		vector<int> path = graph->getPath(src, auxDest.first);
		paintGreen.insert(paintGreen.end(), path.begin(), path.end());

		// removing the destination found from the vector
		aux.erase(find(aux.begin(), aux.end(), findUser(auxDest.first, aux)));

		// updating next src with this iterations' dest
		src = auxDest.first;
	}

	// the last path calculation, so the van can return
	graph->dijkstraShortestPath(src, airport->getInfo());
	vector<int> path = graph->getPath(src, airport->getInfo());
	paintGreen.insert(paintGreen.begin(), path.begin(), path.end());


	displayMap(graph);
}

void mainMenu()
{
	cout << "*******************************************************************" << endl;
	cout << "Welcome to AirShuttle! Please select the city you wish to travel to" << endl;
	cout << "1 - Porto" << endl;
	cout << "2 - Maia" << endl;
	cout << "-------------" << endl;
	cout << "3 - Exit program" << endl;
}

int menu()
{
	cout << "*************************************************" << endl;
	cout << "What would you like to do" << endl;
	cout << "1 - View Map" << endl;
	cout << "2 - View Hotels" << endl;
	cout << "3 - Request Trip" << endl;
	cout << "4 - View current requests" << endl;
	cout << "5 - Plan trip with current requests" << endl;
	cout << "6 - Exit" << endl;
	cout << "*************************************************" << endl;

	int option;

	cin >> option;

	return option;
}

int main()
{

	Graph *graph = new Graph();

	bool quit = false;

	while (!quit)
	{
		switch (menu())
		{
		case 1:
			loadHotels();
			loadMap(graph, city);
			displayMap(graph);
			break;
		case 2:
			displayHotels();
			break;
		case 3:
			requestTrip();
			break;
		case 4:
			displayRequests();
			break;
		case 5:
			planTrip(graph);
			break;
		case 6:
			quit = true;
			break;
		default:
			break;
		}
	}

	graph->gv->closeWindow();
	return 0;
}
