#include <conio.h>
#include <sstream>
#include "World.h"
#include "Species.h"
#include "Animal.h"
#include "Plant.h"
#include "Wolf.h"
#include "Grass.h"
#include "Sheep.h"
#include "Antilope.h"
#include "Turtle.h"
#include "Fox.h"
#include "Dandelion.h"
#include "Guarana.h"
#include "Nightshade.h"
#include "Sosnowsky.h"
#include "Human.h"

World::World() {
	rows = WORLD_HEIGHT;
	columns = WORLD_WIDTH;
	organisms = vector<Organism*>();
	turn = 0;
	for (int i = 0; i < 10; ++i) {
		speciesCounter[i] = 0;
	}
}

World::World(int height, int width) {
	rows = height;
	columns = width;
	organisms = vector<Organism*>();
	turn = 0;
	for (int i = 0; i < 10; ++i) {
		speciesCounter[i] = 0;
	}
}
// znajduje żywy organizm zajmujący podane pole lub nullptr
Organism* World::findOrganismByCoordinate(Coordinate& coord) const {
	for (Organism* org : organisms) { 
		if (org->getCoord() == coord && org->isDead() == false) {
			return org; // Return the pointer to the organism if found
		}
	}
	return nullptr; // Return nullptr if no organism with the specified coordinate is found
}
// sprawdza czy podane pole jest zajęte przez żywy organizm
bool World::SpaceIsOccupied(Coordinate& coord) const {
	for (Organism* org : organisms) {
		if (org->getCoord() == coord && org->isDead() == false) {
			return true; // Found an Organism with the specified coordinates
		}
	}
	return false; // No Organism with the specified coordinates found
}

void World::addOrganism(Organism* org) {
	if (!dynamic_cast<Human*>(org)) { // człowiek nia ma przypisanego licznika
		speciesCounter[org->getIndex()] += 1; // zwiększ licznik o 1
		org->setID(speciesCounter[org->getIndex()]); // ustaw ID organizmu na wartość licznika
	}
	organisms.push_back(org);
}

void World::drawWorld() const {
	cout << "Michal Kwitek" << endl << "nr albumu: 186531" << endl << "tura: " << getTurn() << endl;
	cout << " ";
	int iterations = columns / 10;
	int remainder = columns % 10;
	for (int j = 0; j < iterations; j++) {
		for (int i = 0; i < 10; i++) {
			cout << i;
		}
	}
	for (int i = 0; i < remainder; i++) {
		cout << i;
	}
	cout << endl;
	cout << char(201);
	for (int i = 0; i < columns; i++) {
		cout << char(H_LINE);
	}
	cout << char(187);
	cout << endl;
	for (int i = 0; i < rows; i++) {
		cout << char(V_LINE);
		for (int j = 0; j < columns; j++) {
			Coordinate searchCoord;
			searchCoord.x = j;
			searchCoord.y = i;
			Organism* org = findOrganismByCoordinate(searchCoord);
			if (org) {
				org->draw();
			}
			else {
				cout << GRAY << "." << RESET;
			}
		}
		cout << char(V_LINE);
		cout << i;
		cout << endl;
	}
	cout << char(200);
	for (int i = 0; i < columns; i++) {
		cout << char(H_LINE);
	}
	cout << char(188);
	cout << endl;
}
// jeśli zacznę iterować od końca wektora to nawet nie potrzebuję sprawdzać wieku organizmów
void World::doTurn() { // na początku tury wszystkie organizmy w wektorze organisms są żywe (dead = false)
	turn++; // to tak może być?
	drawWorld();
	sort(organisms.begin(), organisms.end(), [](Organism* a, Organism* b) { // sortowanie wektora z organizmami najpierw po inicjatywie a potem po wieku
		if (a->getInitiative() != b->getInitiative()) {
			return a->getInitiative() > b->getInitiative();
		}
		else if (a->getAge() != b->getAge()) {
			return a->getAge() > b->getAge();
		}
		else if (a->getSprite() != b->getSprite()) { // dla czytelności jeszcze po Sprite i ID - nie zmienia to mechaniki 
			return a->getSprite() > b->getSprite();
		}
		else {
			return a->getID() < b->getID();
		}
	});

	for (int i = 0; i < organisms.size(); i++) { // iterowanie po wektorze i wykonywanie akcji organizmów
		if (organisms[i]->getAge() > -1 && organisms[i]->isDead() == false) // newborns and dead organisms cannot take actions
			organisms[i]->action();
	}

	for (int i = organisms.size() - 1; i >= 0; i--) { // zwalnianie pamięci po zniszczonych organizmach
		if (organisms[i]->isDead() == true) {
			delete organisms[i];
			organisms.erase(organisms.begin() + i);
		}
	}

	for (int i = 0; i < organisms.size(); i++) {
		organisms[i]->endTurn(); // zwiększanie wieku organizmów oraz licznik umiejętności w przypadku człowieka
	}
}

void World::clearBoard() {
	for (auto& ptr : organisms) {
		delete ptr; // Deallocate memory for each object
	}
	organisms.clear();
}

void World::initializeBoard() {
	vector<Coordinate> coords;
	int organismNumber = rand() % ((getColumns() * getRows()) / 5);
	while (coords.size() <= organismNumber){
		Coordinate coord;
		coord.x = rand() % getColumns();
		coord.y = rand() % getRows();
		bool isUnique = true;
		for (Coordinate c : coords)
			if (c == coord)
				isUnique = false;
		if (isUnique)
			coords.push_back(coord);
	}
	for (int i = 0; i < (coords.size() - 1); i++) {
		int organismType = rand() % SPECIES_NUMBER;
		Organism* newOrganism = nullptr;
		switch (organismType) {
		case W:
			newOrganism = new Wolf(this, coords[i]);
			break;
		case S:
			newOrganism = new Sheep(this, coords[i]);
			break;
		case A:
			newOrganism = new Antilope(this, coords[i]);
			break;
		case T:
			newOrganism = new Turtle(this, coords[i]);
			break;
		case F:
			newOrganism = new Fox(this, coords[i]);
			break;
		case g:
			newOrganism = new Grass(this, coords[i]);
			break;
		case d:
			newOrganism = new Dandelion(this, coords[i]);
			break;
		case x:
			newOrganism = new Guarana(this, coords[i]);
			break;
		case n:
			newOrganism = new Nightshade(this, coords[i]);
			break;
		case s:
			newOrganism = new Sosnowsky(this, coords[i]);
			break;
		}
	}
	Human* h = new Human(this, coords[coords.size() - 1]);

	/*Sheep* s1 = new Sheep(this, coords[0]);
	Sheep* s2 = new Sheep(this, coords[1]);
	Sheep* s3 = new Sheep(this, coords[2]);
	Wolf* w1 = new Wolf(this, coords[3]);
	Wolf* w2 = new Wolf(this, coords[4]);
	Wolf* w3 = new Wolf(this, coords[5]);
	Wolf* w4 = new Wolf(this, coords[6]);
	Grass* g1 = new Grass(this, coords[7]);
	Grass* g2 = new Grass(this, coords[8]);
	Dandelion* d1 = new Dandelion(this, coords[9]);
	Dandelion* d2 = new Dandelion(this, coords[10]);
	Antilope* a1 = new Antilope(this, coords[11]);
	Antilope* a2 = new Antilope(this, coords[12]);
	Antilope* a3 = new Antilope(this, coords[13]);
	Antilope* a4 = new Antilope(this, coords[14]);
	Antilope* a5 = new Antilope(this, coords[15]);
	Turtle* t1 = new Turtle(this, coords[16]);
	Turtle* t2 = new Turtle(this, coords[17]);
	Turtle* t3 = new Turtle(this, coords[18]);
	Guarana* x1 = new Guarana(this, coords[19]);
	Guarana* x2 = new Guarana(this, coords[20]);
	Nightshade* n1 = new Nightshade(this, coords[21]);
	Nightshade* n2 = new Nightshade(this, coords[22]);
	Fox* f1 = new Fox(this, coords[23]);
	Fox* f2 = new Fox(this, coords[24]);
	Fox* f3 = new Fox(this, coords[25]);
	Fox* f4 = new Fox(this, coords[26]);
	Sosnowsky* b1 = new Sosnowsky(this, coords[27]);
	Sosnowsky* b2 = new Sosnowsky(this, coords[28]);
	Human* h1 = new Human(this, coords[29]);*/
} 

void World::loadState() {
	system("CLS");
	bool opened = false;
	while (!opened) {
		cout << "Podaj nazwe pliku: ";
		string name;
		cin >> name;
		fstream file;
		file.open(name, fstream::in);
		if (!file.good()) {
			cout << "Nie znaleziono takiego pliku" << endl;
		}
		else {
			//file.exceptions(istream::badbit | istream::failbit );
			clearBoard();
			int height, width;
			file >> height >> width;
			rows = height;
			columns = width;
			readInputs(file);
			opened = true;
		}
		file.close();
	}
}

void World::saveState() {
	system("CLS");
	drawWorld();
	string fileName;
	cout << "Podaj nazwe pliku do ktorego chcesz zapisac stan gry" << endl;
	cin >> fileName;
	ofstream file(fileName);
	file << rows << " " << columns << endl;
	for (auto& org : organisms) {
		if (org->isDead() == false) {
			file << org->getSprite() << " " << org->getStrength() << " " << org->getAge() << " " << org->getXCoord() << " " << org->getYCoord();
			if (Human* h = dynamic_cast<Human*>(org))
				file << " " << h->getSuperStrengthTimer();
			file << endl;
		}
	}
}

void World::readInputs(std::fstream& file)
{
	char sprite;
	int strength, age, superStrengthTimer;
	Coordinate coord;
	string line;
	while (getline(file, line)) {
		if(!line.empty()) { 
			std::stringstream ss(line);
			ss >> sprite;
			ss >> strength;
			ss >> age;
			ss >> coord.x;
			ss >> coord.y;

			/*sprite = line[0];
			strength = line[2] - '0';
			age = line[4] - '0';
			coord.x = line[6] - '0';
			coord.y = line[8] - '0';*/

			if (sprite == 'H') // dla człowieka dodatkowo superStrengthTimer
			ss >> superStrengthTimer;
		
			switch (sprite) {
			case ('H'): {
				Human* h = new Human(this, coord, strength, age, superStrengthTimer);
				break;
			}
			case ('W'): {
				Wolf* w = new Wolf(this, coord, strength, age);
				break;
			}
			case ('S'): {
				Sheep* s = new Sheep(this, coord, strength, age);
				break;
			}
			case ('F'): {
				Fox* f = new Fox(this, coord, strength, age);
				break;
			}
			case ('T'): {
				Turtle* t = new Turtle(this, coord, strength, age);
				break;
			}
			case ('A'): {
				Antilope* a = new Antilope(this, coord, strength, age);
				break;
			}
			case ('d'): {
				Dandelion* d = new Dandelion(this, coord, strength, age);
				break;
			}
			case ('g'): {
				Grass* g = new Grass(this, coord, strength, age);
				break;
			}
			case ('x'): {
				Guarana* u = new Guarana(this, coord, strength, age);
				break;
			}
			case ('s'): {
				Sosnowsky* b = new Sosnowsky(this, coord, strength, age);
				break;
			}
			case ('n'): {
				Nightshade* n = new Nightshade(this, coord, strength, age);
				break;
			}
			}
		}
	}
}

void World::gameMenu() {
	char option = 'a';
	while (option != char(27)) {
		cout << "MENU GLOWNE" << endl << endl;
		cout << RED << "1" << RESET << "- podstawowa plansza 20x20" << endl;
		cout << RED << "2" << RESET << "- wczytaj stan gry z pliku" << endl;
		cout << "bazowe pliki do testu maja format test(nr).txt np. test1.txt" << endl;
		cout << RED << "3" << RESET << "- utworz plansze podstawowa o podanym rozmiarze (wiersze, kolumny)" << endl;
		cout << "Aby zakonczyc dzialanie programu wcisnij " << RED << "ESC" << RESET << endl;
		do {
			option = _getch();
		} while (option != '1' && option != '2' && option != '3' && option != char(27));
		switch (option) {
		case('1'):
		{
			setDimensions(WORLD_HEIGHT, WORLD_WIDTH);
			initializeBoard();
			break;
		}
		case('2'):
		{
			loadState();
			system("CLS");
			break;
		}
		case('3'):
		{
			system("CLS");
			string height, width;
			int heightInt = 0;
			int widthInt = 0;
			do {
				try {
					cout << "Wprowadz liczbe kolumn: ";
					cin >> width;
					widthInt = stoi(width);
					if (widthInt < 4) {
						cout << "Niepoprawny wymiar planszy - szerokosc musi wynosic co najmniej 4 pola" 
							<< endl << "Nacisnij dowolny przycisk aby kontynuowac";
						_getch();
						system("CLS");
					}
				}
				catch (const invalid_argument& e) {
					cout << "Wprowadzono bledne dane" << endl << "Nacisnij dowolny przycisk aby kontynuowac";
					_getch();
					system("CLS");
				}
			} while (widthInt < 4);
			do {
				try {
					cout << "Wprowadz liczbe wierszy: ";
					cin >> height;
					heightInt = stoi(height);
					if (heightInt < 4) {
						cout << "Niepoprawny wymiar planszy - wysokosc musi wynosic co najmniej 4 pola"
							<< endl << "Nacisnij dowolny przycisk aby kontynuowac";
						_getch();
						system("CLS");
					}
				}
				catch (const invalid_argument& e) {
					cout << "Wprowadzono bledne dane" << endl << "Nacisnij dowolny przycisk aby kontynuowac";
					_getch();
					system("CLS");
				}
			} while (heightInt < 4);
			system("CLS");
			setDimensions(heightInt, widthInt);
			initializeBoard();
			break;
		}
		}
		while (option != '5' && option != char(27)) {
			doTurn();
			cout << endl << PURPLE << "Wcisnij 4 aby zapisac stan gry do pliku " << endl <<
				"Wcisnij 5 by wrocic do menu" << endl << "Wcisnij N by przejsc do nastepnej tury" << RESET;
			option = _getch();
			if (option == '4') {
				saveState();
			}
			system("CLS");
		}
		clearBoard();	
	}
}

int World::getColumns() const{
	return columns;
}

int World::getRows() const{
	return rows;
}

int World::getTurn() const{
	return turn;
}

void World::setDimensions(int height, int width) {
	rows = height;
	columns = width;
}

World::~World() {};