#pragma once
#include <unordered_map>
#include <iostream>
#include "Scene.h"
#include "../assets/Assets.h"

class Scene;

typedef std::unordered_map<std::string, std::shared_ptr<Scene>> Scenes;
typedef sf::RenderWindow Window;

class GameEngine
{
	Scenes m_scenes;
	Window m_window;
	Assets m_assets;
	std::string m_currentScene;
	bool m_running = true;

	void init();
	std::shared_ptr<Scene> currentScene();
public:
	GameEngine() { init();};

	void run();
	void update();
	void quit();
	void changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene);
	Assets& getAssets();
	Window& window();
	void sUserInput();
};

