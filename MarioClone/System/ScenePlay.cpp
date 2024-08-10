#include "ScenePlay.h"

void ScenePlay::update()
{
	//std::cout << "CALLS UPDATE FROM SCENE PLAY" << std::endl;
	m_player->getComponent<CAnimation>().animation.update(); //temporary
	sRender();
}

void ScenePlay::sDoAction(const Action& action)
{
	if (action.type() == "START") 
	{
		if (action.name() == "JUMP")
		{
			m_player->getComponent<CInput>().up = true;
			std::cout << "jump" << std::endl;
		}
		else if (action.name() == "LEFT")
		{
			m_player->getComponent<CInput>().left = true;
			std::cout << "left" << std::endl;
		}
		else if (action.name() == "RIGHT")
		{
			m_player->getComponent<CInput>().right = true;
			std::cout << "right" << std::endl;
		}
		else if (action.name() == "EXIT")
		{
			onEnd();
		}
		else if (action.name() == "PAUSE")
		{
			setPaused(!m_paused);
			std::cout << "pause" << std::endl;
		}
		
		//toggle_grid
		//toggle_texture
		//toggle_collision
	} 
	else if (action.type() == "END")
	{
		if (action.name() == "JUMP")
		{
			m_player->getComponent<CInput>().up = false;
			//modify state
		}
		else if (action.name() == "LEFT")
		{
			m_player->getComponent<CInput>().left = false;
		}
		else if (action.name() == "RIGHT")
		{
			m_player->getComponent<CInput>().right = false;
		}
		
	}
}

void ScenePlay::sRender()
{	
	//TODO: Implement this
	auto& window = m_game->window();

	window.clear();
	window.draw(m_player->getComponent<CAnimation>().animation.getSprite());
	window.display();
}

void ScenePlay::onEnd()
{
	//TODO: Implement this
	m_game->quit();
}

void ScenePlay::init(const std::string& levelPath)
{
	this->registerAction(sf::Keyboard::W, "JUMP");
	this->registerAction(sf::Keyboard::A, "LEFT");
	this->registerAction(sf::Keyboard::D, "RIGHT");
	this->registerAction(sf::Keyboard::Escape, "EXIT");
	this->registerAction(sf::Keyboard::P, "PAUSE");

	sSpawnPlayer();
}

void ScenePlay::sSpawnPlayer()
{
	m_player = m_entities.addEntity("player");
	auto& t = m_player->addComponent<CTransform>(Vec2(100, 150), Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f), 0);

	auto& animation = m_game->getAssets().getAnimation("player");
	animation.getSprite().setPosition(t.pos.x, t.pos.y);
	m_player->addComponent<CAnimation>(animation, false);
	m_player->addComponent<CBoundingBox>(animation.getSize());
	m_player->addComponent<CState>("idleRight");
	m_player->addComponent<CGravity>(9.8f);
	m_player->addComponent<CInput>();

	std::cout << "Player -> " << m_player->getId() << std::endl;
}

ScenePlay::ScenePlay(GameEngine* gameEngine, const std::string& levelPath)
	: Scene(gameEngine), m_levelPath(levelPath)
{
	init(levelPath);
}
