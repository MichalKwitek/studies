#include "Plant.h"
#include "World.h"
void Plant::action() {
	int growRoll = rand() % 100;
	if (growRoll <= GROW_CHANCE) {
		Coordinate newbornCoord = FindVoidSpace(getCoord());
		if (newbornCoord != getCoord()){
			multiply(this, newbornCoord);
			cout << getSpecies() << getID() << " z pola " << getCoord() << " rozprzestrzenia sie na pole " << newbornCoord << endl << endl;
		}
		else cout << getSpecies() << getID() << " z pola " << getCoord() << " nie moze sie rozprzestrzenic - brak pustego miejsca w poblizu" << endl << endl;
	}
}

void Plant::draw() const {
	cout << BRIGHT_GREEN << getSprite() << RESET;
}
