#pragma once
#include <map>
#include <string>
#include "../Entity/EntityManager.h"
#include "GameEngine.h"
#include "../Component/Action.h"

class GameEngine;
typedef std::map<int, std::string> ActionMap;

class Scene {
protected:
	GameEngine* m_game;
	EntityManager m_entities;
	int currentFrame = 0;
	ActionMap m_actionMap;
	bool m_paused = false;
	bool m_hasEnded = false;

public:
	Scene(){}
	Scene(GameEngine* engine) : m_game(engine) {}
	virtual ~Scene(){}

	virtual void update() = 0;
	virtual void sDoAction(const Action& action) = 0;
	virtual void sRender() = 0;
	virtual void onEnd() = 0;

	//void simulate(int a); //not really sure what this for
	const ActionMap& getActions() const;
	void registerAction(int inputKey, const std::string& actionName);
	void setPaused(bool pause);
};
