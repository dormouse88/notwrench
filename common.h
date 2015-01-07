#pragma once
#include <SFML/graphics.hpp>
#include <string>

const std::string FADE = "FADE";
const std::string SNAP = "SNAP";
const std::string OVR = "OVR";
const std::string ADD = "ADD";
const std::string SUB = "SUB";

sf::Color CalculateBlend(sf::Color i, sf::Color j, int duration);
sf::FloatRect CalculateBlend(sf::FloatRect i, sf::FloatRect j, int duration);

sf::Color ApplyBlend(sf::Color base, sf::Color blendRate, int timeMultiplier);
sf::FloatRect ApplyBlend(sf::FloatRect base, sf::FloatRect blendRate, int timeMultiplier);
