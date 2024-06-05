#include "Grass.h"
#include "World.h"
Grass::Grass(World* w, Coordinate c) {
	strength = 0;
	initiative = 0;
	species = "Grass";
	sprite = 'g';
	age = 0;
	world = w;
	coord = c;
	dead = false;
	w->addOrganism(this);
}

Grass::Grass(World* w, Coordinate c, int s, int a) {
	strength = s;
	initiative = 0;
	species = "Grass";
	sprite = 'g';
	age = a;
	world = w;
	coord = c;
	dead = false;
	w->addOrganism(this);
}
