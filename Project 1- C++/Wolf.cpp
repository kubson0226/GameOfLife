#include <iostream>

#include "World.h"
#include "Organism.h"
#include "Animal.h"
#include "Wolf.h"

Wolf::Wolf() : Animal()
{
	strengthOfAnimal = 9;
	initiativeOfAnimal = 5;
}

Wolf::Wolf(int x, int y, World* world) : Animal(9, 5, x, y, world)
{

}

void Wolf::SetMovement(char moveKey)
{
	Animal::SetMovement(moveKey);
}

int Wolf::GetLastMove() const
{
	return Animal::GetLastMove();
}

char Wolf::GetKey() const
{
	return _key;
}

string Wolf::GetName() const
{
	return "Wolf";
}

void Wolf::Action()
{
	Animal::Action();
}

void Wolf::Collision(Organism* secondOrganism)
{
	Animal::Collision(secondOrganism);
}