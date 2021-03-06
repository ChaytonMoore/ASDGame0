#include "GameInstance.h"
#include "MainMenu.h"
#include <iostream>
#include "Editor.h"
#include "LoaderManager.h"



int main() {
	int choice = 0;
	Button::LoadFont();
	MainMenu* Menu = new MainMenu();
	choice = Menu->MenuLoop();


	ConfigData conf = getConfiguration();
	

	//choice = conf.Choice;//temp

	if (choice == 0) {
		Anim::LoadAllAnims();
		SoundData::LoadAllSounds();
		Building::LoadAllBuildings();
		getLoaderManager().loadBuildings();
		getLoaderManager().loadSoliders();
		getLoaderManager().loadWaves();
		
		GameInstance* Game = new GameInstance(GameMap::ChosenMap);
		Game->GameLoop();
	}

	
	


	if (choice == 1) {
		Anim::LoadAllAnims();
		SoundData::LoadAllSounds();
		Building::LoadAllBuildings();
		getLoaderManager().loadBuildings();
		getLoaderManager().loadSoliders();
		getLoaderManager().loadWaves();
	
		GameInstance* Game = new GameInstance(GameMap::ChosenMap);
		Game->LoadGame();
		Game->GameLoop();
	}



	//particle editor
	if (choice == 2 || choice == 3)
	{
		Anim::LoadAllAnims();
		SoundData::LoadAllSounds();
		Editor* editor = new Editor();
		editor->RunEditor(choice);
	}

}