#ifndef Zwierze_Defined
#define Zwierze_Defined

#include <iostream>
#include <string.h>

#include "Organism.h"

using namespace std;

class World;
class Organism;

class Animal : public Organism
{
private:
	void Reproduction(Organism* secondOrganism, World* world);
	Organism* CreateOrganism(int x, int y, World* world) override;
protected:
	int _lastMove;
	void MoveToEmptySquare();
	void Move(int howManySquares);
public:
	Animal();
	Animal(int strength, int ini, int x, int y, World* world);
	int GetLastMove() const override;
	virtual char GetKey() const = 0;
	virtual string GetName() const = 0;
	string Write() const override;
	void SetMovement(char moveKey) override;
	void Action() override;
	void Collision(Organism* organism) override;	
	void GoBack() override;
	void RunAway() override;
	bool IsAnimal() override;
	void DeathComment(Organism* secondOrganism) override;
};
#endif