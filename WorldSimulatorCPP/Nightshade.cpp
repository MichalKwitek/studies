#include "Nightshade.h"
#include "World.h"

Nightshade::Nightshade() {}

Nightshade::Nightshade(World* w, Coordinate c) {
	strength = 99;
	initiative = 0;
	species = "Nightshade";
	sprite = 'n';
	age = 0;
	world = w;
	coord = c;
	dead = false;
	w->addOrganism(this);
}

Nightshade::Nightshade(World* w, Coordinate c, int s, int a) {
	strength = s;
	initiative = 0;
	species = "Nightshade";
	sprite = 'n';
	age = a;
	world = w;
	coord = c;
	dead = false;
	w->addOrganism(this);
}

bool Nightshade::isPoisonous(Organism* attacker) {
	cout << attacker->getSpecies() << attacker->getID() << " zjada " << getSpecies() << getID() << " na polu " << getCoord() << " i umiera" << endl << endl;
	attacker->kill();
	return true;
}

void Nightshade::draw() const {
	cout << GREEN_BCKG << BLACK << getSprite() << RESET;
}