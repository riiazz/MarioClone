#include "EntityManager.h"
#include "Entity.h"
#include <memory>

void EntityManager::removeEntity(const std::string& tag)
{
    auto& entities = m_entityMap[tag];
    bool isAlive = false;
    auto it = std::remove_if(entities.begin(), entities.end(), [isAlive](const std::shared_ptr<Entity>& entity) {
        return entity->isActive() == isAlive;
        });
    entities.erase(it, entities.end());
}

EntityManager::EntityManager()
{
}

void EntityManager::update()
{
    //Deleting Dead entity;
    //from vector
    bool isAlive = false;
    auto it = std::remove_if(m_entities.begin(), m_entities.end(), [isAlive](const std::shared_ptr<Entity>& entity) {
        return entity->isActive() == isAlive;
        });
    if (it != m_entities.end())
        m_entities.erase(it, m_entities.end());

    //from map
    for (const auto& pair : m_entityMap) {
        removeEntity(pair.first);
    }

    //Add Entity;
    for (auto& entity : m_toAdd) 
    {
        m_entities.push_back(entity);
        m_entityMap[entity->getTag()].push_back(entity);
    }
    m_toAdd.clear();
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
    auto entity = std::shared_ptr<Entity>(new Entity(tag, ++m_entityCounter));
    m_toAdd.push_back(entity);
    return entity;
}

const EntityVec& EntityManager::getEntities() const
{
    return m_entities;
}

const EntityVec& EntityManager::getEntities(const std::string& tag) const
{
    if (m_entityMap.count(tag) == 0)
        return EntityVec();
    return m_entityMap.at(tag);
}
