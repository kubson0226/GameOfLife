#include <iostream>

#include "World.h"
#include "Organism.h"
#include "Animal.h"
#include "Fox.h"

Fox::Fox() : Animal()
{
	strengthOfAnimal = 3;
	initiativeOfAnimal = 7;
}

Fox::Fox(int x, int y, World* swiat) : Animal(3, 7, x, y, swiat)
{

}

void Fox::SetMovement(char ruch)
{
	Animal::SetMovement(ruch);
}

int Fox::GetLastMove() const
{
	return Animal::GetLastMove();
}

char Fox::GetKey() const
{
	return _key;
}

string Fox::GetName() const
{
	return "Fox";
}

void Fox::Action()
{
	Animal::RunAway();
}

void Fox::Collision(Organism* atakujacy)
{
	Animal::Collision(atakujacy);
}