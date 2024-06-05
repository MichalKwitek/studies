#include "Organism.h"
#include "World.h"
#include "Species.h"
#include "Animal.h"
#include "Plant.h"
#include "Wolf.h"
#include "Grass.h"
#include "Sheep.h"
#include "Antilope.h"
#include "Turtle.h"
#include "Fox.h"
#include "Dandelion.h"
#include "Guarana.h"
#include "Nightshade.h"
#include "Sosnowsky.h"

void Organism::draw() const{
	cout << sprite;
}

Coordinate Organism::FindSpace() const{
    Coordinate newCoord = coord;
    while (newCoord == coord)
    {
        int dir = rand() % 4;
        if (dir == North) {
            newCoord.y -= 1;
            if (newCoord.y < 0) {
                newCoord.y += 1;
            }
        }
        else if (dir == East) {
            newCoord.x += 1;
            if (newCoord.x >= world->getColumns()) {
                newCoord.x -= 1;
            }
        }
        else if (dir == South) {
            newCoord.y += 1;
            if (newCoord.y >= world->getRows()) {
                newCoord.y -= 1;
            }
        }
        else if (dir == West) {
            newCoord.x -= 1;
            if (newCoord.x < 0) {
                newCoord.x += 1;
            }
        }
    }
    return newCoord;
}

bool Organism::spaceIsViable(Coordinate& coord) const {
    if (coord.x < 0 || coord.y < 0 || coord.x >= world->getColumns() || coord.y >= world->getRows()) {
        return false;
    }
    Organism* org = world->findOrganismByCoordinate(coord);
    if (org != nullptr)
        return false;
    return true; // No Organism with the specified coordinates found
}

Coordinate Organism::FindVoidSpace(Coordinate coord) const { // w przypadku gdy nie ma wolnego pola, funkcja zwraca niezmieniony koordynat
    Coordinate newCoord = coord;
    bool nClear = true, eClear = true, wClear = true, sClear = true;
    while (nClear || eClear || wClear || sClear) {
        int dir = rand() % 4;
        if (dir == North && nClear == true) {
            newCoord.y -= 1;
            if (spaceIsViable(newCoord)) {
                return newCoord;
            }
            else {
                newCoord.y += 1;
                nClear = false;
                continue;
            }
        }
        if (dir == East && eClear == true) {
            newCoord.x += 1;
            if (spaceIsViable(newCoord)) {
                return newCoord;
            }
            else {
                newCoord.x -= 1;
                eClear = false;
                continue;
            }
        }
        if (dir == South && sClear == true) {
            newCoord.y += 1;
            if (spaceIsViable(newCoord)) {
                return newCoord;
            }
            else {
                newCoord.y -= 1;
                sClear = false;
                continue;
            }
        }
        if (dir == West && wClear == true) {
            newCoord.x -= 1;
            if (spaceIsViable(newCoord)) {
                return newCoord;
            }
            else {
                newCoord.x += 1;
                wClear = false;
                continue;
            }
        }
    }
    return coord;
}

void Organism::endTurn() {
    age += 1;
}

// ustawianie indkesowania talbicy speciesCounter
int Organism::getIndex() const {
    switch (getSprite()) {
    case 'W':
        return W;
    case 'S':
        return S;
    case 'A':
        return A;
    case 'T':
        return T;
    case 'F':
        return F;
    case 'g':
        return g;
    case 'd':
        return d;
    case 'x':
        return x;
    case 'n':
        return n;
    case 's':
        return s;
    }
}

Organism* Organism::multiply(Organism* org, Coordinate coord) {
    Organism* newborn = nullptr;
    switch (org->getSprite()) {
    case 'W':
        newborn = new Wolf(org->world, coord);
        break;
    case 'S':
        newborn = new Sheep(org->world, coord);
        break;
    case 'A':
        newborn = new Antilope(org->world, coord);
        break;
    case 'T':
        newborn = new Turtle(org->world, coord);
        break;
    case 'F':
        newborn = new Fox(org->world, coord);
        break;
    case 'g':
        newborn = new Grass(org->world, coord);
        break;
    case 'd':
        newborn = new Dandelion(org->world, coord);
        break;
    case 'x':
        newborn = new Guarana(org->world, coord);
        break;
    case 'n':
        newborn = new Nightshade(org->world, coord);
        break;
    case 's':
        newborn = new Sosnowsky(org->world, coord);
        break;
    }
    newborn->setAge(-1);
    return newborn;
}

void Organism::kill() {
    dead = true;
    Coordinate negative;
    negative.x = -1;
    negative.y = -1;
    setCoord(negative);
}

int Organism::getInitiative() const {
    return initiative;
}

int Organism::getStrength() const {
    return strength;
}

void Organism::setStrength(int s) {
    strength = s;
}

int Organism::getAge() const {
    return age;
}

void Organism::setAge(int a) {
    age = a;
}

void Organism::setInitiative(int initiative) {
    initiative = initiative;
}

int Organism::getID() const {
    return id;
}

void Organism::setID(int index) {
    id = index;
}

string Organism::getSpecies() const {
    return species;
}

char Organism::getSprite() const {
    return sprite;
}

bool Organism::isDead() const {
    return dead;
}

Coordinate Organism::getCoord() const {
    return coord;
}

void Organism::setCoord(Coordinate c) {
    coord = c;
}

int Organism::getXCoord() const {
    return coord.x;
}

int Organism::getYCoord() const {
    return coord.y;
}

bool Organism::ranAway(Organism* attacker) {
    return false;
}

bool Organism::hasDeflectedAttack(Organism* attacker) {
    return false;
}

bool Organism::hasIncreasedStrength(Organism* attacker) {
    cout << endl;
    return false;
}

bool Organism::isPoisonous(Organism* attacker) {
    return false;
}