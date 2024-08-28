#pragma once

#include <SFML/Graphics.hpp>
#include "../utils/Vec2.h"

class Animation
{
	sf::Sprite m_sprite;
	int m_frameCount = 0;
	int m_currentFrame = 0;
	int m_speed = 0; //speed in frame, the smaller the value the faster animation runs
	size_t m_gameFrame = 0; //number of frame this animation runs
	Vec2 m_size = 0;
	std::string m_name;

public:
	Animation() = default;
	Animation(sf::Texture& texture, const std::string& name, int frameCount, int speed, bool isCenter);

	void init();
	void update();
	bool hasEnded();
	std::string& getName();
	const Vec2& getSize() const;
	sf::Sprite& getSprite();
};

