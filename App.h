#pragma once
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include "Box.h"
#include "LevelPack.h"
#include "SoundGen.hpp"
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
        sf::RenderTexture preShader;
        sf::Shader shader;
	int groove;
	BoxSeq boxes;
	Hero hero;
	LevelPack levelPack;
        SoundGen soundGen;
        bool quitYet;
};

