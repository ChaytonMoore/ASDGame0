#pragma once
#include "Entity.h"
#include "Projectile.h"
#include "Soldier.h"


struct ProjectileData
{
	sf::Texture Texture;
	std::string effectType;
	int Damage;
	float Speed;
	float TimeGap;
	float TimeExists;
};


struct BuildingData
{
	int size;
	int Surrounding;
	int PDamage;
	int PSpeed;
	float PTimeExists;
	float PTimeGap;
	float PTimeGapVariance;
	int Health;
	int Range;
	std::map<std::string, std::string> AudioComps;
	std::vector<std::string> Comps;
	std::vector<float> CompRots;
	std::vector<sf::Vector2f> CompLocs;
	std::vector<sf::Vector2f> CompScales;

	BuildingData(std::string file);
};

class Building : public Entity
{
public:
	Building(std::string buildingName, std::string componentName, std::string buildingType, std::string effectType, int damage, float speed, float timeExists, float timeGap,
		float attackDelay, int health, int size, int range, int cost);
	Building(Building* building, sf::Vector2f loc);
	Building(std::string inName, sf::Vector2f Loc);
	void EntityLogic(double DeltaTime, std::vector<Projectile*>* projectiles, std::vector<Soldier*> Targets);
	void Upgrade();
	float UpgradeCost();

	std::string ComponentName;
	std::string BuildingType;
	std::string EffectType;
	int currentLevel = 0;
	int Cost;
	float Range;
	float UsingTerrain = 50;
	ProjectileData ProjectileInst;
	sf::Vector2f AimingDirection = sf::Vector2f(0, 0);
	std::vector<Building*> upgrades;

	static bool NotWithinBuilding(std::vector<Building*> buildings, sf::Vector2f point);

	static int GetIndexOfHoveredTower(std::vector<Building*> buildings, sf::Vector2f point);

	static void LoadAllBuildings();

	static std::map<std::string, BuildingData> BuildingList;
private:
	void setStatTo(Building* building);
};


