#include <iostream>
#include <cstdlib>
#include <string>

#include "World.h"
#include "Organism.h"
#include "Animal.h"

#include "Wolf.h"
#include "Sheep.h"
#include "Fox.h"
#include "Turtle.h"
#include "Antelope.h"

#define GORA 1
#define PRAWO 2
#define DOL 3
#define LEWO 4
#define SIZE 20

using namespace std;

Animal::Animal() : Organism()
{
	_lastMove = NULL;
}

Animal::Animal(int strength, int ini, int x, int y, World* world) : Organism(strength, ini, x, y, world)
{
	_lastMove = NULL;
}

void Animal::SetMovement(char moveKey)
{
	_lastMove = moveKey;
}

int Animal::GetLastMove() const
{
	return _lastMove;
}

string Animal::Write() const
{
	string result = this->GetName() + " " + to_string(strengthOfAnimal) + " " + to_string(initiativeOfAnimal) + " ";
	result += to_string(_x) + " " + to_string(_y) + " " + to_string(yearOfAnimal);
	return result;
}

void Animal::Action()
{
	this->Move(1);
}

void Animal::Collision(Organism* organism)
{
	string komentarz;
	organism->DeathComment(this);
	if (this->GetKey() == organism->GetKey() && organism->GetAge() > 0)
	{
		this->Reproduction(organism, _world);
		komentarz = "Organism reproducted";
		_world->Comment(komentarz);
	}
	else if (this->GetKey() == organism->GetKey() && organism->GetAge() <= 0)
	{
		organism->GoBack();
		komentarz = "Trying to reproduct with young organism";
		_world->Comment(komentarz);
	}
	else if (this->GetStrength() > organism->GetStrength())
	{
		_world->RemoveOrganism(organism);
	}
	else
	{
		_world->SetSquare(this->GetX(), this->GetY(), organism);
		_world->RemoveOrganism(this);
		organism->Draw();
	}
}

void Animal::GoBack()
{
	int atakujacyX = this->GetX();
	int atakujacyY = this->GetY();
	if (this->GetLastMove() == GORA)
	{
		this->SetCoordinates(atakujacyX - 1, atakujacyY);
	}
	else if (this->GetLastMove() == PRAWO)
	{
		this->SetCoordinates(atakujacyX - 2, atakujacyY - 1);
	}
	else if (this->GetLastMove() == DOL)
	{
		this->SetCoordinates(atakujacyX - 1, atakujacyY - 2);
	}
	else if (this->GetLastMove() == LEWO)
	{
		this->SetCoordinates(atakujacyX, atakujacyY - 1);
	}
	this->Draw();
}

void Animal::RunAway()
{
	string komentarz;
	int* pointsX = new int[4];
	int* pointsY = new int[4];
	int* ruch = new int[4];
	int pointsCount = 0;
	Organism** org = new Organism * [4];
	Organism* secondOrganism = _world->GetSquare(_x, _y);
	if (secondOrganism == this)
	{
		_world->SetSquare(_x, _y, nullptr);
	}
	org[0] = _world->GetSquare(_x, _y - 1);
	org[1] = _world->GetSquare(_x + 1, _y);
	org[2] = _world->GetSquare(_x, _y + 1);
	org[3] = _world->GetSquare(_x - 1, _y);
		
	if (_y - 1 != 0 && (org[0] == nullptr || org[0]->GetStrength() <= strengthOfAnimal))
	{
		pointsX[pointsCount] = _x;
		pointsY[pointsCount] = _y - 1;
		ruch[pointsCount] = 1;
		pointsCount++;
	}
	if (_x + 1 != _world->GetLength() + 1 && (org[1] == nullptr || org[1]->GetStrength() <= strengthOfAnimal))
	{
		pointsX[pointsCount] = _x + 1;
		pointsY[pointsCount] = _y;
		ruch[pointsCount] = 2;
		pointsCount++;
	}
	if (_y + 1 != _world->GetWidth() + 1 && (org[2] == nullptr || org[2]->GetStrength() <= strengthOfAnimal))
	{
		pointsX[pointsCount] = _x;
		pointsY[pointsCount] = _y + 1;
		ruch[pointsCount] = 3;
		pointsCount++;
	}
	if (_x - 1 != 0 && (org[3] == nullptr || org[3]->GetStrength() <= strengthOfAnimal))
	{
		pointsX[pointsCount] = _x - 1;
		pointsY[pointsCount] = _y;
		ruch[pointsCount] = 4;
		pointsCount++;
	}
	komentarz = this->GetName() + ": \tmoving from ("+ to_string(_x) + ", " + to_string(_y) + ") to (";
	if (pointsCount != 0)
	{
		int los = rand() % pointsCount;
		_x = pointsX[los];
		_y = pointsY[los];
		_lastMove = ruch[los];
	}
	else
	{
		this->Draw();
		_lastMove = 0;
	}
	komentarz += to_string(_x) + ", " + to_string(_y) + ")";
	_world->Comment(komentarz);
}

bool Animal::IsAnimal()
{
	return true;
}

void Animal::DeathComment(Organism* org)
{
	string com = this->GetName() + ": \tattacked " + org->GetName();
	_world->Comment(com);
}

void Animal::MoveToEmptySquare()
{
	string komentarz;
	_world->SetSquare(_x, _y, nullptr);
	int* pointsX = new int[4];
	int* pointsY = new int[4];
	int* ruch = new int[4];
	int pointsCount = 0;
	_world->CreateEmptyPoints(_x, _y, pointsX, pointsY, ruch, &pointsCount);
	komentarz = this->GetName() + ": \tmoving from (" + to_string(_x) + ", " + to_string(_y) + ") to (";
	if (pointsCount != 0)
	{
		int los = rand() % pointsCount;
		_x = pointsX[los];
		_y = pointsY[los];
		_lastMove = ruch[los];
	}
	else
	{
		this->Draw();
		_lastMove = 0;
	}
	komentarz += to_string(_x) + ", " + to_string(_y) + ")";
	_world->Comment(komentarz);
}

void Animal::Move(int length)
{
	string komentarz;
	_world->SetSquare(_x, _y, nullptr);
	int* pointsX = new int[4];
	int* pointsY = new int[4];
	int* ruch = new int[4];
	int pointsCount = 0;
	if (_y - length > 0)
	{
		pointsX[pointsCount] = _x;
		pointsY[pointsCount] = _y - length;
		ruch[pointsCount] = GORA;
		pointsCount++;
	}
	if (_x + length < _world->GetLength() + 1)
	{
		pointsX[pointsCount] = _x + length;
		pointsY[pointsCount] = _y;
		ruch[pointsCount] = PRAWO;
		pointsCount++;
	}
	if (_y + length < _world->GetWidth() + 1)
	{
		pointsX[pointsCount] = _x;
		pointsY[pointsCount] = _y + length;
		ruch[pointsCount] = DOL;
		pointsCount++;
	}
	if (_x - length > 0)
	{
		pointsX[pointsCount] = _x - length;
		pointsY[pointsCount] = _y;
		ruch[pointsCount] = LEWO;
		pointsCount++;
	}
	komentarz = this->GetName() + ": \tmoving from (" + to_string(_x) + ", " + to_string(_y) + ") to (";
	if (pointsCount != 0)
	{
		int random = rand() % pointsCount;
		_x = pointsX[random];
		_y = pointsY[random];
		_lastMove = ruch[random];
	}
	else
	{
		this->Draw();
		_lastMove = 0;
	}
	komentarz += to_string(_x) + ", " + to_string(_y) + ")";
	_world->Comment(komentarz);
}

Organism* Animal::CreateOrganism(int x, int y, World* world)
{
	if (typeid(*this) == typeid(Wolf))
	{
		Wolf* zw = new Wolf(x - 1, y - 1, world);
		return zw;
	}
	else if (typeid(*this) == typeid(Sheep))
	{
		Sheep* zw = new Sheep(x - 1, y - 1, world);
		return zw;
	}
	else if (typeid(*this) == typeid(Fox))
	{
		Fox* zw = new Fox(x - 1, y - 1, world);
		return zw;
	}
	else if (typeid(*this) == typeid(Turtle))
	{
		Turtle* zw = new Turtle(x - 1, y - 1, world);
		return zw;
	}
	else if (typeid(*this) == typeid(Antelope))
	{
		Antelope* zw = new Antelope(x - 1, y - 1, world);
		return zw;
	}
}

void Animal::Reproduction(Organism* secondOrganism, World* world)
{
	int* positionX = new int[6];
	int* positionY = new int[6];
	int* ruch = new int[6];
	int point = 0;
	int x = 0;
	int y = 0;
	int pointsCount = 0;
	secondOrganism->GoBack();
	if (secondOrganism->GetLastMove() == GORA || secondOrganism->GetLastMove() == DOL)
	{
		world->CreateEmptyPoints(secondOrganism->GetX(), secondOrganism->GetY(), positionX, positionY, ruch, &pointsCount);
		world->CreateEmptyPoints(this->GetX(), this->GetY(), positionX, positionY, ruch, &pointsCount);

		if (pointsCount != 0)
		{
			point = rand() % pointsCount;
			Organism* org = this->CreateOrganism(positionX[point], positionY[point], world);
			world->AddOrganism(org);
		}
	}
	else if (secondOrganism->GetLastMove() == LEWO || secondOrganism->GetLastMove() == PRAWO)
	{
		world->CreateEmptyPoints(secondOrganism->GetX(), secondOrganism->GetY(), positionX, positionY, ruch, &pointsCount);
		world->CreateEmptyPoints(this->GetX(), this->GetY(), positionX, positionY, ruch, &pointsCount);

		if (pointsCount != 0)
		{
			point = rand() % pointsCount;
			Organism* org = this->CreateOrganism(positionX[point], positionY[point], world);
			world->AddOrganism(org);
		}
	}
}