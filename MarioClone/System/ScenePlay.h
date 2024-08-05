#pragma once
#include "Scene.h"

struct PlayerConfig {
	//add config properties;
	float X, Y, CX, CY, SPEED, MAXSPEED, JUMP, GRAVITY;
	std::string WEAPON;
};

class ScenePlay : public Scene
{
	std::string m_levelPath;
	std::shared_ptr<Entity> m_player;
	PlayerConfig m_playerConfig;
	//temporary
	sf::Texture m_texture;

	void update() override;
	void sDoAction(const Action& action) override;
	void sRender() override;
	void onEnd() override;
	
	//Systems
	void init(const std::string& levelPath);
	void sSpawnPlayer();
	void sAnimation();
	void sMovement();
	void sEnemySpawner();
	void sCollision();
	void sDebug();

public:
	ScenePlay(GameEngine* gameEngine, const std::string& levelPath);
};

