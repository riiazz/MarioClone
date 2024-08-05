#pragma once

#include <SFML/Graphics.hpp>
#include "../utils/Vec2.h"

class Animation
{
	sf::Texture m_texture; //this could be just a temporary
	sf::Sprite m_sprite;
	int m_frameCount = 0;
	int m_currentFrame = 0;
	int m_speed = 0;
	Vec2 m_size = 0;
	std::string m_name;

public:
	Animation() = default;
	Animation(sf::Sprite& sprite, sf::Texture& texture, const std::string& name, int frameCount, int speed, const Vec2& size)
		: m_sprite(sprite), m_texture(texture), m_name(name), m_frameCount(frameCount), m_speed(speed), m_size(size)
	{}

	void update();
	void hasEnded();
	std::string& getName();
	const Vec2& getSize() const;
	sf::Sprite& getSprite();
	sf::Texture& getTexture();
};

