#pragma once

#include <SFML/Graphics.hpp>
#include "../utils/Vec2.h"
#include "../System/Animation.h"

class Component
{
public:
	bool has;
};

class CTransform : public Component
{
public:
	Vec2 pos = { 0.0f, 0.0f };
	Vec2 prevPos = { 0.0f, 0.0f };
	Vec2 velocity = { 0.0f, 0.0f };
	Vec2 scale = { 0.0f, 0.0f };
	float angle = 0;

	CTransform(){}
	CTransform(const Vec2& _pos) : pos(_pos){}
	CTransform(const Vec2& _pos, const Vec2& _vel, const Vec2& _scale, float _angle) 
		: pos(_pos), velocity(_vel), scale(_scale), angle(_angle)
	{}
};

class CBoundingBox : public Component
{
public:
	Vec2 size = { 0.0f, 0.0f };
	Vec2 preOverlap = { 0.0f, 0.0f };

	CBoundingBox(){}
	CBoundingBox(const Vec2& _size) : size(_size){}
};

class CInput : public Component
{
public:
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool shoot = false;
	bool canShoot = true;
	bool canJump = true;

	CInput() {}
};

class CLifespan : public Component
{
public:
	float total = 0;
	float remaining = 0;

	CLifespan(){}
	CLifespan(float _total) : total(_total), remaining(_total){}
};

class CState : public Component
{
public:
	std::string state = "none";

	CState(){}
	CState(const std::string& _state) : state(_state){}
};

class CGravity : public Component
{
public:
	float gravity = 0;
	bool isOnGround = true;
	CGravity(){}
	CGravity(float g) : gravity(g){}
};

//Component animation here
class CAnimation : public Component
{
public:
	Animation animation;
	bool repeat = false;

	CAnimation(){}
	CAnimation(const Animation& _animation, bool _repeat) : animation(_animation), repeat(_repeat){}
};