#include <iostream>

#include "World.h"
#include "Organism.h"
#include "Plant.h"
#include "Grass.h"

Grass::Grass() : Plant()
{
	strengthOfAnimal = 0;
}

Grass::Grass(int x, int y, World* swiat) : Plant(0, x, y, swiat)
{

}

char Grass::GetKey() const
{
	return _key;
}

string Grass::GetName() const
{
	return "Grass";
}

void Grass::Action()
{
	int randomNumber = rand() % 100;
	if (randomNumber < chance)
	{
		Plant::Action();
	}
}

void Grass::Collision(Organism* atakujacy)
{
	Plant::Collision(atakujacy);
}