#include "LevelPack.h"
#include <iostream>
#include <assert.h>

const std::string LEVEL_LIST_FILENAME = "levels.lua";

LevelPack::LevelPack(void)
	:currentLevel(0)
{
	//use lua to populate "levelFilenames"...
	lua_State * L = luaL_newstate();
	luaL_openlibs(L);
	luaL_dofile(L, LEVEL_LIST_FILENAME.c_str());

	int lev = currentLevel + 1; //(because lua indices start at 1)
	lua_getglobal(L, "filenames");
	while (lev > 0) {
		lua_pushinteger(L, lev);
		lua_gettable(L, -2);
		if (lua_isnil(L,-1)) {
			lua_pop(L,1);
			lev = -1;
		}
		else {
			levelFilenames.push_back( lua_tostring(L,-1) );
			lua_pop(L,1);
			lev++;
		}
	}
}

LevelPack::~LevelPack(void)
{}

void LevelPack::NextLevel(Hero& hero, BoxSeq& boxes)
{
	boxes.clear();
	std::string filename = levelFilenames.at(currentLevel);
	lua_State * L = luaL_newstate();
	luaL_openlibs(L);
	if ( luaL_dofile(L, filename.c_str()) )
	{
		std::cout << "ERROR RUNNING LUA FILE! LUA SAYS: " << lua_tostring(L, -1);
		throw std::string(lua_tostring(L, -1) );
	}

	if (lua_gettop(L) > 0) std::cout << "On Top: " << lua_tostring(L,-1);
	assert(lua_gettop(L) == 0);
	lua_getglobal(L, "hero");
	if (lua_isnil(L,-1)) throw std::string("hideously malformed level file");
	float left, top, width, height;
	{
		lua_getfield(L, -1, "left");
		left = lua_tonumber(L, -1);
		lua_pop(L,1);
	}
	{
		lua_getfield(L, -1, "top");
		top = lua_tonumber(L, -1);
		lua_pop(L,1);
	}
	{
		lua_getfield(L, -1, "width");
		width = lua_tonumber(L, -1);
		lua_pop(L,1);
	}
	{
		lua_getfield(L, -1, "height");
		height = lua_tonumber(L, -1);
		lua_pop(L,1);
	}
	lua_pop(L,1);
	hero.LoadHome(sf::Vector2f(left, top), sf::Vector2f(width, height) );
	
	assert(lua_gettop(L) == 0);
	lua_getglobal(L, "boxes");
	if (lua_isnil(L,-1)) throw std::string("hideously malformed level file");
	int boxindex = 1;
	while (boxindex > 0) {
		assert(lua_gettop(L) == 1);
		lua_pushinteger(L, boxindex);
		lua_gettable(L, -2);
		assert(lua_gettop(L) == 2);
		if (lua_isnil(L,-1)) {
			boxindex = -1;
		}
		else {
			boxindex++;
			std::unique_ptr<Box> tempBox(new Box);
			tempBox->LoadRoute(L);
			boxes.push_back( std::move(tempBox) );
		}
		lua_pop(L,1);
	}
	lua_pop(L,1);

	currentLevel++;
	if (currentLevel >= levelFilenames.size() ) currentLevel = 0;
}
