#include "GameEngine.h"
#include "ScenePlay.h"

void GameEngine::init()
{
    m_window.create(sf::VideoMode(360, 200), "MarioClone");
    m_window.setFramerateLimit(60);

    loadAssets();
    changeScene("LEVEL1", std::make_shared<ScenePlay>(this, "2"));
}

std::shared_ptr<Scene> GameEngine::currentScene()
{
    return m_scenes[m_currentScene];
}

void GameEngine::loadAssets()
{
    //load font
    m_assets.addFont("font1", "assets/RobotRebels.ttf");

    //load texture
    m_assets.addTexture("player", "assets/images/characters-sprite.png", 16, 0, 16 * 3, 16);

    //load animation
    m_assets.addAnimation("player", Animation(m_assets.getTexture("player"), "player", 3, 12));

    //load soundBuffer
    //m_assets.addSound()
}

void GameEngine::run()
{
    while (isRunning()) {
        update();
    }
    m_window.close();
}

void GameEngine::update()
{
    sUserInput();
    currentScene()->update();
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
