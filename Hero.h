#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include "Box.h"

class Hero
{
public:
	Hero();
	~Hero(void);
	void LoadHome(sf::Vector2f home, sf::Vector2f size);
	void Die();
	void DoStep(sf::FloatRect scr, BoxSeq & boxes);
	void Draw(sf::RenderTarget & window);
        float GetEngine() { return (255 - _chromaPower.z) / 255.f; }
        float GetHealth() { return (255 - _chromaPower.x) / 255.f; }

	bool inWinZone;
private:
	sf::Vector2f _home;
	sf::Vector2f _pos;
	sf::Vector2f _size;
	sf::Vector2f _vel;
	float _engine;
	float _health;
	sf::Vector3f _chromaPower;
	std::vector<std::vector<sf::Color> > chromagrid;
};

