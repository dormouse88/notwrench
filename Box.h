#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <lua.hpp>
#include "Aspect.h"

class Box
{
public:
	Box(void);
	~Box(void);
	//Box(const Box&) = delete;  //needs C++11 :(
	//Box& operator=(const Box&) = delete;
	void LoadRoute(lua_State * L);
	void DoFrame(unsigned int groove);
	void Draw(sf::RenderTarget & window);
	sf::FloatRect	GetPos()            { return positionAspect.GetActual(); }
	sf::Color	GetCol()            { return colorAspect.GetActual(); }
	std::string	GetBlendString()    { return blendString; }
private:
	Aspect<sf::FloatRect> positionAspect;
	Aspect<sf::Color> colorAspect;
	unsigned int cycle;
        std::string blendString;
	sf::BlendMode blendMode;
	unsigned int offset;
};

typedef std::vector<std::unique_ptr<Box> > BoxSeq;
