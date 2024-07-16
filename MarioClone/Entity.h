#pragma once

#include <tuple>
#include <iostream>
#include "Component.h"

typedef std::tuple<
	std::shared_ptr<CTransform>,
	std::shared_ptr<CBoundingBox>,
	std::shared_ptr<CInput>,
	std::shared_ptr<CLifespan>,
	std::shared_ptr<CState>,
	std::shared_ptr<CGravity>> Components;

class Entity
{
	Components m_components;
	std::string m_tag = "default";
	bool m_active = true;
	size_t m_id = 0;

	
	
public:
	Entity(const std::string& _tag, size_t _id) : m_id(_id), m_tag(_tag) {}

	void destroy();

	// Parameter packing. && means it's an r-value reference
	// Ex: entity->addComponent<CTransform>(Vec2(100, 100), Vec2(5, 5));
	// Ex: entity->addComponent<CInput>();
	template <typename T, typename... Targs>
	T& addComponent(Targs&&... mArgs) {
		//TODO here
	}

	template <typename T>
	bool hasComponent() const {
		return getComponent<T>()->has;
	}

	template <typename T>
	T& getComponent() const 
	{
		return std::get<T>(m_components);
	}

	template <typename T>
	void removeComponent();
};