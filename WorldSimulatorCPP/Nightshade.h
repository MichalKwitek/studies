#pragma once
#include "Plant.h"
#include "Animal.h"
class Nightshade :
    public Plant
{
public:
    Nightshade();
    Nightshade(World* world, Coordinate coord);
    Nightshade(World* world, Coordinate coord, int strength, int age);
private:
    virtual void draw() const override;
    bool isPoisonous(Organism* attacker) override;
};

