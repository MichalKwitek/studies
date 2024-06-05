#pragma once
#include "Organism.h"
class Animal :
    public Organism
{
public:
    virtual void action() override;
protected:
    virtual void collision(Animal* initiator, Organism* opponent);
    virtual void fight(Animal* initiator, Organism* opponent);

};

