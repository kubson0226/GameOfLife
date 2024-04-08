#ifndef Mlecz_Defined
#define Mlecz_Defined

#include <iostream>
#include <string.h>

#include "Plant.h"

using namespace std;

class World;
class Organism;
class Plant;

class SowThistle : public Plant
{
private:
	const char _key = 'm';
	const int chance = 30;
public:
	SowThistle();
	SowThistle(int x, int y, World* swiat);
	char GetKey() const override;
	string GetName() const override;
	void Action() override;
	void Collision(Organism* atakujacy) override;

};

#endif