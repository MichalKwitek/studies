#include "Turtle.h"
#include "World.h"
Turtle::Turtle(World* w, Coordinate c) {
    strength = 2;
    initiative = 1;
    species = "Turtle";
    sprite = 'T';
    age = 0;
    world = w;
    coord = c;
    dead = false;
    w->addOrganism(this);
}

Turtle::Turtle(World* w, Coordinate c, int s, int a) {
    strength = s;
    initiative = 1;
    species = "Turtle";
    sprite = 'T';
    age = a;
    world = w;
    coord = c;
    dead = false;
    w->addOrganism(this);
}

void Turtle::action() {
    int movementRoll = rand() % 100;
    if (movementRoll > MOVE_CHANCE) {
        cout << getSpecies() << getID() << " pozostaje na polu " << getCoord() << endl << endl;
        return;
    }
    Coordinate newCoord = FindSpace();
    Organism* opponent = world->findOrganismByCoordinate(newCoord);
    cout << getSpecies() << getID() << " przechodzi z pola " << getCoord() << " na pole " << newCoord << endl;
    if (opponent == nullptr)
    {
        cout << endl;
        setCoord(newCoord);
    }
    else
        collision(this, opponent);
}

bool Turtle::hasDeflectedAttack(Organism* attacker) {
    if (attacker->getStrength() < DEFLECT_STRENGTH) {
        cout << getSpecies() << getID() << " odbija atak " << attacker->getSpecies() << attacker->getID() << " na polu " << getCoord() << endl;
        cout << attacker->getSpecies() << attacker->getID() << " wraca na pole " << attacker->getCoord() << endl << endl;
        return true;
    }
    else {
        return false;
    }
}

void Turtle::draw() const {
    cout << BRIGHT_BLUE << getSprite() << RESET;
}