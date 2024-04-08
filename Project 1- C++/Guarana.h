#ifndef Guarana_Defined
#define Guarana_Defined

#include <iostream>
#include <string.h>

#include "Plant.h"

using namespace std;

class World;
class Organism;
class Plant;

class Guarana : public Plant
{
private:
	const char _key = 'G';
	const int chance = 20;
public:
	Guarana();
	Guarana(int x, int y, World* worlds);
	char GetKey() const override;
	string GetName() const override;
	void Action() override;
	void Collision(Organism* atakujacy) override;
};

#endif