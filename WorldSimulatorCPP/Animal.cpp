#include "Animal.h"
#include "World.h"
void Animal::action() {
    Coordinate newCoord = FindSpace();
    Organism* opponent = world->findOrganismByCoordinate(newCoord);
    cout << getSpecies() << getID() << " przechodzi z pola " << getCoord() << " na pole " << newCoord << endl;
    if (opponent == nullptr)
    {
        setCoord(newCoord);
        cout << endl;
    }
    else
        collision(this, opponent);
}

void Animal::collision(Animal* initiator, Organism* opponent) {
    cout << initiator->getSpecies() << initiator->getID() << " napotyka " << opponent->getSpecies() << opponent->getID() << " na polu " << opponent->getCoord() << endl;
    if (initiator->getSpecies() == opponent->getSpecies()) {
        Coordinate newbornCoord = FindVoidSpace(opponent->getCoord());
        if (newbornCoord != opponent->getCoord())
        {
            Organism* newborn = multiply(opponent, newbornCoord);
            cout << "Narodzilo sie nowe zwierze: " << newborn->getSpecies() << newborn->getID() << " na polu " << newbornCoord << endl;
        }
        else cout << "Nowe zwierze: " << getSpecies() << " nie moze sie narodzic - brak pustego miejsca w poblizu" << endl;
        cout << initiator->getSpecies() << initiator->getID() << " wraca na pole " << initiator->getCoord() << endl << endl;
    }
    else {
        fight(initiator, opponent);
    }
}

void Animal::fight(Animal* initiator, Organism* opponent) { // pamiêæ po walce zwalniania jest w world.cpp w funkcji wykonuj¹cej turê
    if (dynamic_cast<Animal*>(opponent)) { // gdy na nowym polu znajduje siê zwierze
        if (!opponent->ranAway(initiator) && !opponent->hasDeflectedAttack(initiator)) {
            if (initiator->getStrength() < opponent->getStrength()) {
                cout << "Walka: " << initiator->getSpecies() << initiator->getID() << " przegrywa z " << opponent->getSpecies() << opponent->getID() << endl << endl;
                initiator->kill(); // ustawianie flagi dead na true i zmienianie koordynatów na ujemne
            }
            else {
                cout << "Walka: " << initiator->getSpecies() << initiator->getID() << " pokonuje " << opponent->getSpecies() << opponent->getID() << endl << endl;
                initiator->setCoord(opponent->getCoord());
                opponent->kill(); // ustawianie flagi dead na true
            }
        }
    }
    else { // jeœli zwierze natrafi na roœlinê zjada j¹
        if (!opponent->isPoisonous(initiator)) {
            cout << initiator->getSpecies() << initiator->getID() << " zjada " << opponent->getSpecies() << opponent->getID() << " na polu " << opponent-> getCoord() << endl;
            opponent->hasIncreasedStrength(initiator);
            initiator->setCoord(opponent->getCoord());
            opponent->kill(); // ustawianie flagi dead na true
        }
    }
}




