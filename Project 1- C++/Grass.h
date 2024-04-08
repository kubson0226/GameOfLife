#ifndef Trawa_Defined
#define Trawa_Defined

#include <iostream>
#include <string.h>

#include "Plant.h"

using namespace std;

class World;
class Organism;
class Plant;

class Grass : public Plant
{
private:
	const char _key = 'g';
	const int chance = 50;
public:
	Grass();
	Grass(int x, int y, World* swiat);
	char GetKey() const override;
	string GetName() const override;
	void Action() override;
	void Collision(Organism* secondOrganism) override;
};

#endif