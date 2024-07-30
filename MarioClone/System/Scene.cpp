#include "Scene.h"

const ActionMap& Scene::getActions() const
{
    return m_actionMap;
}

void Scene::registerAction(int inputKey, const std::string& actionName)
{
    m_actionMap[inputKey] = actionName;
}

void Scene::setPaused(bool pause)
{
    m_paused = pause;
}
