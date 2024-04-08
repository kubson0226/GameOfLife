#ifndef Roslina_Defined
#define Roslina_Defined

#include <iostream>
#include <string.h>

#include "Organism.h"

using namespace std;

class World;
class Organism;

class Plant : public Organism
{
protected:
	Organism* CreateOrganism(int x, int y, World* world) override;
public:
	Plant();
	Plant(int sila, int x, int y, World* swiat);
	int GetLastMove() const override;
	virtual char GetKey() const = 0;
	virtual string GetName() const = 0;
	string Write() const override;
	bool IsAnimal() override;
	void DeathComment(Organism* atakowany) override;
	void Action() override;
	void Collision(Organism* atakujacy) override;
	void SetMovement(char ruch) override;
	void GoBack() override;
	void RunAway() override;
};
#endif