#pragma once
#include "Plant.h"
class Dandelion :
    public Plant
{
public:
    Dandelion(World* world, Coordinate coord);
    Dandelion(World* world, Coordinate coord, int strength, int age);
    void action() override;
private:
    void draw() const override;
};

