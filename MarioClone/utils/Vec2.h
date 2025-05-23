#pragma once
#include <iostream>
#include <string>
class Vec2
{
public:
	double x;
	double y;

	Vec2(double x = 0, double y = 0);

	bool operator == (const Vec2& v) const;
	bool operator != (const Vec2& v) const;
	Vec2 operator + (const Vec2& v) const;
	Vec2 operator - (const Vec2& v) const;
	Vec2 operator * (const Vec2& v) const;
	Vec2 operator / (const Vec2& v) const;
	void operator += (const Vec2& v);
	void operator -= (const Vec2& v);
	void operator *= (const Vec2& v);
	void operator /= (const Vec2& v);
	Vec2 operator * (const float v) const;

	void normalize();
	double length() const;
	std::string print() const;
};

