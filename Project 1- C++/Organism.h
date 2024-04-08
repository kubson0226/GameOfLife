#ifndef Organizm_Defined
#define Organizm_Defined

#include <iostream>
#include <string.h>

using namespace std;

class World;

class Organism
{
protected:	
	int strengthOfAnimal;
	int initiativeOfAnimal;
	int _x;
	int _y;
	int yearOfAnimal;
	World* _world;
	virtual Organism* CreateOrganism(int x, int y, World* swiat) = 0;
public:
	Organism();
	Organism(int strength, int initiative, int x, int y, World* world);
	void SetStrength(int strength);
	void SetInitiative(int initiative);
	void SetCoordinates(int x, int y);
	void SetAge(int year);
	void SetWorld(World* world);
	void Draw();
	int GetStrength() const;
	int GetInitiative() const;
	int GetX() const;
	int GetY() const;
	int GetAge() const;
	World* GetWorld() const;
	virtual void SetMovement(char moveKey) = 0;
	virtual int GetLastMove() const = 0;
	virtual char GetKey() const = 0;
	virtual string GetName() const = 0;
	virtual string Write() const = 0;
	virtual void Action() = 0;
	virtual void Collision(Organism* secondOrganism) = 0;
	virtual void GoBack() = 0;
	virtual void RunAway() = 0;
	virtual bool IsAnimal() = 0;
	virtual void DeathComment(Organism* organism) = 0;
};

#endif