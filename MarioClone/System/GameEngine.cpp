#include "GameEngine.h"

std::shared_ptr<Scene> GameEngine::currentScene()
{
    return m_scenes[m_currentScene];
}

void GameEngine::run()
{
    while (m_running) {
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

Window& GameEngine::window()
{
    return m_window;
}
