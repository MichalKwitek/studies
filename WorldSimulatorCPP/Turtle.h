#pragma once
#include "Animal.h"
#define DEFLECT_STRENGTH 5
#define MOVE_CHANCE 25
class Turtle :
    public Animal
{
public:
    Turtle(World* world, Coordinate coord);
    Turtle(World* world, Coordinate coord, int strength, int age);
    void action() override;
private:
    void draw() const override;
    bool hasDeflectedAttack(Organism* attacker) override;
};

