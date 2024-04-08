#ifndef Wilcze_jagody_Defined
#define Wilcze_jagody_Defined

#include <iostream>
#include <string.h>

#include "Plant.h"

using namespace std;

class World;
class Organism;
class Plant;

class Belladonna : public Plant
{
private:
	const char _key = 'b';
	const int chance = 20;
public:
	Belladonna();
	Belladonna(int x, int y, World* swiat);
	char GetKey() const override;
	string GetName() const override;
	void Action() override;
	void Collision(Organism* secondOrganism) override;
};

#endif