#include "Entity.h"

size_t Entity::getId() const
{
	return m_id;
}

bool Entity::isActive() const
{
	return m_active;
}

std::string Entity::getTag() const
{
	return m_tag;
}

void Entity::destroy()
{
	m_active = false;
}
