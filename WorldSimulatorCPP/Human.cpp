#include "Human.h"
#include "World.h"

Human::Human(World* w, Coordinate c) {
    superStrengthTimer = 0;
    strength = 5;
    initiative = 4;
    species = "Human";
    sprite = 'H';
    age = 0;
    world = w;
    coord = c;
    dead = false;
    w->addOrganism(this);
}

Human::Human(World* w, Coordinate c, int s, int a, int sst) {
    superStrengthTimer = sst;
    strength = s;
    initiative = 4;
    species = "Human";
    sprite = 'H';
    age = a;
    world = w;
    coord = c;
    dead = false;
    w->addOrganism(this);
}

bool Human::canMove(Coordinate c) const {
    if (c.x < 0 || c.y < 0 ||
        c.x >= world->getColumns() ||
        c.y >= world->getRows() ||
        c == this->coord) // to jest potrzebne do wejœcia w pêtlê
        return false;
    else
        return true;
}

void Human::action() {
    cout << "Wcisnij W S A D lub Spacje by aktywowac zdolnosc" << endl;
	Coordinate newCoord;
    do {
        newCoord = getCoord();
        int token = 0;
        switch ((token = _getch())) {
        case W_KEY:
            newCoord.y -= 1;
            break;
        case D_KEY:
            newCoord.x += 1;
            break;
        case S_KEY:
            newCoord.y += 1;
            break;
        case A_KEY:
            newCoord.x -= 1;
            break;
        case SPACE:
            activateSuperStrength();
            break;
        }
    } while (!canMove(newCoord));
    Organism* opponent = world->findOrganismByCoordinate(newCoord);
    cout << getSpecies() << " przechodzi z pola " << getCoord() << " na pole " << newCoord << endl;
    if (opponent == nullptr)
    {
        setCoord(newCoord);
        cout << endl;
    }
    else
        collision(this, opponent);
}

void Human::activateSuperStrength() {
    if (superStrengthTimer == 0) {
        superStrengthTimer = 5;
        cout << "Aktywowano zdolnosc specjalna" << endl;
        cout << getSpecies() << " zwieksza swoja sile z " << getStrength() << " do " << getStrength() + SUPER_STRENGTH_INCREASE << endl;
        setStrength(getStrength() + SUPER_STRENGTH_INCREASE);
    }
    else {
        cout << "Jeszcze nie mozna aktywowac zdolnosci specjalnej" << endl;
    }
}

void Human::draw() const {
    cout << CYAN << sprite << RESET;
}

void Human::endTurn() {
    age += 1;
    if (superStrengthTimer != 0) // dopóki zdolnoœæ jest aktywna nale¿y zmniejszyæ timer i si³ê o 1
    {
        cout << "Sila " << getSpecies() << " spada o 1 z " << getStrength() << " do " << getStrength() - 1 << endl;
        superStrengthTimer -= 1;
        strength -= 1;
    }
}

void Human::setSuperStrengthTimer(int timer) {
    superStrengthTimer = timer;
}

int Human::getSuperStrengthTimer() const {
    return superStrengthTimer;
}