#include "Collision.h"
#include <memory>

bool Collision::rayVsRect(const std::shared_ptr<Entity>& origin, const Vec2& rayDir, const std::shared_ptr<Entity>& target, Vec2& contactPoint, Vec2& contactNormal, float& tHitNear)
{
    auto& originTransform = origin->getComponent<CTransform>();
    auto& originBoundingBox = origin->getComponent<CBoundingBox>();
    auto& targetTransform = target->getComponent<CTransform>();
    auto& targetBoundingBox = target->getComponent<CBoundingBox>();

    // Change the origin of target to top left
    Vec2 targetTopLeft = targetTransform.pos - (targetBoundingBox.size / Vec2(2, 2));
    // expanded target size
    targetTopLeft = targetTopLeft - (originBoundingBox.size / Vec2(2, 2));
    Vec2 targetExpandedSize = targetBoundingBox.size + originBoundingBox.size;

    contactNormal = { 0, 0 };
    contactPoint = { 0, 0 };

    // Cache division
    Vec2 invdir = Vec2(1, 1) / rayDir;

    // calculate intersections with rectangle bounding axes
    Vec2 tNear = (targetTopLeft - originTransform.pos) * invdir;
    
    Vec2 tFar = (targetTopLeft + targetExpandedSize - originTransform.pos) * invdir;

    if (std::isnan(tFar.y) || std::isnan(tFar.x)) return false;
    if (std::isnan(tNear.y) || std::isnan(tNear.y)) return false;

    //sort distances
    if (tNear.x > tFar.x) std::swap(tNear.x, tFar.x);
    if (tNear.y > tFar.y) std::swap(tNear.y, tFar.y);

    //early rejection
    if (tNear.x > tFar.y || tNear.y > tFar.x) return false;

    // closest 'time' will be the first contact
    tHitNear = std::max(tNear.x, tNear.y);

    // furthest 'time is contact on opposite side of target
    float tHitFar = std::min(tFar.x, tFar.y);

    // Reject if ray direction is pointing  away from object
    if (tHitFar < 0) return false;

    // contact point of collision from parametic line equation
    contactPoint = originTransform.pos + (rayDir * tHitNear);

    if (tNear.x > tNear.y) {
        if (invdir.x < 0) {
            contactNormal = { 1, 0 };
        }
        else {
            contactNormal = { -1,0 };
        }
    }
    else if (tNear.x < tNear.y) {
        if (invdir.y < 0) {
            contactNormal = { 0,1 };
        }
        else {
            contactNormal = { 0, -1 };
        }
    }

    // Note if tNear == tFar, collision is principly in a diagonal
    // so pointless to resolve, By returning CN={0,0} even though its
    // considered a hit, the resolver wont change anything.
    return true;
}

bool Collision::dynamicRectVsRect(const std::shared_ptr<Entity>& origin, const std::shared_ptr<Entity>& target, Vec2& contactPoint, Vec2& contactNormal, float& contactTime, const float timeStep)
{
    auto& vel = origin->getComponent<CTransform>().velocity;
    //if (vel.x == 0 && vel.y)
    //    return false;

    if (rayVsRect(origin, vel * timeStep, target, contactPoint, contactNormal, contactTime)) {
        return (contactTime >= 0.0f && contactTime < 1.0f);
    }
    return false;
}

bool Collision::resolveDynamicRectVsRect(const std::shared_ptr<Entity>& origin, const std::shared_ptr<Entity>& target, const float timeStep)
{
    Vec2 contactPoint, contactNormal;
    float contactTime = 0;
    if (dynamicRectVsRect(origin, target, contactPoint, contactNormal, contactTime, timeStep)) {
        auto& transform = origin->getComponent<CTransform>();
        transform.velocity += contactNormal * Vec2(std::abs(transform.velocity.x), std::abs(transform.velocity.y));
        if (contactNormal.y == -1)
            origin->getComponent<CGravity>().isOnGround = true;
        return true;
    }
    return false;
}

bool Collision::resolveEnemyDynamicRectVsRect(const std::shared_ptr<Entity>& origin, const std::shared_ptr<Entity>& target, const float timeStep)
{
    Vec2 contactPoint, contactNormal;
    float contactTime = 0;
    if (dynamicRectVsRect(origin, target, contactPoint, contactNormal, contactTime, timeStep)) {
        auto& transform = origin->getComponent<CTransform>();
        transform.velocity += contactNormal * Vec2(std::abs(transform.velocity.x), std::abs(transform.velocity.y));
        if (contactNormal.y == -1)
            origin->getComponent<CGravity>().isOnGround = true;
        if (contactNormal.x == 1 || contactNormal.x == -1)
            transform.ACC *= -1;
        return true;
    }
    return false;
}
