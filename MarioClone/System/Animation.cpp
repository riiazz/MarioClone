#include "Animation.h"

std::string& Animation::getName()
{
    return m_name;
}

const Vec2& Animation::getSize() const
{
    return m_size;
}

sf::Sprite& Animation::getSprite()
{
    return m_sprite;
}


