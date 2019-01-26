#pragma once

// RenderSystem includes
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

	void update(sf::Time delta_time) override
	{

	}

private:
	entt::DefaultRegistry& registry;
	Scene& scene;
};



