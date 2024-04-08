#include <conio.h>
#include <string>
#include "Organism.h"
#include "Human.h"
#include "World.h"
#include "Wolf.h"
#include "Sheep.h"
#include "Fox.h"
#include "Turtle.h"
#include "Antelope.h"
#include "Grass.h"
#include "SowThistle.h"
#include "Guarana.h"
#include "Belladonna.h"
#include "Sosnowsky.h"

#define InsertKey 224
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4
#define UPARROW 72
#define RIGHTARROW 77
#define DOWNARROW 80
#define LEFTARROW 75
#define KOMENTARZE_NA_ORG 5

using namespace std;

World::World() : World(20, 20)
{
	
}

World::World(int n, int m)
{
	length = n;
	width = m;

	numberOfAliveOrganisms = 0;
	numberOfOrganisms = 0;
	_turn = 0;
	isHumanAlive = false;
	player = nullptr;
	_comments = new string[KOMENTARZE_NA_ORG * n * m];
	numberOfComments = 0;

	_organisms = new Organism * [length * width];

	_environment = new Organism ** [m + 2];
	for (int y = 0; y < (m + 2); y++)
	{
		_environment[y] = new Organism * [n + 2];
	}
		
	for (int y = 0; y < (m + 2); y++)
	{
		for (int x = 0; x < (n + 2); x++)
		{
			_environment[y][x] = nullptr;
		}
	}
}

void World::SetTheBoard(int n, int m)
{
	length = n;
	width = m;
}

void World::SetSquare(int x, int y, Organism* org)
{
	_environment[y][x] = org;
}

void World::SetTurn(int turn)
{
	_turn = turn;
}

void World::Comment(string comment)
{
	_comments[numberOfComments] = comment;
	numberOfComments++;
}

int World::GetLength() const
{
	return length;
}

int World::GetWidth() const
{
	return width;
}

int World::GetNumberOfOrganisms() const
{
	return numberOfOrganisms;
}

int World::GetTurn() const
{
	return _turn;
}

Organism* World::GetSquare(int x, int y) const
{
	if ((x > 0) && (x < length + 2) && (y > 0) && (y < width + 2))
	{
		return _environment[y][x];
	}
	return nullptr;
}

Organism* World::GetOrganism(int i) const
{
	return _organisms[i];
}

Human* World::GetHuman() const
{
	return player;
}

void World::AddOrganism(Organism* org)
{
	string com;
	if ((numberOfOrganisms < length * width) && (_environment[org->GetY()][org->GetX()] == nullptr)) 
	{
		_organisms[numberOfOrganisms] = org;
		numberOfOrganisms++;
		if (numberOfOrganisms > 1 && org->IsAnimal())
		{
			Organism* organism;
			int i = 0;
			while (i < numberOfOrganisms && _organisms[i]->GetInitiative() >= org->GetInitiative())
			{
				i++;
			}
			for (int j = numberOfOrganisms - 2; j >= i; j--)
			{
				organism = _organisms[j];
				_organisms[j] = _organisms[j + 1];
				_organisms[j + 1] = organism;
			}
		}

		org->Draw();
		if (typeid(*org) == typeid(Human))
		{
			isHumanAlive = true;
			player = dynamic_cast<Human*>(org);
		}
		
		com = org->GetName() + ": \tcreating new organism (" + to_string(org->GetX()) + ", ";
		com += to_string(org->GetY()) + ")";
		this->Comment(com);
	}
	else if ((numberOfOrganisms < length * width) && (_environment[org->GetY()][org->GetX()] != nullptr))
	{
		delete org;
	}
	else if (numberOfOrganisms >= length * width)
	{
		com = "You cannot add more organisms";
		this->Comment(com);
	}
	
}

void World::RemoveOrganism(Organism* org)
{
	string com;
	Organism* predator;
	Organism* victim;
	bool escaped = true;
	if (org == player && player->IsAbilityActive())
	{
		player->RunAway();
		if (player->GetLastMove() == 0)
		{
			escaped = false;
		}
		else
		{
			com = "Human succesfully escaped";
			this->Comment(com);
			victim = _environment[org->GetY()][org->GetX()];
			if (victim == nullptr)
			{
				player->Draw();
			}
			else
			{
				victim->Collision(player);
			}
		}
	}
	if (org != player || !player->IsAbilityActive() || !escaped)
	{
		victim = _environment[org->GetY()][org->GetX()];
		if (victim == org)
		{
			_environment[org->GetY()][org->GetX()] = nullptr;
		}
		if (typeid(*org) == typeid(Human))
		{
			isHumanAlive = false;
		}
		for (int i = 0; i < numberOfOrganisms; i++)
		{
			if (_organisms[i] == org)
			{
				_organisms[i] = nullptr;
				for (int j = i; j < numberOfOrganisms - 1; j++)
				{
					predator = _organisms[j];
					_organisms[j] = _organisms[j + 1];
					_organisms[j + 1] = predator;
				}
				i = numberOfOrganisms;
			}
		}
		numberOfOrganisms--;
		numberOfAliveOrganisms--;

		com = org->GetName() + ": \torganism died";
		this->Comment(com);
		delete org;
	}
}

void World::CreateEmptyPoints(int x, int y, int* positionX, int* positionY, int* move, int* pointsCount)
{
	if (y - 1 != 0 && _environment[y - 1][x] == nullptr)
	{
		positionX[*pointsCount] = x;
		positionY[*pointsCount] = y - 1;
		move[*pointsCount] = UP;
		(*pointsCount)++;
	}
	if (x + 1 != length + 1 && _environment[y][x + 1] == nullptr)
	{
		positionX[*pointsCount] = x + 1;
		positionY[*pointsCount] = y;
		move[*pointsCount] = RIGHT;
		(*pointsCount)++;
	}
	if (y + 1 != width + 1 && _environment[y + 1][x] == nullptr)
	{
		positionX[*pointsCount] = x;
		positionY[*pointsCount] = y + 1;
		move[*pointsCount] = DOWN;
		(*pointsCount)++;
	}
	if (x - 1 != 0 && _environment[y][x - 1] == nullptr)
	{
		positionX[*pointsCount] = x - 1;
		positionY[*pointsCount] = y;
		move[*pointsCount] = LEFT;
		(*pointsCount)++;
	}
}

void World::MakeTurn()
{
	numberOfAliveOrganisms = numberOfOrganisms;
	if (isHumanAlive)
	{
		cout << endl;
		if (!player->IsAbilityActive() && player->GetHowManyTurnsActive() >= 5)
		{
			cout << "To activate Immortality press I" << endl;
		}
		else if (!player->IsAbilityActive() && player->GetHowManyTurnsActive() == 0)
		{
			cout << "Immortality deactivated" << endl;
		}
		cout << "Move your character by one of the arrow keys (You are 'X')" << endl;
	}
	bool canIMove = true;

	if (isHumanAlive)
	{
		unsigned char sign = _getch();
		unsigned char sign2 = '0';

		switch (sign)
		{
			case 'i':
				if (!player->IsAbilityActive())
				{
					player->TurnOnAbility();
					sign2 = _getch();
				}
				if ((sign2 != InsertKey) || (sign2 == '0' && player->IsAbilityActive()))
				{
					cout << "Wrong key, try again" << endl;
					canIMove = false;
					break;
				}
			case InsertKey:
				sign = _getch();
				player->SetMovement(sign);
				break;
			default:
				cout << "Wrong key, try again" << endl;
				canIMove = false;
				break;
		}
	}
	if (canIMove)
	{
		Activity();
	}
}

void World::Activity()
{
	Organism* org;
	Organism* victim;
	Organism* predator;
	for (int i = 0; i < numberOfAliveOrganisms; i++)
	{

		org = _organisms[i];
		org->Action();
		victim = _environment[org->GetY()][org->GetX()];	
		if (victim == nullptr || org->GetLastMove() == 0)
		{
			org->Draw();
		}
		else
		{
			victim->Collision(org);
		}
	}
	for (int i = 0; i < numberOfAliveOrganisms; i++)
	{
		org = _organisms[i];
		org->SetAge(org->GetAge() + 1);
	}
	if (isHumanAlive)
	{
		player->SetHowManyTurns(player->GetHowManyTurnsActive() + 1);
		if (player->IsAbilityActive() && player->GetHowManyTurnsActive() == 5)
		{
			player->TurnOffAbility();
		}
	}
	_turn++;
}

void World::DrawWorld()
{
	cout << "Made by Jakub Kondracki ID:188767" << endl << endl;
	cout << "Turn: " << _turn << endl;
	cout << endl << "N) New game" << endl;
	cout << "S) Save progress" << endl;
	cout << "To start a turn press ENTER" << endl << endl;

	for (int i = 0; i < numberOfOrganisms; i++)
	{
		_organisms[i]->Draw();
	}

	for (int y = 0; y < (width + 2); y++)
	{
		for (int x = 0; x < (length + 2); x++)
		{
			if (GetSquare(x, y) == nullptr)
			{
				if ((x == 0) || (y == 0) || (x == length + 1) || (y == width + 1))
					cout << '%';
				else
					cout << ' ';
			}
			else
			{
				cout << GetSquare(x, y)->GetKey();
			}
		}
		cout << endl;
	}
	
	cout << endl;

	for (int i = 0; i < numberOfComments; i++)
	{
		cout << _comments[i] << endl;
	}
	numberOfComments = 0;
}

World::~World()
{
	delete[] _organisms;
	delete player;
	for (int y = 0; y < width; y++)
	{
		for (int x = 0; x < length; x++)
		{
			delete _environment[y];
		}
	}
	delete[] _comments;

}