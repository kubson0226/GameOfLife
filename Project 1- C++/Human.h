#ifndef Czlowiek_Defined
#define Czlowiek_Defined

#include <iostream>
#include <string.h>

#include "Animal.h"

using namespace std;

class World;
class Organism;
class Animal;

class Human : public Animal
{
private:
	const char _key = 'X';
	bool _abilityActivated;
	int _howManyTurns;
public:
	Human(int x, int y, World* world);
	bool IsAbilityActive() const;
	int GetLastMove() const override;
	int GetHowManyTurnsActive() const;
	char GetKey() const override;
	string GetName() const override;
	string Write() const override;
	void SetMovement(char moveKey) override;
	void SetIsAbilityActive(bool abilityActivated);
	void SetHowManyTurns(int turns);
	void Action() override;
	void Collision(Organism* atakujacy) override;
	void RunAway() override;
	void TurnOnAbility();
	void TurnOffAbility();
};
#endif