#ifndef Owca_Defined
#define Owca_Defined

#include <iostream>
#include <string.h>

#include "Animal.h"

using namespace std;

class World;
class Organism;
class Animal;

class Sheep : public Animal
{
private:
	const char _key = 'S';
public:
	Sheep();
	Sheep(int x, int y, World* swiat);
	int GetLastMove() const override;
	char GetKey() const override;
	string GetName() const override;
	void SetMovement(char ruch) override;
	void Action() override;
	void Collision(Organism* atakujacy) override;
};

#endif