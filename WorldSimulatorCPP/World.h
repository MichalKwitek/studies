#pragma once
#include "Organism.h"
#include "Animal.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

#define WORLD_WIDTH 20
#define WORLD_HEIGHT 20
#define GRAY "\033[90m"
#define GRAY "\033[90m"
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define BRIGHT_GREEN "\033[92m"
#define YELLOW_BCKG "\033[43m"
#define GREEN_BCKG "\033[42m"
#define CYAN "\033[36m"
#define PURPLE "\033[35m"
#define RED "\033[31m"
#define BLACK "\033[30m"
#define YELLOW "\033[33m"
#define BRIGHT_YELLOW "\033[93m"
#define ORANGE "\033[91m"
#define BRIGHT_BLUE "\033[96m"
#define GRAY_BCKG "\033[100m"
#define H_LINE 205
#define V_LINE 186
using namespace std;
class World
{
private:
	int rows;
	int columns;
	std::vector<Organism*> organisms;
	int speciesCounter[10];
	int turn;
public:
	World();
	World(int rows, int columns);
	~World();
	void gameMenu();
	int getRows() const;
	int getColumns() const;
	int getTurn() const;
	void setDimensions(int rows, int columns);
	Organism* findOrganismByCoordinate(Coordinate& coord) const;
	bool SpaceIsOccupied(Coordinate& coord) const;
	void addOrganism(Organism* org);
private:
	void drawWorld() const;
	void doTurn();
	void initializeBoard();
	void readInputs(std::fstream& file);
	void clearBoard();
	void loadState();
	void saveState();
};



