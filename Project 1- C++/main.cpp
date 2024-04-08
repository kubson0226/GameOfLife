#include <iostream>
#include <conio.h>
#include <string>
#include <time.h>
#include "Generator.h"
#include "World.h"

#define InsertKey 224
#define ENTER 13
#define SAVE 115
#define READ 114
#define NEW 110
#define AllSpecies 10
#define FreeSpace 20			//na 10 zwierzat - po jednym z kazdego gatunku

using namespace std;

int main()
{
	srand(time(NULL));
	int n, m;
	char choice1 = NULL;
	char choice2 = NULL;
	bool loaded = true;

	cout << "Made by Jakub Kondracki ID:188767" << endl << endl;

	cout << "Hello! Welcome to Game Of Life" << endl << endl;
	cout << "Your task is to survive as long as possible as a human." << endl;
	cout << "In this world you can meet some animals and also various plants." << endl;
	cout << "However you have to be careful because there are many organisms that are stronger than you " << endl << "and can kill you if you collide with them" << endl; 
	cout << "Remember also that even if you die, the game doesn't end and you can watch other animals living their own lives." << endl;
	cout << "In any moment you can save the game by clicking S. Just remember to do it before the beginning of a turn." << endl;
	cout << "Otherwise there will be no such possibility" << endl << endl;

	cout << "Menu:" << endl;
	cout << "R) Load the game" << endl;
	cout << "N) New Game" << endl;

	World* world = nullptr;
	Generator* generator = nullptr;

	do
	{
		loaded = true;
		choice1 = _getch();
		switch (choice1)
		{
		case READ:
			world = new World();
			generator = new Generator(world);
			if (!generator->LoadWorld())
			{
				cout << "Please try again" << endl;
				loaded = false;
			}
			break;
		case NEW:
			do
			{
				cout << "Type in the size of the board (N x M): ";
				cin >> n >> m;
				system("cls");
			} while (n * m < (AllSpecies + FreeSpace));

			world = new World(n, m);
			generator = new Generator(world);
			generator->GenerateWorld();
			break;
		default:
			cout << "Wrong key, please try again" << endl;
		}
	} while ((choice1 != READ || !loaded) && choice1 != NEW);

	system("cls");
	world->DrawWorld();
	
	do
	{
		choice2 = _getch();
		switch (choice2)
		{
			case SAVE:
				generator->SaveWorld();
				break;
			case ENTER:
				world->MakeTurn();
				system("cls");
				world->DrawWorld();
				break;
			case NEW:
				system("cls");
				cout << "New Game" << endl << endl;
				do
				{
					cout << "Type in size of the board(N x M): ";
					cin >> n >> m;
					system("cls");
				} while (n * m < (AllSpecies + FreeSpace));

				world = new World(n, m);
				generator = new Generator(world);
				generator->GenerateWorld();
				system("cls");
				world->DrawWorld();
				break;
			default:
				cout << "Wrong key, please try again" << endl;
		}
	} while (true);

	delete generator;
	delete world;

	return 0;
}