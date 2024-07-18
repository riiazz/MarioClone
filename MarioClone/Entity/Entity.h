#pragma once

#include <tuple>
#include <iostream>
#include "../Component/Component.h"

typedef std::tuple<
	CTransform,
	CBoundingBox,
	CInput,
	CLifespan,
	CState,
	CGravity> Components;

class Entity
{
	friend class EntityManager;

	Components m_components;
	std::string m_tag = "default";
	bool m_active = true;
	size_t m_id = 0;

	Entity(const std::string& _tag, size_t _id) : m_id(_id), m_tag(_tag) {}
	
public:

	size_t getId() const;
	bool isActive() const;
	std::string getTag() const;
	void destroy();

	// Parameter packing. && means it's an r-value reference
	// Ex: entity->addComponent<CTransform>(Vec2(100, 100), Vec2(5, 5));
	// Ex: entity->addComponent<CInput>();
	template <typename T, typename... Targs>
	T& addComponent(Targs&&... mArgs) {
		auto& comp = std::get<T>(m_components);
		comp = T(std::forward<Targs>(mArgs)...);
		comp.has = true;
		return comp;
	}

	template <typename T>
	bool hasComponent() const{
		return getComponent<T>().has;
	}

	template <typename T>
	T& getComponent()
	{
		return std::get<T>(m_components);
	}

	template <typename T>
	const T& getComponent() const 
	{
		return std::get<T>(m_components);
	}

	template <typename T>
	void removeComponent() {
		auto& comp = std::get<T>(m_components);
		comp = NULL;
		comp.has = false;
	}
};