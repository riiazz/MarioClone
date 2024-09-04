#include "Vec2.h"
#include <math.h>

Vec2::Vec2(double x, double y) 
	: x(x), y(y)
{}

bool Vec2::operator==(const Vec2 & v) const
{
	return (this->x == v.x && this->y == v.y);
}

bool Vec2::operator!=(const Vec2& v) const
{
	return (this->x != v.x || this->y != v.y);;
}

Vec2 Vec2::operator+(const Vec2& v) const
{
	return Vec2(this->x + v.x, this->y + v.y);
}

Vec2 Vec2::operator-(const Vec2& v) const
{
	return Vec2(this->x - v.x, this->y - v.y);
}

Vec2 Vec2::operator*(const Vec2& v) const
{
	return Vec2(this->x * v.x, this->y * v.y);
}

Vec2 Vec2::operator/(const Vec2& v) const
{
	return Vec2(this->x / v.x, this->y / v.y);
}

void Vec2::operator+=(const Vec2& v)
{
	this->x += v.x;
	this->y += v.y;
}

void Vec2::operator-=(const Vec2& v)
{
	this->x -= v.x;
	this->y -= v.y;
}

void Vec2::operator*=(const Vec2& v)
{
	this->x *= v.x;
	this->y *= v.y;
}

void Vec2::operator/=(const Vec2& v)
{
	this->x /= v.x;
	this->y /= v.y;
}

Vec2 Vec2::operator*(const float v) const
{
	return Vec2(this->x * v, this->y * v);
}

void Vec2::normalize()
{
	int l = length();
	this->x = this->x / l;
	this->y = this->y / l;
}

double Vec2::length() const
{
	return sqrtf((this->x* this->x) + (this->y* this->y));
}

std::string Vec2::print() const
{
	return std::to_string(x) + "," + std::to_string(y);
}
