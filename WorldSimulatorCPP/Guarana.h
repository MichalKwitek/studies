#pragma once
#include "Plant.h"
#include "Animal.h"
#define STRENGTH_INCREASE 3

class Guarana :
    public Plant
{
public:
    Guarana(World* world, Coordinate coord);
    Guarana(World* world, Coordinate coord, int strength, int age);
private:
    bool hasIncreasedStrength(Organism* attacker) override;
    void draw() const override;
};

