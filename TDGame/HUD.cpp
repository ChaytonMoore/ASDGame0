#include "HUD.h"
#include "GameInstance.h"
#include "StandardIO.h"

void HUD::Render(sf::RenderWindow* window, int money, double DeltaTime)
{


	for (sf::Sprite* i : StartingClouds)
	{
		window->draw(*i);
		if (i->getPosition().x < ScreenX / 2)
		{
			i->move(-DeltaTime * 400, 0);
		}
		else
		{
			i->move(DeltaTime * 400, 0);
		}
		i->setColor(sf::Color(255,255,255,StartingCloudOpacity));
		StartingCloudOpacity -= DeltaTime*0.6;
		StartingCloudDelete = StartingCloudOpacity < 0;
	}
	if (StartingCloudDelete && StartingClouds.size())
	{
		for (sf::Sprite* i : StartingClouds)
		{
			delete i;
		}
		StartingClouds.clear();
	}


	MoneyTest.setString("Gold: "+std::to_string(money));
	window->draw(MoneyTest);
	window->draw(BaseSprite);
	StandardTowerButton.Render(window);
	MineButton.Render(window);
	MageButton.Render(window);
	PauseButton.Render(window);




}

int HUD::PauseMenu(sf::RenderWindow* window)
{


	VButton GobackButton(sf::Vector2i(900,400),sf::Vector2i(1020,450),"PauseMenu/back.png");
	VButton ExitButton(sf::Vector2i(900, 600), sf::Vector2i(1020, 650), "PauseMenu/exit.png");
	VButton SaveButton(sf::Vector2i(900, 800), sf::Vector2i(1020, 850), "PauseMenu/save.png");

	while (true)
	{
		window->clear();
		GobackButton.Render(window);
		ExitButton.Render(window);
		SaveButton.Render(window);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (GobackButton.CallIfHovered())
			{
				return 0;
			}
			if (ExitButton.CallIfHovered())
			{
				exit(0);
			}
			if (SaveButton.CallIfHovered()) //yes this isn't ideal but it's good enough probably
			{
				return 1;
			}
		}



		window->display();
	}

}





sf::Font* Button::GenericFont;


void Button::LoadFont()
{
	sf::Font* font = new sf::Font();
	if (!font->loadFromFile("Data/UI/UI.ttf"))
	{
		// error...
	}
	Button::GenericFont = font;

}


HUD::HUD()
{

	ConfigData Config = getConfiguration();
	ScreenX = Config.ScreenX;
	ScreenY = Config.ScreenY;



	if (StartingCloudTexture.loadFromFile("Data/UI/StartingCloud.png"))
	{
		//TODO
	}
	//set up the clouds that will appear initially when the game starts.
	for (size_t i = 0; i < 20; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			StartingClouds.push_back(new sf::Sprite());
			StartingClouds.back()->setTexture(StartingCloudTexture);
			StartingClouds.back()->setPosition(i*100,j*100);
			StartingClouds.back()->setRotation(Utils::RandomFloatInRange(360));
		}

	}






	//second thing is the main UI element
	sf::Texture* UIT = new sf::Texture();
	if (!UIT->loadFromFile("Data/UI/UIbase.png"))
	{
		//TODO
	}
	BaseSprite.setTexture(*UIT);

	//Need to make the UI the correct size for the user's screensize
	float ScaleX = (float)Config.ScreenX / UIT->getSize().x;
	float ScaleY = (float)Config.ScreenY / UIT->getSize().y;

	MoneyTest.setFont(*Button::GenericFont);
	MoneyTest.setPosition(((float)Config.ScreenX) / 100 + ScaleX*200, ((float)Config.ScreenY) / 100);

	sf::Texture* UITower = new sf::Texture();
	if (!UITower->loadFromFile("Data/UI/UITower.png"))
	{
		//TODO
	}
	StandardTower.setTexture(*UITower);
	StandardTower.setPosition(0, Config.ScreenY*0.75);

	sf::Texture* UIMine = new sf::Texture();
	if (!UIMine->loadFromFile("Data/UI/UIMine.png"))
	{
		//TODO
	}
	Mine.setTexture(*UIMine);
	Mine.setPosition(600 * ScaleX, Config.ScreenY * 0.75);

	sf::Texture* UIMage = new sf::Texture();
	if (!UIMage->loadFromFile("Data/UI/UIMage.png"))
	{
		//TODO
	}
	Mage.setTexture(*UIMage);
	Mage.setPosition(1200 * ScaleX, Config.ScreenY * 0.75);


	BaseSprite.setScale(ScaleX,ScaleY);
	StandardTower.setScale(ScaleX,ScaleY);
	Mine.setScale(ScaleX,ScaleY);
	Mage.setScale(ScaleX,ScaleY);


	//StandardTowerButton.SetLoc(0,Config.ScreenY-ScaleY*200,ScaleX*600,Config.ScreenY);
	//MineButton.SetLoc(600, Config.ScreenY - ScaleY * 200, ScaleX * 600 + 600, Config.ScreenY);
	//MageButton.SetLoc(1200, Config.ScreenY - ScaleY * 200, ScaleX * 600 + 1200, Config.ScreenY);
	

}