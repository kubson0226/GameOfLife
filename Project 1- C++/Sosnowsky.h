#ifndef Barszcz_sosnowskiego_Defined
#define Barszcz_sosnowskiego_Defined

#include <iostream>
#include <string.h>

#include "Plant.h"

using namespace std;

class World;
class Organism;
class Plant;

class Sosnowsky : public Plant
{
private:
	const char _key = 's';
	const int chance = 15;
public:
	Sosnowsky();
	Sosnowsky(int x, int y, World* worlds);
	char GetKey() const override;
	string GetName() const override;
	void Action() override;
	void Collision(Organism* atakujacy) override;
};

#endif