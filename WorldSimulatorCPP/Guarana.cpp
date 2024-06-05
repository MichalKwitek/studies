#include "Guarana.h"
#include "World.h"

Guarana::Guarana(World* w, Coordinate c) {
	strength = 0;
	initiative = 0;
	species = "Guarana";
	sprite = 'x';
	age = 0;
	world = w;
	coord = c;
	dead = false;
	w->addOrganism(this);
}

Guarana::Guarana(World* w, Coordinate c, int s, int a) {
	strength = s;
	initiative = 0;
	species = "Guarana";
	sprite = 'x';
	age = a;
	world = w;
	coord = c;
	dead = false;
	w->addOrganism(this);
}

bool Guarana::hasIncreasedStrength(Organism* attacker) {
	attacker->setStrength(attacker->getStrength() + STRENGTH_INCREASE);
	cout << attacker -> getSpecies() << attacker->getID() << " zwieksza swoja sile o " << STRENGTH_INCREASE << endl << endl;
	return true;
}

void Guarana::draw() const {
	cout << GREEN_BCKG << RED << getSprite() << RESET;
}
