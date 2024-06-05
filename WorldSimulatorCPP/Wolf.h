#pragma once
#include "Animal.h"
class Wolf :
    public Animal
{
public:
    Wolf(World* world, Coordinate coord);
    Wolf(World* world, Coordinate coord, int strength, int age);
    void draw() const override;
};

