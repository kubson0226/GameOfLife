#ifndef Zolw_Defined
#define Zolw_Defined

#include <iostream>
#include <string.h>

#include "Animal.h"

using namespace std;

class World;
class Organism;
class Animal;

class Turtle : public Animal
{
private:
	const char _key = 'T';
public:
	Turtle();
	Turtle(int x, int y, World* swiat);
	int GetLastMove() const override;
	char GetKey() const override;
	string GetName() const override;
	void SetMovement(char ruch) override;
	void Action() override;
	void Collision(Organism* atakujacy) override;
};

#endif