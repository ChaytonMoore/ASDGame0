#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Camera.h"

struct Button
{
private:
	sf::Vector2i TopLeft;
	sf::Vector2i BottomRight;

	
public:
	Button(sf::Vector2i TL, sf::Vector2i BR)
	{
		
		TopLeft = TL;
		BottomRight = BR;
	}
	Button()
	{

	}
	bool CallIfHovered()
	{
		

		bool x = sf::Mouse::getPosition().x > TopLeft.x && sf::Mouse::getPosition().x < BottomRight.x;
		bool y = sf::Mouse::getPosition().y > TopLeft.y && sf::Mouse::getPosition().y < BottomRight.y;
		
		return x && y;
	}

	void SetLoc(int x, int y, int x2, int y2)
	{
		TopLeft = sf::Vector2i(x,y);
		BottomRight = sf::Vector2i(x2,y2);
	}
	
	static sf::Font* GenericFont;
	
	static void LoadFont();

};


struct VButton : public Button
{
	sf::Sprite sprite;
	sf::Text text;
	VButton(sf::Vector2i TL, sf::Vector2i BR, std::string UIImage) : Button(TL, BR)
	{
		sf::Texture* texture = new sf::Texture();
		texture->loadFromFile("Data/UI/"+UIImage);
		sprite.setTexture(*texture);
		sprite.setPosition((sf::Vector2f)TL);
	}

	VButton(sf::Vector2i TL, sf::Vector2i BR, std::string UIImage, std::string textIn) : Button(TL, BR)
	{
		sf::Texture* texture = new sf::Texture();
		texture->loadFromFile("Data/UI/" + UIImage);
		sprite.setTexture(*texture);
		sprite.setPosition((sf::Vector2f)TL);
		text.setString(textIn);
		text.setFont(*GenericFont);
		text.setPosition((sf::Vector2f)TL);
		text.setCharacterSize(22);
	}



	void Render(sf::RenderWindow* window)
	{
		if (CallIfHovered())
		{
			//Do something here make it look different when hovered
			sprite.setColor(sf::Color(1500,1500,1500));
		}
		else
		{
			sprite.setColor(sf::Color(255, 255, 255));
		}
		window->draw(sprite);
		window->draw(text);
	}


};


struct FieldButton : public VButton
{
	float Radius;
	sf::CircleShape circle;
	sf::Vector2i AbsolutePos;
	FieldButton(sf::Vector2i TL, sf::Vector2i BR, std::string UIImage, float inRadius) : VButton(TL,BR,UIImage)
	{

		AbsolutePos = TL - sf::Vector2i(inRadius,inRadius)/2;
		Radius = inRadius;
		sprite.setOrigin(sprite.getTexture()->getSize().x/2, sprite.getTexture()->getSize().y / 2);
		circle.setOrigin(Radius/2,Radius/2);



		circle.setRadius(Radius);
		circle.setPosition((sf::Vector2f)AbsolutePos);
		circle.setFillColor(sf::Color(60,60,60,80));
		circle.setOutlineThickness(2);
		circle.setOutlineColor(sf::Color(255,216,0));
		
	}

	void Render(sf::RenderWindow* window)
	{
		circle.setPosition(((sf::Vector2f)AbsolutePos+Camera::Location)*Camera::Zoom);
		sprite.setPosition(((sf::Vector2f)AbsolutePos + Camera::Location) * Camera::Zoom);
		circle.setScale(Camera::Zoom,Camera::Zoom);
		sprite.setScale(Camera::Zoom, Camera::Zoom);
		window->draw(circle);
		window->draw(sprite);
	}
};



class HUD
{
	float ScreenX;
	float ScreenY;


	sf::Text MoneyTest;
	sf::Sprite BaseSprite;

	sf::Sprite StandardTower;
	sf::Sprite Mine;
	sf::Sprite Mage;
	


	//This is a quick thing to create a less jaring start
	sf::Texture StartingCloudTexture;
	std::vector<sf::Sprite*> StartingClouds;
	float StartingCloudOpacity = 255;
	bool StartingCloudDelete = false;


public:

	HUD();
	void Render(sf::RenderWindow* window, int money, double DeltaTime);
	VButton StandardTowerButton = VButton(sf::Vector2i(0,815),sf::Vector2i(475,1080),"UITower.png");
	VButton MineButton = VButton(sf::Vector2i(475, 815), sf::Vector2i(975, 1080), "UIMine.png");
	VButton MageButton = VButton(sf::Vector2i(975, 815), sf::Vector2i(1460, 1080), "UIMage.png");
	VButton PauseButton = VButton(sf::Vector2i(0,0),sf::Vector2i(160,40),"UIPause.png");

	int PauseMenu(sf::RenderWindow* window);

};