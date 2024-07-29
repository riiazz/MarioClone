#pragma once

#include <SFML/Graphics.hpp>
#include "../utils/Vec2.h"

class Animation
{
	sf::Sprite m_sprite;
	int m_frameCount = 0;
	int m_currentFrame = 0;
	int m_speed = 0;
	Vec2 m_size = 0;
	std::string m_name;

public:
	Animation() = default;

	void update();
	void hasEnded();
	std::string& getName();
	const Vec2& getSize() const;
	sf::Sprite& getSprite();
};

