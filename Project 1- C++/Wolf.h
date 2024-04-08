#ifndef Wilk_Defined
#define Wilk_Defined

#include <iostream>
#include <string.h>

#include "Animal.h"

using namespace std;

class World;
class Organism;
class Animal;

class Wolf : public Animal
{
private:
	const char _key = 'W';
public:
	Wolf();
	Wolf(int x, int y, World* swiat);
	int GetLastMove() const override;
	char GetKey() const override;
	string GetName() const override;
	void SetMovement(char moveKey) override;
	void Action() override;
	void Collision(Organism* secondOrganism) override;
};

#endif