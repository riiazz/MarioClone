#pragma once
#include <vector>
#include <map>
#include <iostream>
#include "Entity.h"
#include <memory>

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec> EntityMap;

class EntityManager
{
	EntityVec m_entities;
	EntityMap m_entityMap;
	EntityVec m_toAdd;
	size_t m_entityCounter = 0;

	void removeEntity(const std::string& tag);
public:
	EntityManager();
	void update();
	std::shared_ptr<Entity> addEntity(const std::string& tag);
	const EntityVec& getEntities() const;
	const EntityVec& getEntities(const std::string& tag) const;
};

