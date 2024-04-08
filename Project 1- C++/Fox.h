#ifndef Lis_Defined
#define Lis_Defined

#include <iostream>
#include <string.h>

#include "Animal.h"

using namespace std;

class World;
class Organism;
class Animal;

class Fox : public Animal
{
private:
	const char _key = 'F';
public:
	Fox();
	Fox(int x, int y, World* world);
	void SetMovement(char moveKey) override;
	int GetLastMove() const override;
	char GetKey() const override;
	string GetName() const override;
	void Action() override;
	void Collision(Organism* atakujacy) override;
};

#endif