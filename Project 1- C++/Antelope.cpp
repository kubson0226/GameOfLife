#include <iostream>

#include "World.h"
#include "Organism.h"
#include "Animal.h"
#include "Antelope.h"

Antelope::Antelope() : Animal()
{
	strengthOfAnimal = 4;
	initiativeOfAnimal = 4;
}

Antelope::Antelope(int x, int y, World* world) : Animal(4, 4, x, y, world)
{

}

void Antelope::SetMovement(char moveKey)
{
	Animal::SetMovement(moveKey);
}

int Antelope::GetLastMove() const
{
	return Animal::GetLastMove();
}

char Antelope::GetKey() const
{
	return _key;
}

string Antelope::GetName() const
{
	return "Antelope";
}


void Antelope::Action()
{
	_world->SetSquare(_x, _y, nullptr);
	this->Move(2);
}

void Antelope::Collision(Organism* secondOrganism)
{
	int randomNumber = rand() % 100 + 1;
	if (randomNumber % 2 == 0 && secondOrganism->GetKey() != _key)
	{
		this->MoveToEmptySquare();
		if (_lastMove != 0)
		{
			return;
		}
	}
	
	Animal::Collision(secondOrganism);
}