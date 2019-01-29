#pragma once

// RenderSystem includes
#include <iostream>


#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include <entt/entt.hpp>
#include "Scene.h"

#include "GameSystem.h"


class RenderSystem : public GameSystem
{
public:
	RenderSystem(entt::DefaultRegistry& registry, Scene& scene)
		:	registry{ registry }
		,	scene{ scene }
	{
	}

	void render_sprites(sf::RenderWindow& render_window)
	{
		auto view = registry.view<sf::Sprite>();
		//render_target.draw(view);
		view.each(
			[&](const auto, sf::Sprite& sprite) {
			render_window.draw(sprite);
		});

	}

	virtual void update(sf::Time delta_time)
	{
	}

private:
	entt::DefaultRegistry& registry;
	Scene& scene;
};

class MotionSystem : public GameSystem
{
public:
	MotionSystem(entt::DefaultRegistry& registry, Scene& scene)
		:	registry{ registry }
		,	scene{ scene }
	{}

	virtual void update(sf::Time delta_time) 
	{
		auto view = registry.view<sf::Sprite, Components::Velocity>();
		view.each(
			[&](const auto, sf::Sprite& sprite, auto& velocity)
			{
				sf::Vector2f v{ velocity.x, velocity.y };
				sf::Vector2f displacement( velocity.x * delta_time.asSeconds(), velocity.y * delta_time.asSeconds() );
				sprite.setPosition( sprite.getPosition() + displacement );
			}

		);

	}

private:
	entt::DefaultRegistry& registry;
	Scene& scene;

};

class CollisionSystem : public GameSystem
{
public:
	CollisionSystem(entt::DefaultRegistry& registry, Scene& scene)
	:	registry{ registry }
		, scene{ scene }
	{}

	virtual void update(sf::Time delta_time)
	{
		auto view = registry.view<sf::Sprite, Components::Velocity>();
		// Let's do it simple for now and just keep those stars within the screen
		for(auto entity : view)
		{
			auto& sprite = view.get<sf::Sprite>(entity);
			auto& vel = view.get<Components::Velocity>(entity);

			sf::Vector2f pos = sprite.getPosition();

			if ((pos.x < 0 || pos.x > 640) ||
				(pos.y < 0 || pos.y > 480))
			{
				vel.x *= -1;
				vel.y *= -1;
			}
			
		}



	}

private:
	entt::DefaultRegistry& registry;
	Scene& scene;
};

