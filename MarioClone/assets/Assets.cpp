#include "Assets.h"
#include <iostream>

void Assets::addTexture(const std::string& name, const std::string& path)
{
	sf::Texture texture;
	if (!texture.loadFromFile(path))
	{
		std::cout << "failed load sprite -> " << name << std::endl;
		return;
	}
	m_textures[name] = texture;
}

void Assets::addTexture(const std::string& name, const std::string& path, float x, float y, float width, float height)
{
	sf::IntRect area(x, y, width, height);
	sf::Texture texture;
	if (!texture.loadFromFile(path, area))
	{
		std::cout << "failed load sprite -> " << name << std::endl;
		return;
	}
	m_textures[name] = texture;
}

void Assets::addAnimation(const std::string& name, const Animation& animation)
{
	m_animations[name] = animation;
}

void Assets::addSound(const std::string& name, const std::string& path)
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(path)) {
		std::cout << "failed to load sound -> " << name << std::endl;
		return;
	}
	m_sounds[name] = buffer;
}

void Assets::addFont(const std::string& name, const std::string& path)
{
	sf::Font font;
	if (!font.loadFromFile(path)) {
		std::cout << "failed to load font -> " << name << std::endl;
		return;
	}
	m_fonts[name] = font;
}

sf::Texture& Assets::getTexture(const std::string& name)
{
    return m_textures[name];
}

Animation& Assets::getAnimation(const std::string& name)
{
    return m_animations[name];
}

sf::SoundBuffer& Assets::getSoundBuffer(const std::string& name)
{
	return m_sounds[name];
}

sf::Font& Assets::getFont(const std::string& name)
{
    return m_fonts[name];
}
