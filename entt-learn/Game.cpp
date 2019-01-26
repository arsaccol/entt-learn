#include "Game.h"
#include "Game.h"

#include "ActualSystems.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);


Game::Game(unsigned int width, unsigned int height)
	:	mWindow { sf::VideoMode{ width, height }, "Entities are cool" }
	,	mScene{mEntityRegistry}
{
	mSystemsManager["RenderSystem"] = std::make_unique<RenderSystem>(mEntityRegistry, mScene);
	

}


Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			handleEvents();
			update(TimePerFrame);
		}

		render();
	}
}

void Game::handleEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			mWindow.close();
	}

}

void Game::handleRealTimeInput()
{
}

void Game::update(sf::Time elapsedTime)
{
	//game_object.Update(elapsedTime);
}

void Game::render()
{
	mWindow.clear();

	// old rendering call attached to scene
	//mScene.render_sprites(mWindow);

	// new rendering call based on RenderSystem
	static_cast<RenderSystem*>(mSystemsManager["RenderSystem"].get())->render_sprites(mWindow);

	mWindow.display();
}
