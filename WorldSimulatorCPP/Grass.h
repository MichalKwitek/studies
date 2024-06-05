#pragma once
#include "Plant.h"
class Grass :
    public Plant
{
public:
    Grass(World* world, Coordinate coord);
    Grass(World* world, Coordinate coord, int strength, int age);
};

