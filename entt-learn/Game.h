#pragma once
#include <unordered_map>
#include <string>

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include "Scene.h"
#include "GameSystem.h"

class Game
{
public:
	Game(unsigned int width, unsigned int height);
	~Game();

	void run();

private:
	void handleEvents();
	void handleRealTimeInput();
	void update(sf::Time elapsedTime);
	void render();

	sf::RenderWindow mWindow;
	static const sf::Time TimePerFrame;

	// Experimental
	entt::DefaultRegistry mEntityRegistry;


	std::unordered_map < std::string, std::unique_ptr<GameSystem> > mSystemMap;
	Scene mScene;
	// /Experimental

};

