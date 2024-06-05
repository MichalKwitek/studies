#pragma once
#include "Organism.h"

#define GROW_CHANCE 10

class Plant :
    public Organism
{
public:
    virtual void action() override;
private:
    virtual void draw() const override;
};

