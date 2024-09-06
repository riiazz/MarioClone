#pragma once
#include "Scene.h"
#include "../System/Collision.h"

struct PlayerConfig {
	//add config properties;
	float X, Y, CW, CH, ACC, SPEED, MAXSPEED, JUMP, GRAVITY;
	std::string WEAPON;
};

struct EnemyConfig {
	float X, Y, CW, CH, SPEED, GRAVITY;
	std::string animationName;
};

struct SceneConfig {
	int levelWidth, levelHeight, pixelSize;
};

class ScenePlay : public Scene
{
	//std::string m_levelPath;
	std::shared_ptr<Entity> m_player;
	PlayerConfig m_playerConfig;
	std::vector<sf::RectangleShape> m_grid;
	std::vector<sf::Text> m_coordiates;
	SceneConfig m_sceneConfig;
	bool m_showGrid = false;
	bool m_showBoundingBox = false;
	Collision m_collisionManager;

	void update(sf::Time elapsedTime) override;
	void sDoAction(const Action& action) override;
	void sRender() override;
	void onEnd() override;
	
	//Systems
	void init(const std::string& levelPath);
	void readConfig(const std::string& levelPath);
	void sSpawnPlayer();
	void sPlayerMovement(sf::Time elapsedTime);
	void setAnimation(std::shared_ptr<Entity> entity, const std::string& animationName, bool repeat);
	void sAnimation();
	void sMovement(sf::Time elapsedTime);
	void sEnemySpawner(const EnemyConfig& con);
	void sEnemyMovement();
	const bool sCheckCollision(std::shared_ptr<Entity> actor, std::shared_ptr<Entity> other, Vec2& predictedPos, Vec2& _overlap) const;
	void sCollision();
	void sGravity();
	void sDebug();
	void sCreatePixelGrid();

public:
	ScenePlay(GameEngine* gameEngine, const std::string& levelPath);
};

