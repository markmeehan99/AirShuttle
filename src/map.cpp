#include "map.h"

Map::Map() {
	this->gv = new GraphViewer(50, 50, true);
	this->gv->createWindow(600, 600);
}
