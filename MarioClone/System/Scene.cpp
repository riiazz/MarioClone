#include "Scene.h"

const ActionMap& Scene::getActions() const
{
    return m_actionMap;
}

void Scene::setPaused(bool pause)
{
    m_paused = pause;
}
