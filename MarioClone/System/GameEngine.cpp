#include "GameEngine.h"
#include "ScenePlay.h"

void GameEngine::init()
{
    changeScene("LEVEL1", std::make_shared<ScenePlay>(this, "2"));
}

std::shared_ptr<Scene> GameEngine::currentScene()
{
    return m_scenes[m_currentScene];
}

void GameEngine::run()
{
    //debug purpose only
    int i = 0;
    while (m_running && i < 100) {
        update();
        i++;
    }
    m_window.close();
}

void GameEngine::update()
{
    //sUserInput();
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
