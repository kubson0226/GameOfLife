#include <iostream>

#include "World.h"
#include "Organism.h"

using namespace std;

Organism::Organism()
{
	strengthOfAnimal = 0;
	initiativeOfAnimal = 0;
	_x = 0;
	_y = 0;
	_world = NULL;
	yearOfAnimal = 0;
}

Organism::Organism(int strength, int initiative, int x, int y, World* world)
{
	strengthOfAnimal = strength;
	initiativeOfAnimal = initiative;
	_x = x + 1;
	_y = y + 1;
	_world = world;
	yearOfAnimal = 0;
}

void Organism::SetStrength(int strength)
{
	strengthOfAnimal = strength;
}

void Organism::SetInitiative(int ini)
{
	initiativeOfAnimal = ini;
}

void Organism::SetCoordinates(int x, int y)
{
	_x = x + 1;
	_y = y + 1;
}

void Organism::SetAge(int wiek)
{
	yearOfAnimal = wiek;
}

void Organism::SetWorld(World* world)
{
	_world = world;
}

int Organism::GetStrength() const
{
	return strengthOfAnimal;
}

int Organism::GetInitiative() const
{
	return initiativeOfAnimal;
}

int Organism::GetX() const
{
	return _x;
}

int Organism::GetY() const
{
	return _y;
}

int Organism::GetAge() const
{
	return yearOfAnimal;
}

World* Organism::GetWorld() const
{
	return _world;
}

void Organism::Draw()
{
	_world->SetSquare(_x, _y, this);
}