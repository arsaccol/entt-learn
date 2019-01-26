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


