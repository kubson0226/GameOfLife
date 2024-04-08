#include <iostream>

#include "World.h"
#include "Organism.h"
#include "Plant.h"
#include "Sosnowsky.h"

Sosnowsky::Sosnowsky() : Plant()
{
	strengthOfAnimal = 10;
}

Sosnowsky::Sosnowsky(int x, int y, World* world) : Plant(10, x, y, world)
{

}

char Sosnowsky::GetKey() const
{
	return _key;
}

string Sosnowsky::GetName() const
{
	return "Sosnowsky hogweed";
}

void Sosnowsky::Action()
{
	Organism** org = new Organism * [4];
	org[0] = _world->GetSquare(_x, _y - 1);
	org[1] = _world->GetSquare(_x + 1, _y);
	org[2] = _world->GetSquare(_x, _y + 1);
	org[3] = _world->GetSquare(_x - 1, _y);

	if ((org[0] != nullptr) && org[0]->IsAnimal())
	{
		this->DeathComment(org[0]);
		_world->RemoveOrganism(org[0]);
	}
	if ((org[1] != nullptr) && org[1]->IsAnimal())
	{
		this->DeathComment(org[1]);
		_world->RemoveOrganism(org[1]);
	}
	if ((org[2] != nullptr) && org[2]->IsAnimal())
	{
		this->DeathComment(org[2]);
		_world->RemoveOrganism(org[2]);
	}
	if ((org[3] != nullptr) && org[3]->IsAnimal())
	{
		this->DeathComment(org[3]);
		_world->RemoveOrganism(org[3]);
	}
	int randomNumber = rand() % 100;
	if (randomNumber < chance)
	{
		Plant::Action();
	}
}

void Sosnowsky::Collision(Organism* secondOrganism)
{
	secondOrganism->DeathComment(this);
	_world->RemoveOrganism(secondOrganism);
}