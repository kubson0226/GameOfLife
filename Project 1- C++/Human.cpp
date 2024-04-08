#include <iostream>
#include <string>

#include "World.h"
#include "Organism.h"
#include "Animal.h"
#include "Human.h"

#define UPARROW 72
#define RIGHTARROW 77
#define DOWNARROW 80
#define LEFTARROW 75
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

using namespace std;

Human::Human(int x, int y, World* world) : Animal(5, 4, x, y, world)
{
	_howManyTurns = 5;
	_abilityActivated = false;
}

void Human::SetMovement(char moveKey)
{
	if (moveKey == UPARROW)
	{
		_lastMove = UP;
	}		
	else if (moveKey == RIGHTARROW)
	{
		_lastMove = RIGHT;
	}
	else if (moveKey == DOWNARROW)
	{
		_lastMove = DOWN;
	}
	else if (moveKey == LEFTARROW)
	{
		_lastMove = LEFT;
	}
}

void Human::SetIsAbilityActive(bool active)
{
	_abilityActivated = active;
}

void Human::SetHowManyTurns(int turns)
{
	_howManyTurns = turns;
}

int Human::GetLastMove() const
{
	return Animal::GetLastMove();
}

bool Human::IsAbilityActive() const
{
	return _abilityActivated;
}

int Human::GetHowManyTurnsActive() const
{
	return _howManyTurns;
}

char Human::GetKey() const
{
	return _key;
}

string Human::GetName() const
{
	return "Human";
}

string Human::Write() const
{
	string result = this->GetName() + " " + to_string(strengthOfAnimal) + " " + to_string(initiativeOfAnimal) + " ";
	result += to_string(_x) + " " + to_string(_y) + " " + to_string(yearOfAnimal);
	result += " " + to_string(_abilityActivated) + " " + to_string(_howManyTurns);
	return result;
}

void Human::Action()
{
	string com;
	com = this->GetName() + ": \tmoving from (" + to_string(_x) + ", " + to_string(_y) + ") to (";
	_world->SetSquare(_x, _y, nullptr);
	if ((_lastMove == 1) && (_y - 1 != 0))
	{
		_y -= 1;
	}
	else if ((_lastMove == 2) && (_x + 1 != _world->GetLength() + 1))
	{
		_x += 1;
	}
	else if ((_lastMove == 3) && (_y + 1 != _world->GetWidth() + 1))
	{
		_y += 1;
	}
	else if ((_lastMove == 4) && (_x - 1 != 0))
	{
		_x -= 1;
	}
	else
	{
		_lastMove = 0;
		this->Draw();
	}
	com += to_string(_x) + ", " + to_string(_y) + ")";
	_world->Comment(com);
}

void Human::Collision(Organism* secondOrganism)
{
	Animal::Collision(secondOrganism);
}

void Human::RunAway()
{
	Animal::RunAway();
}

void Human::TurnOnAbility()
{
	_abilityActivated = true;
	_howManyTurns = 0;
	cout << "Immortality activated" << endl;
}

void Human::TurnOffAbility()
{
	_abilityActivated = false;
	_howManyTurns = 0;
}