#include "Sheep.h"
#include "World.h"

Sheep::Sheep(World* w, Coordinate c) {
	strength = 4;
	initiative = 4;
	species = "Sheep";
	sprite = 'S';
	age = 0;
	world = w;
	coord = c;
	dead = false;
	w->addOrganism(this);
}

Sheep::Sheep(World* w, Coordinate c, int s, int a) {
	strength = s;
	initiative = 4;
	species = "Sheep";
	sprite = 'S';
	age = a;
	world = w;
	coord = c;
	dead = false;
	w->addOrganism(this);
}