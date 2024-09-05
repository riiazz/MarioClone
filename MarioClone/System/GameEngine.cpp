#include "GameEngine.h"
#include "ScenePlay.h"
#include <fstream>
#include <sstream>

void GameEngine::init(const std::string& configPath, const std::string& assetConfigPath)
{
    m_window.create(sf::VideoMode(360, 200), "MarioClone");
    m_window.setFramerateLimit(60);

	readAssetConfig(assetConfigPath);
    changeScene("LEVEL1", std::make_shared<ScenePlay>(this, "level1.txt"));
}

std::shared_ptr<Scene> GameEngine::currentScene()
{
    return m_scenes[m_currentScene];
}

void GameEngine::readAssetConfig(const std::string& assetConfigPath)
{
	std::ifstream fileStream(assetConfigPath);
	if (!fileStream.is_open())
		std::cout << "Failed to open the file!!!" << std::endl;
	std::string line;
	while (std::getline(fileStream, line)) {
		std::istringstream s(line);
		std::string type;
		s >> type;
		if (type == "Font") {
			std::string name;
			std::string path;
			s >> name;
			s >> path;
			m_assets.addFont(name, path);
		}
		else if (type == "Sound") {
			std::string name;
			std::string path;
			s >> name;
			s >> path;
			m_assets.addFont(name, path);
		}
		else if (type == "Texture") {
			std::string name;
			std::string path;
			float x, y, width, height;
			s >> name;
			s >> path;
			if (s >> x >> y >> width >> height) {
				m_assets.addTexture(name, path, x, y, width, height);
				continue;
			}
			m_assets.addTexture(name, path);
		}
		else if (type == "Animation") {
			std::string name;
			std::string textureName;
			std::string path;
			int frameCount, speed;
			bool isCenter;
			s >> name >> textureName;
			s >> frameCount >> speed;
			s >> isCenter;
			m_assets.addAnimation(name, Animation(m_assets.getTexture(textureName), name, frameCount, speed, isCenter));
		}
	}
	fileStream.close();
}

void GameEngine::run()
{
	sf::Clock clock;
    while (isRunning()) {
		sf::Time elapsed = clock.restart();
        update(elapsed);
    }
    m_window.close();
}

void GameEngine::update(sf::Time& elapsedTime)
{
    sUserInput();
    currentScene()->update(elapsedTime);
}

void GameEngine::quit()
{
    m_running = false;
}

void GameEngine::changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene)
{
    m_scenes[sceneName] = scene;
    m_currentScene = sceneName;
}

Assets& GameEngine::getAssets()
{
    return m_assets;
}

const bool GameEngine::isRunning() const
{
    return m_running && m_window.isOpen();
}

Window& GameEngine::window()
{
    return m_window;
}

void GameEngine::sUserInput()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            quit();
        }
        else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
        {
            auto& actions = currentScene()->getActions();
            if (actions.find(event.key.code) == actions.end()) continue;

            const std::string& actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";
            currentScene()->sDoAction(Action(actions.at(event.key.code), actionType));
        }
    }
}
