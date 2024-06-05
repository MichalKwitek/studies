#include "Antilope.h"
#include "World.h"
Antilope::Antilope(World* w, Coordinate c) {
    strength = 4;
    initiative = 4;
    species = "Antilope";
    sprite = 'A';
    age = 0;
    world = w;
    coord = c;
    dead = false;
    w->addOrganism(this);
}

Antilope::Antilope(World* w, Coordinate c, int s, int a) {
    strength = s;
    initiative = 4;
    species = "Antilope";
    sprite = 'A';
    age = a;
    world = w;
    coord = c;
    dead = false;
    w->addOrganism(this);
}

void Antilope::action() {
    Coordinate oldCoord = getCoord();
    Coordinate newCoord = oldCoord;
    while (newCoord == oldCoord)
    {
        int dir = (rand() % 4);
        if (dir == North) {
            newCoord.y -= 2;
            if (newCoord.y < 0) {
                newCoord.y += 2;
            }
        }
        else if (dir == East) {
            newCoord.x += 2;
            if (newCoord.x >= world->getColumns()) {
                newCoord.x -= 2;
            }
        }
        else if (dir == South) {
            newCoord.y += 2;
            if (newCoord.y >= world->getRows()) {
                newCoord.y -= 2;
            }
        }
        else if (dir == West) {
            newCoord.x -= 2;
            if (newCoord.x < 0) {
                newCoord.x += 2;
            }
        }
    }
    Organism* opponent = world->findOrganismByCoordinate(newCoord);
    cout << getSpecies() << getID() << " przechodzi z pola " << oldCoord << " na pole " << newCoord << endl;
    if (opponent == nullptr)
    {
        cout << endl;
        setCoord(newCoord);
    }
    else
        collision(this, opponent);
}

bool Antilope::ranAway(Organism* attacker) {
    int runRoll = rand() % 100;
    if (runRoll < RUN_CHANCE) {
        Coordinate newCoord = FindVoidSpace(getCoord()); // wybranie miejsca ucieczki
        if (newCoord != getCoord())
        {
            attacker->setCoord(getCoord());
            cout << getSpecies() << getID() << " uciekla przed " << attacker->getSpecies() << attacker->getID() << " z pola " << getCoord() << " na pole " << newCoord << endl << endl;
            setCoord(newCoord);
            return true;
        }
        else {
            cout << getSpecies() << getID() << "Nie moze uciec - brak pustego miejsca w poblizu" << endl;
            return false;
        }
    }
    else return false;
}

void Antilope::draw() const {
    cout << YELLOW << getSprite() << RESET;
}