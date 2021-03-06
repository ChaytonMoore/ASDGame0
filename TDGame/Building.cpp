#include "Building.h"
#include <iostream>
#include <filesystem>
#include <fstream>

Building::Building(std::string buildingName, std::string componentName, std::string buildingType, std::string effectType, int damage, float speed, float timeExists, float timeGap,
	float attackDelay, int health, int size, int range, int cost) : Entity(buildingName) {
	if (!componentName.empty())
		Components.push_back(new Component(componentName));

	ComponentName = componentName;
	ProjectileInst.effectType = effectType;
	ProjectileInst.Damage = damage;
	ProjectileInst.Speed = speed;
	ProjectileInst.TimeExists = timeExists;
	ProjectileInst.TimeGap = timeGap;
	BuildingType = buildingType;
	EffectType = effectType;
	AttackDelay = attackDelay;
	Health = health;
	this->size = size;
	Range = range;
	Cost = cost;
}

Building::Building(Building* building, sf::Vector2f loc) : Entity(building->Name) {
	setStatTo(building);

	if (this->upgrades.empty()) {
		//std::cout << "[DEBUG] Copying upgrades list " << building->upgrades.size() << std::endl;

		this->upgrades = building->upgrades;
	}

	this->Loc = loc;
}

void Building::EntityLogic(double DeltaTime, std::vector<Projectile*>* projectiles, std::vector<Soldier*> Targets)
{
	if (CountdownToNextAttack <= 0)
	{
		CountdownToNextAttack = AttackDelay;
		if (AimingDirection != sf::Vector2f(0, 0))
		{
			if (BuildingType == "Mage")
			{
				
				projectiles->push_back(new Projectile(ProjectileInst.Speed, ProjectileInst.Damage, ProjectileInst.TimeExists, AimingDirection, EffectType, "Magic"));
				projectiles->back()->Loc = Loc;


				projectiles->push_back(new Projectile(ProjectileInst.Speed, ProjectileInst.Damage, ProjectileInst.TimeExists, AimingDirection, EffectType, "Magic"));
				projectiles->back()->Loc = Loc + sf::Vector2f(std::rand() % 20 - 10, std::rand()%20-10);

				projectiles->push_back(new Projectile(ProjectileInst.Speed, ProjectileInst.Damage, ProjectileInst.TimeExists, AimingDirection, EffectType, "Magic"));
				projectiles->back()->Loc = Loc+sf::Vector2f(std::rand() % 20 - 10, std::rand() % 20 - 10);

			}
			if (BuildingType == "Tower")
			{

				projectiles->push_back(new Projectile(ProjectileInst.Speed, ProjectileInst.Damage, ProjectileInst.TimeExists, AimingDirection, EffectType, "Arrow"));

				projectiles->back()->Loc = Loc;

			}


			std::map<std::string, SoundComponent*>::iterator it;

			for (it = AudioComponents.begin(); it != AudioComponents.end(); it++) {
				it->second->Audio.play();
			}

			//AudioComponents.at("Fire")->Audio.play();

		}
	}
	else
	{
		CountdownToNextAttack -= DeltaTime;
	}

}

void Building::Upgrade() {
	if (currentLevel + 1 >= upgrades.size()) {
		std::cout << "[DEBUG] Level Max! YAY :D" << std::endl;

		return;
	}

	setStatTo(upgrades[++currentLevel]);
}

float Building::UpgradeCost() {
	if (currentLevel + 1 >= upgrades.size()) {
		std::cout << "[DEBUG] Level Max! YAY :D" << std::endl;

		return 0;
	}

	return upgrades[currentLevel + 1]->Cost;
}

void Building::setStatTo(Building* building) {
	if (!building->ComponentName.empty())
		Components.push_back(new Component(building->ComponentName));

	if(building->BuildingType.length() != 0)
		BuildingType = building->BuildingType;

	if(building->EffectType.length() != 0)
		EffectType = building->EffectType;

	if(building->ProjectileInst.effectType.length() != 0)
		ProjectileInst.effectType = building->ProjectileInst.effectType;

	if (building->ProjectileInst.Damage != 0)
		ProjectileInst.Damage = building->ProjectileInst.Damage;

	if (building->ProjectileInst.Speed != 0)
		ProjectileInst.Speed = building->ProjectileInst.Speed;

	if (building->ProjectileInst.TimeExists != 0)
		ProjectileInst.TimeExists = building->ProjectileInst.TimeExists;

	if (building->ProjectileInst.TimeGap != 0)
		ProjectileInst.TimeGap = building->ProjectileInst.TimeGap;

	if (building->AttackDelay != 0)
		AttackDelay = building->AttackDelay;

	if (building->Health != 0)
		Health = building->Health;

	if (building->Range != 0)
		Range = building->Range;

	if (building->size != 0)
		this->size = building->size;
	
	Cost = building->Cost;

	std::map<std::string, SoundComponent*>::iterator it;

	for (it = building->AudioComponents.begin(); it != building->AudioComponents.end(); it++) {
		AudioComponents.emplace(it->first, it->second);
	}
}

bool Building::NotWithinBuilding(std::vector<Building*> buildings, sf::Vector2f point)
{
	for (Building* i : buildings)
	{
		if (i->DistanceTo(point) < i->size + i->UsingTerrain)
		{
			return false;
		}
	}

	return true;
}

int Building::GetIndexOfHoveredTower(std::vector<Building*> buildings, sf::Vector2f point)
{
	int idx = 0;

	for (Building* i : buildings)
	{
		if (i->DistanceTo(point) < i->size)
		{
			return idx;
		}
		idx++;
	}

	return -1;
}

std::map<std::string, BuildingData> Building::BuildingList;

namespace fs = std::filesystem;

void Building::LoadAllBuildings()
{

	for (const auto& entry : fs::directory_iterator("Data/Buildings"))
	{
		BuildingData tmp = BuildingData(entry.path().filename().string());
		BuildingList.emplace(entry.path().filename().stem().string(), tmp);
	}

}

//put this somewhere else
std::string ReadString(std::ifstream* inp)
{
	uint8_t len;
	inp->read((char*)&len, 1);
	std::string out;
	char tmp[255];
	inp->read(tmp, len);
	tmp[len] = '\0';
	out = tmp;
	return out;
}


BuildingData::BuildingData(std::string file)
{
	std::ifstream ifs("Data/Buildings/" + file, std::fstream::binary);

	int version; //probably add an if here
	ifs.read((char*)&version, 4);
	ReadString(&ifs);
	ifs.read((char*)&Health, 4);
	ifs.read((char*)&PDamage, 4);
	ifs.read((char*)&PTimeGap, 4);
	ifs.read((char*)&size, 4);
	ifs.read((char*)&Range, 4);
	ifs.read((char*)&Surrounding, 4);
	ReadString(&ifs);



}