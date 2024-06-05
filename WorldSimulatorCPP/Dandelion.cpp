#include "Dandelion.h"
#include "World.h"
Dandelion::Dandelion(World* w, Coordinate c) {
	strength = 0;
	initiative = 0;
	species = "Dandelion";
	sprite = 'd';
	age = 0;
	world = w;
	coord = c;
	dead = false;
	w->addOrganism(this);
}

Dandelion::Dandelion(World* w, Coordinate c, int s, int a) {
	strength = s;
	initiative = 0;
	species = "Dandelion";
	sprite = 'd';
	age = a;
	world = w;
	coord = c;
	dead = false;
	w->addOrganism(this);
}

void Dandelion::action() {
	bool grew = false;
	int growTimes = 0;
	while (growTimes < 3) {
		int growRoll = rand() % 100;
		if (growRoll <= GROW_CHANCE) {
			grew = true;
			Coordinate newbornCoord = FindVoidSpace(getCoord());
			if (newbornCoord != getCoord()) {
				multiply(this, newbornCoord);
				cout << getSpecies() << getID() << " z pola " << getCoord() << " rozprzestrzenia sie na pole " << newbornCoord << endl;
			}
			else cout << getSpecies() << getID() << " z pola " << getCoord() << " nie moze sie rozprzestrzenic - brak pustego miejsca w poblizu" << endl;
		}
		growTimes++;
	}
	if (grew)
		cout << endl;
}

void Dandelion::draw() const{
	cout << BRIGHT_YELLOW << getSprite() << RESET;
}
