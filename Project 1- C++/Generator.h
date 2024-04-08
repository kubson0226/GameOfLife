#ifndef Generator_swiata_Defined
#define Generator_swiata_Defined

#include <iostream>
#include <string.h>

using namespace std;

class World;

class Generator
{
private:
	World* _world;
	void GeneratingPointsForOrg(int* squares, int* howManyAnimals);
	void ReadCoordinates(int* squares, int* x, int* y, int* which);
	void LoadOrganism(string name, int strength, int ini, int x, int y, int year);
public:
	Generator(World* swiat);
	void GenerateWorld();
	bool LoadWorld();
	void SaveWorld();
	~Generator();
};
#endif;