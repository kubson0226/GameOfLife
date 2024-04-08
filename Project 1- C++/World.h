#ifndef Swiat_Defined
#define Swiat_Defined

#include <iostream>
#include <string.h>

using namespace std;

class Organism;
class Human;

class World
{
private:
	Organism** _organisms;
	Human* player;
	int numberOfOrganisms;
	int numberOfAliveOrganisms;
	Organism*** _environment;
	int length;				//x
	int width;				//y
	int _turn;
	bool isHumanAlive;
	string* _comments;
	int numberOfComments;
	void Activity();
public:
	World();
	World(int n, int m);
	void SetTheBoard(int n, int m);
	void SetSquare(int x, int y, Organism* organism);
	void SetTurn(int tura);
	void Comment(string comment);	
	int GetLength() const;
	int GetWidth() const;
	int GetNumberOfOrganisms() const;
	int GetTurn() const;
	Organism* GetSquare(int x, int y) const;
	Organism* GetOrganism(int i) const;
	Human* GetHuman() const;
	void AddOrganism(Organism* org);
	void RemoveOrganism(Organism* org);
	void CreateEmptyPoints(int x, int y, int* positionX, int* positionY, int* ruch, int* pointsCount);
	void MakeTurn();
	void DrawWorld();
	~World();
};
#endif;