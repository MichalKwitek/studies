#include "Fox.h"
#include "World.h"

Fox::Fox(World* w, Coordinate c) {
	strength = 3;
	initiative = 7;
	species = "Fox";
	sprite = 'F';
	age = 0;
	world = w;
	coord = c;
    dead = false;
    w->addOrganism(this);
}

Fox::Fox(World* w, Coordinate c, int s, int a) {
    strength = s;
    initiative = 7;
    species = "Fox";
    sprite = 'F';
    age = a;
    world = w;
    coord = c;
    dead = false;
    w->addOrganism(this);
}

void Fox::action() {
    Coordinate newCoord;
    Organism* opponent = nullptr;
    bool canMove = false;
    newCoord = FindSpace(); // wybierz s¹siednie pole
    opponent = world->findOrganismByCoordinate(newCoord);
    if (opponent != nullptr)
    {
        // jesli przeciwnik ma wy¿sz¹ si³ê i nie jest lisem (guarana zwiêksza si³ê) to trzeba wybraæ inne miejsce
        if ((opponent->getStrength() > getStrength()) && (opponent->getSpecies() != getSpecies()))
        {
            cout << "Dzieki dobremu wechowi " << getSpecies() << getID() << " z pola " << getCoord() << " unika niebezpieczenstwa ze strony " << opponent->getSpecies() << opponent->getID() << " na polu " << opponent->getCoord() << endl;
            newCoord = FindVoidSpace(getCoord());
            if (newCoord != getCoord()) {// check if there is any space left around - if not then fox cannot shun the opponent            
                canMove = true;
                opponent = world->findOrganismByCoordinate(newCoord);
            }
            else { // if there is no space left stay in the same place
                cout << getSpecies() << getID() << " pozostaje na polu " << getCoord() << " - brak miejsca niezajetego przez silniejszego przeciwnika" << endl << endl;
                return;
            }
        }
        else canMove = true;
    }
    else canMove = true;
    if (canMove)
        cout << getSpecies() << getID() << " przechodzi z pola " << getCoord() << " na pole " << newCoord << endl;
    if (opponent == nullptr)
    {
        cout << endl;
        setCoord(newCoord);
    }
    else
        collision(this, opponent);
}

bool Fox::spaceIsViable(Coordinate& coord) const {
    if (coord.x < 0 || coord.y < 0 || coord.x >= world->getColumns() || coord.y >= world->getRows()) {
        return false;
    }
    Organism* org = world->findOrganismByCoordinate(coord);
    // jesli przeciwnik ma wy¿sz¹ si³ê i nie jest lisem (guarana zwiêksza si³ê) to zwróæ false
    if (org != nullptr)
        if ((org->getStrength() > getStrength()) && (org->getSpecies() != getSpecies()))
            return false;
    return true; // No Organism with the specified coordinates found
}

//Coordinate Fox::checkSurroundings(Coordinate coord) { // w przypadku gdy nie ma s¹siedniego pola niezajêtego przez silniejszy organizm niebêd¹cy lisem, funkcja zwraca niezmieniony koordynat
//    Coordinate newCoord = coord;
//    bool nClear = true, eClear = true, wClear = true, sClear = true;
//    while (nClear || eClear || wClear || sClear) {
//        int dir = rand() % 4;
//        if (dir == North && nClear == true) {
//            newCoord.y -= 1;
//            if (spaceIsViable(newCoord)) {
//                return newCoord;
//            }
//            else {
//                newCoord.y += 1;
//                nClear = false;
//                continue;
//            }
//        }
//        if (dir == East && eClear == true) {
//            newCoord.x += 1;
//            if (spaceIsViable(newCoord)) {
//                return newCoord;
//            }
//            else {
//                newCoord.x -= 1;
//                eClear = false;
//                continue;
//            }
//        }
//        if (dir == South && sClear == true) {
//            newCoord.y += 1;
//            if (spaceIsViable(newCoord)) {
//                return newCoord;
//            }
//            else {
//                newCoord.y -= 1;
//                sClear = false;
//                continue;
//            }
//        }
//        if (dir == West && wClear == true) {
//            newCoord.x -= 1;
//            if (spaceIsViable(newCoord)) {
//                return newCoord;
//            }
//            else {
//                newCoord.x += 1;
//                wClear = false;
//                continue;
//            }
//        }
//    }
//    return coord;
//}

void Fox::draw() const {
    std::cout << ORANGE << getSprite() << RESET;
}