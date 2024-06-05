#pragma once
#include "Animal.h"
#define RUN_CHANCE 50
class Antilope :
    public Animal
{
public:
    Antilope(World* world, Coordinate coord);
    Antilope(World* world, Coordinate coord, int strength, int age);
    void action() override;
private:
    void draw() const override;
    bool ranAway(Organism* attacker) override;
};

