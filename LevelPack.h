#pragma once
#include "Hero.h"
#include "Box.h"
#include <lua.hpp>

class LevelPack
{
public:
	LevelPack(void);
	~LevelPack(void);
	void NextLevel(Hero&, BoxSeq&);
private:
	unsigned int currentLevel;
	std::vector<std::string> levelFilenames;
};

