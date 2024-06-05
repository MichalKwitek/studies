#pragma once
#include "Animal.h"
class Fox :
    public Animal
{
public:
    Fox(World* world, Coordinate coord);
    Fox(World* world, Coordinate coord, int strength, int age);
    void action() override;
private:
    void draw() const override;
    bool spaceIsViable(Coordinate& coord) const override;
    //Coordinate checkSurroundings(Coordinate coord);
};

