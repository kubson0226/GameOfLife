#include <iostream>

#include "World.h"
#include "Organism.h"
#include "Animal.h"
#include "Sheep.h"

Sheep::Sheep() : Animal()
{
	strengthOfAnimal = 4;
	initiativeOfAnimal = 4;
}

Sheep::Sheep(int x, int y, World* swiat) : Animal(4, 4, x, y, swiat)
{

}

void Sheep::SetMovement(char moveKey)
{
	Animal::SetMovement(moveKey);
}

int Sheep::GetLastMove() const
{
	return Animal::GetLastMove();
}

char Sheep::GetKey() const
{
	return _key;
}

string Sheep::GetName() const
{
	return "Sheep";
}

void Sheep::Action()
{
	Animal::Action();
}

void Sheep::Collision(Organism* atakujacy)
{
	Animal::Collision(atakujacy);
}