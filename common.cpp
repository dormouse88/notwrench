#include "common.h"

sf::Color CalculateBlend(sf::Color i, sf::Color j, int duration)
{
	sf::Color ret;
	ret.r = (j.r - i.r) / duration;
	ret.g = (j.g - i.g) / duration;
	ret.b = (j.b - i.b) / duration;
	return ret;
}

sf::FloatRect CalculateBlend(sf::FloatRect i, sf::FloatRect j, int duration)
{
	sf::FloatRect ret;
	ret.left = (j.left - i.left) / duration;
	ret.top = (j.top - i.top) / duration;
	ret.width = (j.width - i.width) / duration;
	ret.height = (j.height - i.height) / duration;
	return ret;
}

sf::Color ApplyBlend(sf::Color base, sf::Color blendRate, int timeMultiplier)
{
	sf::Color ret;
	ret.r = base.r + (blendRate.r * timeMultiplier);
	ret.g = base.g + (blendRate.g * timeMultiplier);
	ret.b = base.b + (blendRate.b * timeMultiplier);
	return ret;
}

sf::FloatRect ApplyBlend(sf::FloatRect base, sf::FloatRect blendRate, int timeMultiplier)
{
	sf::FloatRect ret;
	ret.left = base.left +		(blendRate.left * timeMultiplier);
	ret.top = base.top +		(blendRate.top * timeMultiplier);
	ret.width = base.width +	(blendRate.width * timeMultiplier);
	ret.height = base.height +	(blendRate.height * timeMultiplier);
	return ret;
}
