#ifndef Antylopa_Defined
#define Antylopa_Defined

#include <iostream>
#include <string.h>

#include "Animal.h"

using namespace std;

class World;
class Organism;
class Animal;

class Antelope : public Animal
{
private:
	const char _key = 'A';
public:
	Antelope();
	Antelope(int x, int y, World* world);
	void SetMovement(char moveKey) override;
	int GetLastMove() const override;
	char GetKey() const override;
	string GetName() const override;
	void Action() override;
	void Collision(Organism* secondOrganism) override;
};

#endif