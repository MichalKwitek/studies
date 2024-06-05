#include "Sosnowsky.h"
#include "World.h"
Sosnowsky::Sosnowsky(World* w, Coordinate c) {
	strength = 10;
	initiative = 0;
	species = "Sosnowsky";
	sprite = 's';
	age = 0;
	world = w;
	coord = c;
	dead = false;
	w->addOrganism(this);
}

Sosnowsky::Sosnowsky(World* w, Coordinate c, int s, int a) {
	strength = s;
	initiative = 0;
	species = "Sosnowsky";
	sprite = 's';
	age = a;
	world = w;
	coord = c;
	dead = false;
	w->addOrganism(this);
}

void Sosnowsky::action() {
	killAnimals();
	int growRoll = rand() % 100;
	if (growRoll <= GROW_CHANCE) {
		Coordinate newbornCoord = FindVoidSpace(getCoord());
		if (newbornCoord != getCoord()) {
			multiply(this, newbornCoord);
			cout << getSpecies() << getID() << " z pola " << getCoord() << " rozprzestrzenia sie na pole " << newbornCoord << endl << endl;
		}
		else cout << getSpecies() << getID() << " z pola " << getCoord() << " nie moze sie rozprzestrzenic - brak pustego miejsca w poblizu" << endl << endl;
	}
}

void Sosnowsky::killAnimals() {
	bool killed = false;
	Coordinate newCoord = getCoord();
	newCoord.x += 1;
	Organism* org = dynamic_cast<Animal*>(world->findOrganismByCoordinate(newCoord));
	if (org) {
		killed = true;
		cout << org->getSpecies() << org->getID() << " z pola " << org->getCoord() << " ginie zatruty przez " << this->getSpecies() << this->getID() << " z pola " << this->getCoord() << endl;
		org->kill();
	}
	newCoord.y -= 1;
	org = dynamic_cast<Animal*>(world->findOrganismByCoordinate(newCoord));
	if (org) {
		killed = true;
		cout << org->getSpecies() << org->getID() << " z pola " << org->getCoord() << " ginie zatruty przez " << this->getSpecies() << this->getID() << " z pola " << this->getCoord() << endl;
		org->kill();
	}
	newCoord.x -= 1;
	org = dynamic_cast<Animal*>(world->findOrganismByCoordinate(newCoord));
	if (org) {
		killed = true;
		cout << org->getSpecies() << org->getID() << " z pola " << org->getCoord() << " ginie zatruty przez " << this->getSpecies() << this->getID() << " z pola " << this->getCoord() << endl;
		org->kill();
	}
	newCoord.x -= 1;
	org = dynamic_cast<Animal*>(world->findOrganismByCoordinate(newCoord));
	if (org) {
		killed = true;
		cout << org->getSpecies() << org->getID() << " z pola " << org->getCoord() << " ginie zatruty przez " << this->getSpecies() << this->getID() << " z pola " << this->getCoord() << endl;
		org->kill();
	}
	newCoord.y += 1;
	org = dynamic_cast<Animal*>(world->findOrganismByCoordinate(newCoord));
	if (org) {
		killed = true;
		cout << org->getSpecies() << org->getID() << " z pola " << org->getCoord() << " ginie zatruty przez " << this->getSpecies() << this->getID() << " z pola " << this->getCoord() << endl;
		org->kill();
	}
	newCoord.y += 1;
	org = dynamic_cast<Animal*>(world->findOrganismByCoordinate(newCoord));
	if (org) {
		killed = true;
		cout << org->getSpecies() << org->getID() << " z pola " << org->getCoord() << " ginie zatruty przez " << this->getSpecies() << this->getID() << " z pola " << this->getCoord() << endl;
		org->kill();
	}
	newCoord.x += 1;
	org = dynamic_cast<Animal*>(world->findOrganismByCoordinate(newCoord));
	if (org) {
		killed = true;
		cout << org->getSpecies() << org->getID() << " z pola " << org->getCoord() << " ginie zatruty przez " << this->getSpecies() << this->getID() << " z pola " << this->getCoord() << endl;
		org->kill();
	}	
	newCoord.x += 1;
	org = dynamic_cast<Animal*>(world->findOrganismByCoordinate(newCoord));
	if (org) {
		killed = true;
		cout << org->getSpecies() << org->getID() << " z pola " << org->getCoord() << " ginie zatruty przez " << this->getSpecies() << this->getID() << " z pola " << this->getCoord() << endl;
		org->kill();
	}
	if(killed == true)
		cout << endl;
}

void Sosnowsky::draw() const {
	cout << GREEN_BCKG << getSprite() << RESET;
}