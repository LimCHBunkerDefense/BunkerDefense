#pragma once
#include <ctime>
#include <cmath>
#include "Singleton.h"

#define MATH Math::Instance()

struct Vector
{
	float x, y;

	Vector() { x = 0.0f; y = 0.0f; }
	Vector(float x, float y) { this->x = x; this->y = y; }

	Vector operator + (Vector v) { return Vector(x + v.x, y + v.y); }
	Vector operator - (Vector v) { return Vector(x - v.x, y - v.y); }
	Vector operator * (Vector v) { return Vector(x * v.x, y * v.y); }
	Vector operator / (Vector v) { return Vector(x / v.x, y / v.y); }

	Vector operator + (float num) { return Vector(x + num, y + num); }
	Vector operator - (float num) { return Vector(x - num, y - num); }
	Vector operator * (float num) { return Vector(x * num, y * num); }
	Vector operator / (float num) { return Vector(x / num, y / num); }
};

struct Box
{
	Vector pos;
	Vector size;
	Vector anchor;

	Box() {}
	Box(Vector pos, Vector size, Vector anchor = Vector(0.5f, 0.5f))
	{
		this->pos = pos;
		this->size = size;
		this->anchor = anchor;
	}

	Vector LeftTop() { return pos - size * anchor; }
	Vector RightBottom() { return LeftTop() + size; }
};

class Math : public Singleton<Math>
{
public:
	Math()
	{
		srand(time(NULL));
	}

	template <typename T>
	T Clamp(T num, T min, T max)
	{
		if (num < min) num = min;
		if (num > max) num = max;
		return num;
	}

	float SqrDistance(Vector a, Vector b)
	{
		return pow(b.x - a.x, 2) + pow(b.y - a.y, 2);
	}

	float Distance(Vector a, Vector b)
	{
		return sqrt(SqrDistance(a, b));
	}

	bool IsCollided(Vector point, Box box)
	{
		Vector leftTop = box.LeftTop();
		Vector rightBottom = box.RightBottom();

		return (point.x >= leftTop.x && point.x <= rightBottom.x)
			&& (point.y >= leftTop.y && point.y <= rightBottom.y);
	}

	bool IsCollided(Box a, Box b)
	{
		Vector leftTopA = a.LeftTop();
		Vector leftTopB = b.LeftTop();
		Vector rightBottomA = a.RightBottom();
		Vector rightBottomB = b.RightBottom();

		if (rightBottomA.x < leftTopB.x) return false;
		if (rightBottomA.y < leftTopB.y) return false;
		if (leftTopA.x > rightBottomB.x) return false;
		if (leftTopA.y > rightBottomB.y) return false;
		return true;
	}
};