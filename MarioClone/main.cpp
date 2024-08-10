#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity/EntityManager.h"
#include "System/GameEngine.h"
#include <SFML/Audio.hpp>

int main()
{
    GameEngine g;
    g.run();

	/*sf::RenderWindow m_window;
	m_window.create(sf::VideoMode(360, 200), "MarioClone");
	m_window.setFramerateLimit(60);

	Assets assets;

	sf::IntRect area(16, 0, 16*3, 16);*/
	/*sf::Texture texture;
	if (!texture.loadFromFile("assets/images/characters-sprite.png", area))
	{
		std::cout << "failed load sprite" << std::endl;
	}*/
	
	/*assets.addTexture("mario", "assets/images/characters-sprite.png", 16, 0, 16 * 3, 16);
	sf::Texture texture = assets.getTexture("mario");

	Animation anim(texture, "Mario", 3, 7);
	anim.getSprite().setPosition(m_window.getSize().x / 2, m_window.getSize().y / 2);
	assets.addAnimation("mario", anim);
	while (true) {
		assets.getAnimation("mario").update();
		m_window.clear();
		m_window.draw(assets.getAnimation("mario").getSprite());
		m_window.display();
	}
	m_window.close();*/
}
