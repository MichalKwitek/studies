#pragma once
#include "Animal.h"
class Sheep :
    public Animal
{
public:
    Sheep(World* world, Coordinate coord);
    Sheep(World* world, Coordinate coord, int strength, int age);
private:
};

