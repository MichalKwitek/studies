#pragma once
#include "Nightshade.h"
#include "Animal.h"
class Sosnowsky :
    public Nightshade
{
public:
    Sosnowsky(World* world, Coordinate coord);
    Sosnowsky(World* world, Coordinate coord, int strength, int age);
    void action() override;
private: 
    void draw() const override;
    void killAnimals();
};

