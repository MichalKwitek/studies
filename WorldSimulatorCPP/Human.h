#pragma once
#include "Animal.h"
#include <conio.h>
#define W_KEY 119
#define S_KEY 115
#define A_KEY 97
#define D_KEY 100
#define SPACE 32
#define SUPER_STRENGTH_INCREASE 5
class Human :
    public Animal
{
private:
    int superStrengthTimer;
    bool canMove(Coordinate coord) const;
    void activateSuperStrength();
    void endTurn() override;
    void draw() const override;
public:
    Human(World* world, Coordinate coord);
    Human(World* world, Coordinate coord, int strength, int age, int superStrengthTimer);
    void action() override;
    int getSuperStrengthTimer() const;
    void setSuperStrengthTimer(int timer);
};

