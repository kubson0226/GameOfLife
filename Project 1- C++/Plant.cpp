#include <iostream>
#include <string>
#include "World.h"
#include "Organism.h"
#include "Plant.h"
#include "Grass.h"
#include "SowThistle.h"
#include "Guarana.h"
#include "Belladonna.h"
#include "Sosnowsky.h"

using namespace std;

Plant::Plant() : Organism()
{
	
}

Plant::Plant(int sila, int x, int y, World* swiat) : Organism(sila, 0, x, y, swiat)
{

}

int Plant::GetLastMove() const
{
	return 0;
}

string Plant::Write() const
{
	string result = this->GetName() + " " + to_string(this->GetStrength()) + " " + to_string(this->GetInitiative()) + " ";
	result += to_string(this->GetX()) + " " + to_string(this->GetY()) + " " + to_string(this->GetAge());
	return result;
}

void Plant::Action()
{
	string com;
	int* pointsX = new int[4];
	int* pointsY = new int[4];
	int* ruch = new int[4];				//tablica potrzebna do wygenerowania punktow
	int pointsCount = 0;
	_world->CreateEmptyPoints(_x, _y, pointsX, pointsY, ruch, &pointsCount);

	if (pointsCount != 0)
	{
		int randomNumber = rand() % pointsCount;
		Organism* org = this->CreateOrganism(pointsX[randomNumber], pointsY[randomNumber], _world);
		_world->AddOrganism(org);

		com = this->GetName() + ": \tsawing the plant from (" + to_string(_x) + ", ";
		com += to_string(_y) + ") na pole (" + to_string(pointsX[randomNumber]) + ", " + to_string(pointsY[randomNumber]) + ")";
		_world->Comment(com);
	}
}

void Plant::Collision(Organism* atakujacy)
{
	atakujacy->DeathComment(this);

	if (this->GetStrength() > atakujacy->GetStrength())
	{
		_world->RemoveOrganism(atakujacy);
	}
	else
	{
		_world->SetSquare(this->GetX(), this->GetY(), atakujacy);
		_world->RemoveOrganism(this);
		atakujacy->Draw();
	}
}

bool Plant::IsAnimal()
{
	return false;
}


void Plant::DeathComment(Organism* victim)
{
	string komentarz;
	komentarz = this->GetName() + ": \tattacked  " + victim->GetName();
	_world->Comment(komentarz);
}

Organism* Plant::CreateOrganism(int x, int y, World* world)
{
	if (typeid(*this) == typeid(Grass))
	{
		Grass* r = new Grass(x - 1, y - 1, world);
		return r;
	}
	else if (typeid(*this) == typeid(SowThistle))
	{
		SowThistle* r = new SowThistle(x - 1, y - 1, world);
		return r;
	}
	else if (typeid(*this) == typeid(Guarana))
	{
		Guarana* r = new Guarana(x - 1, y - 1, world);
		return r;
	}
	else if (typeid(*this) == typeid(Belladonna))
	{
		Belladonna* r = new Belladonna(x - 1, y - 1, world);
		return r;
	}
	else if (typeid(*this) == typeid(Sosnowsky))
	{
		Sosnowsky* r = new Sosnowsky(x - 1, y - 1, world);
		return r;
	}
}

void Plant::SetMovement(char ruch)
{
	cout << "Error: You cannot move a plant" << endl;
}

void Plant::GoBack()
{
	cout << "Error: You cannot move a plant" << endl;
}

void Plant::RunAway()
{
	cout << "Error: You cannot move a plant" << endl;
}