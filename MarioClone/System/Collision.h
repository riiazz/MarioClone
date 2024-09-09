#pragma once
#include "../utils/Vec2.h"
#include "../Entity/Entity.h"

class Entity;

class Collision
{
public:
	bool rayVsRect(const std::shared_ptr<Entity>& origin, const Vec2& rayDir, const std::shared_ptr<Entity>& target, Vec2& contactPoint, Vec2& contactNormal, float& tHitNear);

	bool dynamicRectVsRect(const std::shared_ptr<Entity>& origin, const std::shared_ptr<Entity>& target, Vec2& contactPoint, Vec2& contactNormal, float& contactTime, const float timeStep);

	bool resolveDynamicRectVsRect(const std::shared_ptr<Entity>& origin, const std::shared_ptr<Entity>& target, const float timeStep);
	bool resolveEnemyDynamicRectVsRect(const std::shared_ptr<Entity>& origin, const std::shared_ptr<Entity>& target, const float timeStep);
};

