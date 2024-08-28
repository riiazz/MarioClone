#include "Animation.h"

Animation::Animation(sf::Texture& texture, const std::string& name, int frameCount, int speed, bool isCenter)
    : m_sprite(texture), m_name(name), m_frameCount(frameCount), m_speed(speed)
{
    //sprite store full texture of the key frames, then m_size store the size of key frame.
    m_size = Vec2((float)texture.getSize().x / frameCount, (float)texture.getSize().y);
    if(isCenter)
        m_sprite.setOrigin(m_size.x / 2.0f, m_size.y / 2.0f);

    init();
}

void Animation::init()
{
    sf::IntRect rect(m_currentFrame * m_size.x, 0, m_size.x, m_size.y);
    m_sprite.setTextureRect(rect);
}

void Animation::update()
{
    m_gameFrame++;
    m_currentFrame = (m_gameFrame / m_speed) % m_frameCount; //(20 / 4) % 4 == 1 --> back to second frame
    sf::IntRect rect(m_currentFrame * m_size.x, 0, m_size.x, m_size.y);
    m_sprite.setTextureRect(rect);
}

bool Animation::hasEnded()
{
    //the frame loop once
    return m_gameFrame > m_speed && m_currentFrame == 0;
}

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


