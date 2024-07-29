#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include "../System/Animation.h"

typedef std::unordered_map<std::string, sf::Texture> Textures;
typedef std::unordered_map<std::string, Animation> Animations;
typedef std::unordered_map<std::string, sf::Sound> Sounds;
typedef std::unordered_map<std::string, sf::Font> Fonts;

class Assets
{
	Textures m_textures;
	Animations m_animations;
	Sounds m_sounds;
	Fonts m_fonts;

public:
	Assets() = default;

	void addTexture(const std::string& name, const std::string& path);
	void addAnimation(const std::string& name, const Animation& animation);
	void addSound(const std::string& name, const std::string& path);
	void addFont(const std::string& name, const std::string& path);

	sf::Texture& getTexture(const std::string& name);
	Animation& getAnimation(const std::string& name);
	sf::Sound& getSound(const std::string& name);
	sf::Font& getFont(const std::string& name);
};

