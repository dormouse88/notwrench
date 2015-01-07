#pragma once
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include "Box.h"
#include "LevelPack.h"
#include <vector>

class App
{
public:
	App(void);
	~App(void);
	void Run();
	void DoLogicAndDraw();
	void BaseHandleInput();
private:
	sf::RenderWindow window;
	int groove;
	BoxSeq boxes;
	Hero hero;
	LevelPack levelPack;
};

