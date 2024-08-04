#include "Assets.h"

void Assets::addTexture(const std::string& name, const std::string& path)
{
    throw std::runtime_error("Not Implement");
}

sf::Texture& Assets::getTexture(const std::string& name)
{
    return m_textures[name];
}

Animation& Assets::getAnimation(const std::string& name)
{
    return m_animations[name];
}

sf::Sound& Assets::getSound(const std::string& name)
{
    //return m_sounds[name];
}

sf::Font& Assets::getFont(const std::string& name)
{
    return m_fonts[name];
}
