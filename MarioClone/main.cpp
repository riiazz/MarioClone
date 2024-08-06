#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity/EntityManager.h"
#include "System/GameEngine.h"

int main()
{
    //GameEngine g;
    //g.run();
	sf::RenderWindow m_window;
	m_window.create(sf::VideoMode(360, 200), "MarioClone");
	m_window.setFramerateLimit(60);

	sf::IntRect area(16, 0, 16*3, 16);
	sf::Texture texture;
	if (!texture.loadFromFile("assets/images/characters-sprite.png", area))
	{
		std::cout << "failed load sprite" << std::endl;
	}
	
	Animation anim(texture, "Mario", 3, 7);
	anim.getSprite().setPosition(m_window.getSize().x / 2, m_window.getSize().y / 2);
	
	while (true) {
		anim.update();
		m_window.clear();
		m_window.draw(anim.getSprite());
		m_window.display();
	}
	m_window.close();
}
