#include <fstream>
#include <string>
#include <Windows.h>
#include "World.h"
#include "Generator.h"
#include "Organism.h"
#include "Human.h"
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

#define AllSpecies 10
#define FreeSpace 20			//na 10 zwierzat (po jednym z kazdego gatunku)

using namespace std;

Generator::Generator(World* swiat)
{
	_world = swiat;
}

void Generator::GenerateWorld()
{
	int n = _world->GetLength();
	int m = _world->GetWidth();
	int ileZwierzatZGatunku = n * m / (AllSpecies + FreeSpace);
	int* occupiedSpace = new int[ileZwierzatZGatunku * AllSpecies + 1];
	this->GeneratingPointsForOrg(occupiedSpace, &ileZwierzatZGatunku);
	int j = 0;
	int x = occupiedSpace[j] % n;
	int y = (occupiedSpace[j] - x) / n;
	Organism* Player = new Human(x, y, _world);
	_world->AddOrganism(Player);
	j++;
	for (int i = 0; i < ileZwierzatZGatunku; i++)
	{
		ReadCoordinates(occupiedSpace, &x, &y, &j);
		Organism* wolf = new Wolf(x, y, _world);
		_world->AddOrganism(wolf);

		ReadCoordinates(occupiedSpace, &x, &y, &j);
		Organism* sheep = new Sheep(x, y, _world);
		_world->AddOrganism(sheep);

		ReadCoordinates(occupiedSpace, &x, &y, &j);
		Organism* fox = new Fox(x, y, _world);
		_world->AddOrganism(fox);

		ReadCoordinates(occupiedSpace, &x, &y, &j);
		Organism* turtle = new Turtle(x, y, _world);
		_world->AddOrganism(turtle);

		ReadCoordinates(occupiedSpace, &x, &y, &j);
		Organism* antelope = new Antelope(x, y, _world);
		_world->AddOrganism(antelope);

		ReadCoordinates(occupiedSpace, &x, &y, &j);
		Organism* grass = new Grass(x, y, _world);
		_world->AddOrganism(grass);

		ReadCoordinates(occupiedSpace, &x, &y, &j);
		Organism* sowThistle = new SowThistle(x, y, _world);
		_world->AddOrganism(sowThistle);

		ReadCoordinates(occupiedSpace, &x, &y, &j);
		Organism* guarana = new Guarana(x, y, _world);
		_world->AddOrganism(guarana);

		ReadCoordinates(occupiedSpace, &x, &y, &j);
		Organism* bell = new Belladonna(x, y, _world);
		_world->AddOrganism(bell);

		ReadCoordinates(occupiedSpace, &x, &y, &j);
		Organism* hog = new Sosnowsky(x, y, _world);
		_world->AddOrganism(hog);
	}
}

bool Generator::LoadWorld()
{
	bool result = true;
	const string plik = "dane.txt";
	ifstream odczyt(plik.c_str());
	if (odczyt.good())
	{
		int n, m, tura, liczbaOrg;
		odczyt >> n >> m >> tura >> liczbaOrg;
		_world->SetTheBoard(n, m);
		_world->SetTurn(tura);

		string name, name2;
		int sila, inicjatywa, x, y, wiek, umiejetnoscAktywowana, turyZUmiejetnoscia;
		bool aktywowana;
		for (int i = 0; i < liczbaOrg; i++)
		{
			odczyt >> name;
			if (name == "Sow" || name == "Sosnowsky")
			{
				odczyt >> name2;
				name += " " + name2;
			}
			odczyt >> sila >> inicjatywa >> x >> y >> wiek;
			if (name == "Human")
			{
				odczyt >> umiejetnoscAktywowana >> turyZUmiejetnoscia;
				Organism* org = new Human(x - 1, y - 1, _world);
				org->SetStrength(sila);
				org->SetInitiative(inicjatywa);
				org->SetAge(wiek);
				if (umiejetnoscAktywowana == 0) aktywowana = false;
				else aktywowana = true;
				_world->AddOrganism(org);
				_world->GetHuman()->SetIsAbilityActive(aktywowana);
				_world->GetHuman()->SetHowManyTurns(turyZUmiejetnoscia);
			}
			else
			{
				LoadOrganism(name, sila, inicjatywa, x - 1, y - 1, wiek);
			}
		}
		odczyt.close();
		cout << "Game was loaded" << endl;
	}
	else
	{
		cout << "File not found" << endl;
		result = false;
	}
	Sleep(2000);
	return result;
}

void Generator::SaveWorld()
{
	ofstream zapis("dane.txt");
	int liczbaOrg = _world->GetNumberOfOrganisms();
	zapis << _world->GetLength() << " " << _world->GetWidth() << " " << _world->GetTurn() << " " << liczbaOrg << endl;
	Organism* org = nullptr;
	for (int i = 0; i < liczbaOrg; i++)
	{
		org = _world->GetOrganism(i);
		zapis << org->Write() << endl;
	}
	zapis.close();
	cout << "Game was saved" << endl;
}

void Generator::GeneratingPointsForOrg(int* squares, int* howManyAnimals)
{
	int n = _world->GetLength();
	int m = _world->GetWidth();
	int ileMiejsc = (*howManyAnimals) * AllSpecies + 1;		//+1 bo czlowiek
	int* wszystkiePola = new int[n * m];
	int los;
	for (int i = 0; i < n * m; i++)
	{
		wszystkiePola[i] = 0;
	}
	for (int i = 0; i < ileMiejsc; i++)
	{
		do
		{
			los = rand() % (n * m);
		} while (wszystkiePola[los] == 1);
		wszystkiePola[los] = 1;
		squares[i] = los;
	}
}

void Generator::ReadCoordinates(int* squares, int* x, int* y, int* which)
{
	int n = _world->GetLength();
	*x = squares[*which] % n;
	*y = (squares[*which] - *x) / n;
	(*which)++;
}

void Generator::LoadOrganism(string nazwa, int sila, int ini, int x, int y, int wiek)
{
	Organism* org = nullptr;
	if (nazwa == "Wolf")
	{
		org = new Wolf(x, y, _world);
	}
	else if (nazwa == "Sheep")
	{
		org = new Sheep(x, y, _world);
	}
	else if (nazwa == "Fox")
	{
		org = new Fox(x, y, _world);
	}
	else if (nazwa == "Turtle")
	{
		org = new Turtle(x, y, _world);
	}
	else if (nazwa == "Antelope")
	{
		org = new Antelope(x, y, _world);
	}
	else if (nazwa == "Grass")
	{
		org = new Grass(x, y, _world);
	}
	else if (nazwa == "Sow Thistle")
	{
		org = new SowThistle(x, y, _world);
	}
	else if (nazwa == "Guarana")
	{
		org = new Guarana(x, y, _world);
	}
	else if (nazwa == "Sosnowsky hogweed")
	{
		org = new Sosnowsky(x, y, _world);
	}
	else if (nazwa == "Belladonna")
	{
		org = new Belladonna(x, y, _world);
	}
	if (org != nullptr)
	{
		org->SetStrength(sila);
		org->SetInitiative(ini);
		org->SetAge(wiek);
		_world->AddOrganism(org);
	}
	else
	{
		cout << "Couldn't read from the file " << nazwa << endl;
	}
}

Generator::~Generator()
{
	delete _world;
}