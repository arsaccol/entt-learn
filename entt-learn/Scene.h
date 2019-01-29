#pragma once

/// <summary>
/// A scene is a container for entities, possibly in some 
/// internal structuring such as a scene graph, or with a list of layers.
/// Game system methods should receive scene references as arguments.
/// </summary>

#include <vector>
#include <cstdint>
#include <string>
#include <memory>
#include <variant>

#include <cstdlib> // for rand()
#include <ctime>

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>


class PlayerTag {};


namespace Components 
{
	struct Velocity
	{
		float x = 0.f;
		float y = 0.f;
	};
}


class SceneNode
{
public:
	using Node_Ptr = std::unique_ptr<SceneNode>;
	SceneNode(std::uint32_t entity, const std::string& name = "")
		:	entity{ entity }
		, name{ name }
	{}

	void addChild(std::uint32_t entity, const std::string& name)
	{
		auto newborn_ptr{ std::make_unique<SceneNode>(entity, name) };
		children.push_back(std::move(newborn_ptr));
	}


	std::uint32_t getEntity() const
	{
		return entity;
	}

	const std::string& getName() const
	{
		return name;
	}

	std::vector<Node_Ptr>& getChildren()
	{
		return children;
	}


private:

	std::string name;
	std::uint32_t entity;
	std::vector<Node_Ptr> children;
};

class Scene
{
public:
	Scene(entt::DefaultRegistry& registry)
		: registry{ registry }
		, root_node{ SceneNode{registry.create(), "root_scene_node"} }
	{
		player_texture.loadFromFile("star.png");

		// "Actual" game entity creation
		auto player = registry.create();
		//registry.assign<PlayerTag, sf::Sprite>(player, )
		registry.assign<PlayerTag>(player);
		registry.assign<sf::Sprite>(player, player_texture);

		create_particles(500);
		// end "Actual" game entity creation

	}

private:
	void create_particles(int how_many)
	{
		srand(static_cast<unsigned int>(time(nullptr)));
		for(int i = 0; i < how_many; ++i)
		{
			auto particle = registry.create();

			// Create this particle's sprite
			registry.assign<sf::Sprite>(particle, player_texture);
			auto sprites_view = registry.view<sf::Sprite>();
			for (auto entity : sprites_view)
			{
				auto& sprite = sprites_view.get(entity);
				sprite.setPosition(static_cast<float>(rand() % 640), static_cast<float>(rand() % 480));
				sprite.setColor(sf::Color{	static_cast<sf::Uint8>(rand() % 255), 
											static_cast<sf::Uint8>(rand() % 255),
											static_cast<sf::Uint8>(rand() % 255) });
				sprite.setScale(0.3f, 0.3f);
			}

			// Create this particle's velocity
			registry.assign<Components::Velocity>(particle, 50.f, 50.f);
			auto velocities_view = registry.view<Components::Velocity>();

			for (auto entity : velocities_view)
			{
				auto& velocity = velocities_view.get(entity);
				velocity.x = static_cast<float>(rand() % 100);
				velocity.y = static_cast<float>(rand() % 100);

				int flip = rand() % 2; // either 1 or 0
				if (flip) 
				{
					velocity.x *= -1;
					velocity.y *= -1;
				}

			}
		}

	}
private:
	SceneNode root_node;
	std::vector<uint32_t> entities;
	sf::Texture player_texture;

	entt::DefaultRegistry& registry;

};

