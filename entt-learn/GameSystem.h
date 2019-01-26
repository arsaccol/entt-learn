#pragma once
#include <SFML/System/Time.hpp>

class GameSystem
{
public:
	virtual void update(sf::Time delta_time) = 0;
};
