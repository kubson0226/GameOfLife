#include <iostream>

#include "World.h"
#include "Organism.h"
#include "Plant.h"
#include "Guarana.h"

Guarana::Guarana() : Plant()
{
	strengthOfAnimal = 0;
}

Guarana::Guarana(int x, int y, World* swiat) : Plant(0, x, y, swiat)
{

}

char Guarana::GetKey() const
{
	return _key;
}

string Guarana::GetName() const
{
	return "Guarana";
}

void Guarana::Action()
{
	int randomNumber = rand() % 100;
	if (randomNumber < chance)
	{
		Plant::Action();
	}
}

void Guarana::Collision(Organism* atakujacy)
{
	if (this->GetStrength() > atakujacy->GetStrength())
	{
		this->DeathComment(atakujacy);
		_world->RemoveOrganism(atakujacy);
	}
	else
	{
		atakujacy->DeathComment(this);
		atakujacy->SetStrength(atakujacy->GetStrength() + 3);
		string komentarz = this->GetName() + ": \tenhancement of " + atakujacy->GetName() + " by 3 points";
		_world->Comment(komentarz);
		_world->SetSquare(this->GetX(), this->GetY(), atakujacy);
		_world->RemoveOrganism(this);
		atakujacy->Draw();
	}
}