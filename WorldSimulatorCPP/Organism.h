#pragma once
#include "Directions.h"
#include "Coordinate.h"
#include <iostream>
#include <string>
#include <vector>
class World;

class Organism
{
protected:
	int id; // indeksowane od 0
	int strength;
	int initiative;
	int age;
	std::string species;
	char sprite;
	World* world;
	Coordinate coord;
	bool dead;
	virtual Organism* multiply(Organism* org, Coordinate coord);
public: 
	virtual void draw() const;
	virtual void action()=0;
	virtual void endTurn();
	virtual bool spaceIsViable(Coordinate& coord) const;
	Coordinate FindVoidSpace(Coordinate coord) const;
	Coordinate FindSpace() const;
	bool isDead() const;
	void kill();
	std::string getSpecies() const;
	char getSprite() const;
	Coordinate getCoord() const;
	int getXCoord() const;
	int getYCoord() const;
	int getInitiative() const;
	int getStrength() const;
	int getAge() const;
	int getID() const;
	int getIndex() const;
	void setID(int index);
	void setStrength(int s);
	void setCoord(Coordinate c);
	void setInitiative(int initiative);
	void setAge(int age);
	virtual bool ranAway(Organism* attacker);
	virtual bool hasDeflectedAttack(Organism* attacker);
	virtual bool hasIncreasedStrength(Organism* attacker);
	virtual bool isPoisonous(Organism* attacker);
};
