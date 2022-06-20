#include<iostream>
#include "Building.h"
#include "Soldier.h"

struct Condition {
	std::string name;
	int condition;


	Condition(std::string name, int condition) {

		this->name = name;
		this->condition = condition;
	}
};

struct Wave {
	std::string name;
	std::vector<Soldier*> soldiers;

	std::vector<Condition*> conditions;

	Wave(std::string name) {
		this->name = name;
	}
};

class LoaderManager {
public:
	/*
	* No clue how to use arrays in c++...
	* change it to an array - It's much faster.
	*/
	std::vector<Building*> buildings;
	std::vector<Soldier*> soldiers;
	std::vector<Effect*> effects{
		new Fire()
	};
	std::vector<Wave*> waves;

	void loadBuildings();
	void loadSoliders();
	void loadWaves();
	Building* getBuilding(std::string name);
	Soldier* getSoldier(std::string name);
	Effect* getEffects(std::string type);
	std::vector<Wave*> getWaves();
};

LoaderManager& getLoaderManager();