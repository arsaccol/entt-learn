#pragma once

// RenderSystem includes
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include <entt/entt.hpp>
#include "Scene.h"

#include "GameSystem.h"


class RenderSystem : public GameSystem
{
	RenderSystem(entt::DefaultRegistry& registry, Scene& scene)
		:	registry{ registry }
		,	scene{ scene }
	{
	}

	void render_single_node(sf::RenderTarget& render_target, sf::RenderStates render_states)
	{
		registry.view<sf::Drawable, sf::Transformable>();
		//render_target.draw(view);

	}

	entt::DefaultRegistry& registry;
	Scene& scene;
};



