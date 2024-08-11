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

	void init(const std::string& configPath, const std::string& assetConfigPath);
	std::shared_ptr<Scene> currentScene();
	void readAssetConfig(const std::string& assetConfigPath);
	
public:
	GameEngine(const std::string& configPath, const std::string& assetConfigPath) { init(configPath, assetConfigPath);};

	void run();
	void update();
	void quit();
	void changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene);
	Assets& getAssets();
	const bool isRunning() const;
	Window& window();
	void sUserInput();
};

