#include <iostream>

#include "World.h"
#include "Organism.h"
#include "Animal.h"
#include "Turtle.h"

#define GORA 1
#define PRAWO 2
#define DOL 3
#define LEWO 4

Turtle::Turtle() : Animal()
{
	strengthOfAnimal = 2;
	initiativeOfAnimal = 1;
}

Turtle::Turtle(int x, int y, World* world) : Animal(2, 1, x, y, world)
{

}

void Turtle::SetMovement(char moveKey)
{
	Animal::SetMovement(moveKey);
}

int Turtle::GetLastMove() const
{
	return Animal::GetLastMove();
}

char Turtle::GetKey() const
{
	return _key;
}

string Turtle::GetName() const
{
	return "Turtle";
}

void Turtle::Action()
{
	int randomNumber = rand() % 100 + 1;
	if (randomNumber % 4 == 0)
	{
		Animal::Action();
	}
	else
	{
		_lastMove = 0;
	}
}

void Turtle::Collision(Organism* secondOrganism)
{
	if (secondOrganism->GetStrength() < 5 && secondOrganism->GetKey() != _key)
	{
		secondOrganism->GoBack();
	}
	else
	{
		Animal::Collision(secondOrganism);
	}	
}