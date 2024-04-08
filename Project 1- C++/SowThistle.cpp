#include <iostream>

#include "World.h"
#include "Organism.h"
#include "Plant.h"
#include "SowThistle.h"

SowThistle::SowThistle() : Plant()
{
	strengthOfAnimal = 0;
}

SowThistle::SowThistle(int x, int y, World* swiat) : Plant(0, x, y, swiat)
{

}

char SowThistle::GetKey() const
{
	return _key;
}

string SowThistle::GetName() const
{
	return "Sow Thistle";
}

void SowThistle::Action()
{
	for (int i = 0; i < 3; i++)
	{
		int randomNumber = rand() % 100;
		if (randomNumber < chance)
		{
			Plant::Action();
		}
	}
}

void SowThistle::Collision(Organism* atakujacy)
{
	Plant::Collision(atakujacy);
}