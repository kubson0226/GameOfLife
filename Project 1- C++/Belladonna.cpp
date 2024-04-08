#include <iostream>

#include "World.h"
#include "Organism.h"
#include "Plant.h"
#include "Belladonna.h"

Belladonna::Belladonna() : Plant()
{
	strengthOfAnimal = 99;
}

Belladonna::Belladonna(int x, int y, World* swiat) : Plant(99, x, y, swiat)
{

}

char Belladonna::GetKey() const
{
	return _key;
}

string Belladonna::GetName() const
{
	return "Belladonna";
}

void Belladonna::Action()
{
	int randomNumber = rand() % 100;
	if (randomNumber < chance)
	{
		Plant::Action();
	}
}

void Belladonna::Collision(Organism* secondOrganism)
{
	secondOrganism->DeathComment(this);

	_world->RemoveOrganism(secondOrganism);
}