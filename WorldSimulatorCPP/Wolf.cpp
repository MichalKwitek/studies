#include "Wolf.h"
#include "World.h"
Wolf::Wolf(World* w, Coordinate c) {
	strength = 9;
	initiative = 5;
	species = "Wolf";
	sprite = 'W';
	age = 0;
	world = w;
	coord = c;
	dead = false;
	w->addOrganism(this);
}

Wolf::Wolf(World* w, Coordinate c, int s, int a) {
	strength = s;
	initiative = 5;
	species = "Wolf";
	sprite = 'W';
	age = a;
	world = w;
	coord = c;
	dead = false;
	w->addOrganism(this);
}

void Wolf::draw() const {
	std::cout << GRAY_BCKG << getSprite() << RESET;
}