#pragma once
#include "Scene.h"

struct PlayerConfig {
	//add config properties;
};

class ScenePlay : public Scene
{
	std::string m_levelPath;
	std::shared_ptr<Entity> m_player;
	PlayerConfig m_playerConfig;

public:
	void update();
	
	//Systems
	void sAnimation();
	void sMovement();
	void sEnemySpawner();
	void sCollision();
	void sRender();
	//void sDoAction(const Action& action);
	void sDebug();
};

