#pragma once
#include "Common.h"
#include <ctime>
#include <cmath>
#include "Singleton.h"

#define MATH Math::Instance()
#define PI					3.141592f
#define ANGLE_TO_RADIAN		0.0174533f
#define RADIAN_TO_ANGLE		57.2958f

struct Vector
{
	float x, y;

	Vector() { x = 0.0f; y = 0.0f; }
	Vector(float x, float y) { this->x = x; this->y = y; }
	//Vector(POINT point) { x = point.x; y = point.y; }	왜 안되는건지 모르겠당

	float Magnitude() { return sqrt(SqrMagnitude()); }
	float SqrMagnitude() { return pow(x, 2) + pow(y, 2); }
	Vector Normalize()
	{
		float mag = Magnitude();
		if (mag == 0) return Zero();
		return *this / mag;
	}

	
	Vector operator + (Vector v) { return Vector(x + v.x, y + v.y); }
	Vector operator - (Vector v) { return Vector(x - v.x, y - v.y); }
	Vector operator * (Vector v) { return Vector(x * v.x, y * v.y); }
	Vector operator / (Vector v) { return Vector(x / v.x, y / v.y); }

	Vector operator + (float num) { return Vector(x + num, y + num); }
	Vector operator - (float num) { return Vector(x - num, y - num); }
	Vector operator * (float num) { return Vector(x * num, y * num); }
	Vector operator / (float num) { return Vector(x / num, y / num); }

	Vector& operator *= (float num) { x *= num; y *= num; return *this; }
	Vector& operator /= (float num) { x /= num; y /= num; return *this; }
	Vector& operator += (Vector v) { x += v.x; y += v.y; return *this; }
	Vector& operator -= (Vector v) { x -= v.x; y -= v.y; return *this; }
	Vector& operator *= (Vector v) { x *= v.x; y *= v.y; return *this; }
	Vector& operator /= (Vector v) { x /= v.x; y /= v.y; return *this; }

	bool operator == (Vector v) { return x == v.x && y == v.y; }
	bool operator != (Vector v) { return x != v.x || y != v.y; }

	static Vector Zero() { return Vector(0.0f, 0.0f); }
	static Vector One() { return Vector(1.0f, 1.0f); }
	static Vector Left() { return Vector(-1.0f, 0.0f); }
	static Vector Right() { return Vector(1.0f, 0.0f); }
	static Vector Up() { return Vector(0.0f, -1.0f); }
	static Vector Down() { return Vector(0.0f, 1.0f); }
};

// 선분
struct Line
{
	Vector point;
	Vector dir;
	float length;
	Line(){}
	Line(Vector startPos, Vector endPos)
	{
		point = startPos;
		dir = (endPos - startPos).Normalize();
		length = (endPos - startPos).Magnitude();
	}

	void SetEndPoint(Vector endPoint)
	{
		dir = (endPoint - point).Normalize();
		length = (endPoint - point).Magnitude();
	}

	Vector StartPoint() { return point; }
	Vector EndPoint() { return point + dir * length; }
	float Slope() { return (EndPoint().y - StartPoint().y) / (EndPoint().x - StartPoint().x); }
};

// 원
struct Circle
{
	Vector center;
	float radius;

	Circle(Vector center, float radius)
	{
		this->center = center;
		this->radius = radius;
	}
};
// 삼각형
struct Triangle
{
	Vector p0, p1, p2;

	Triangle(Vector point0, Vector point1, Vector point2)
	{
		p0 = point0;
		p1 = point1;
		p2 = point2;
	}
};

//원래 가지고 있던 박스 Collider
struct Box
{
	BUTTON_TAG buttonTag;
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
	
	// index로 박스 구분
	Box(BUTTON_TAG buttonTag, Vector pos, Vector size, Vector anchor = Vector(0.5f, 0.5f))
	{
		this->buttonTag = buttonTag;
		this->pos = pos;
		this->size = size;
		this->anchor = anchor;
	}

	Vector LeftTop() { return pos - size * anchor; }
	Vector RightBottom() { return LeftTop() + size; }
};

// 배울 때 사용하는 사각형
struct Box2
{
	Vector center, size;
	Vector dirX, dirY;
	Box2() {}
	Box2(Vector center, Vector size, float angle = 0)
	{
		this->center = center;
		this->size = size;
		SetAngle(angle);
	}

	void SetAngle(float angle)
	{
		dirX = Vector(cosf(angle * ANGLE_TO_RADIAN), -sinf(angle * ANGLE_TO_RADIAN));
		dirY = Vector(cosf((angle - 90) * ANGLE_TO_RADIAN), -sinf((angle - 90) * ANGLE_TO_RADIAN));
	}
	void SetLeftTop(Vector leftTop)
	{
		center = leftTop + Width() * 0.5f + Height() * 0.5f;
	}
	void SetCenter(Vector center)
	{
		this->center = center;
	}

	Vector Width() { return dirX * size.x; }
	Vector Height() { return dirY * size.y; }

	Vector Center() { return center; }
	Vector LeftTop() { return center - Width() * 0.5f - Height() * 0.5f; }
	Vector LeftBottom() { return LeftTop() + Height(); }
	Vector RightTop() { return LeftTop() + Width(); }
	Vector RightBottom() { return LeftTop() + Width() + Height(); }
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

	float Cos(float angle) { return cosf(angle * ANGLE_TO_RADIAN); }
	float Sin(float angle) { return sinf(angle * ANGLE_TO_RADIAN); }
	float Tan(float angle) { return tanf(angle * ANGLE_TO_RADIAN); }
	float Dot(Vector a, Vector b) { return (a.x * b.x) + (a.y * b.y); }
	float CrossZ(Vector a, Vector b) { return (a.x * -b.y - -a.y * b.x); }

	float Distance2(Vector from, Vector to) { return (to - from).Magnitude(); }
	float SqrDistance2(Vector from, Vector to) { return (to - from).SqrMagnitude(); }
	Vector ToDirection(float angle) { return Vector(Cos(angle), -Sin(angle)); }
	Vector Project(Vector v, Vector dir) { return dir.Normalize() * ProjectLength(v, dir); }
	float ProjectLength(Vector v, Vector dir) { return Dot(v, dir.Normalize()); }
	float ProjectAbsLength(Vector v, Vector dir) { return abs(ProjectLength(v, dir)); }

	float SinAngle(Vector from, Vector to)
	{
		float value = CrossZ(from, to) / (from.Magnitude() * to.Magnitude());
		return asinf(value) * RADIAN_TO_ANGLE;
	}

	float CosAngle(Vector from, Vector to)
	{
		float value = Dot(from, to) / (from.Magnitude() * to.Magnitude());
		return acosf(value) * RADIAN_TO_ANGLE;
	}

	float Angle(Vector from, Vector to)
	{
		float angle = CosAngle(from, to);
		if (SinAngle(from, to) < 0) angle = 360 - angle;
		return angle;
	}

	float ToAngle(Vector dir)
	{
		float angle = CosAngle(Vector::Right(), dir);
		if (SinAngle(Vector::Right(), dir) < 0) angle = 360 - angle;
		return angle;
	}

	// 값을 일정 비율로 보간
	float Lerp(float from, float to, float rate)
	{
		rate = Clamp(rate, 0.0f, 1.0f);
		return from + (to - from) * rate;
	}

	// 벡터를 일정 비율로 보간
	Vector Lerp(Vector from, Vector to, float rate)
	{
		rate = Clamp(rate, 0.0f, 1.0f);
		return from * (1 - rate) + to * rate;
	}

	// 값을 일정 값만큼 보간
	float MoveForward(float from, float to, float delta)
	{
		float rate = delta / abs(from - to);
		return Lerp(from, to, rate);
	}

	// 벡터를 일정 값만큼 보간
	Vector MoveForward(Vector from, Vector to, float delta)
	{
		float rate = delta / (to - from).Magnitude();
		return Lerp(from, to, rate);
	}

	// 점에서 선까지 가장 가까운 점 반환
	Vector ClosestPoint(Vector point, Line line)
	{
		Vector vToPoint = point - line.StartPoint();

		float length = Dot(vToPoint, line.dir);
		length = Clamp(length, 0.0f, line.length);

		return line.StartPoint() + line.dir * length;
	}

	// 1차 함수 그래프
	float LinearGraph(Vector point, float slope, float x)
	{
		return slope * (x - point.x) + point.y;
	}

	// 2차 함수 그래프
	float QuadricGraph(Vector point, Vector vertex, float x)
	{
		float a = (point.y - vertex.y) / pow(point.x - vertex.x, 2);
		return a * pow(x - vertex.x, 2) + vertex.y;
	}

	// Sin 함수 그래프
	float SinGraph(float height, float angle)
	{
		return Sin(angle) * -height;
	}

	// Cos 함수 그래프
	float CosGraph(float height, float angle)
	{
		return Cos(angle) * -height;
	}

	// 점과 선 충돌
	bool IsCollided(Vector point, Line line)
	{
		float y = LinearGraph(line.point, line.Slope(), point.x);
		if (abs(point.y - y) < 0.01)
		{
			return Dot(point - line.StartPoint(), line.EndPoint() - point) > 0;
		}
		return false;
	}

	// 점과 원 충돌
	bool IsCollided(Vector point, Circle circle)
	{
		float sqrDist = SqrDistance2(point, circle.center);
		return sqrDist <= circle.radius * circle.radius;
	}

	// 점과 사각형 충돌
	bool IsCollided(Vector point, Box2 box)
	{
		// AABB 충돌
		//Vector leftTop = box.LeftTop();
		//Vector rightBottom = box.RightBottom();
		//return point.x >= leftTop.x && point.x <= rightBottom.x
		//	&& point.y >= leftTop.y && point.y <= rightBottom.y;

		// OBB 충돌
		float distX = ProjectAbsLength(point - box.center, Vector::Right());
		float halfWidth = ProjectAbsLength(box.Width() * 0.5f, Vector::Right())
			+ ProjectAbsLength(box.Height() * 0.5f, Vector::Right());
		if (distX > halfWidth) return false;

		float distY = ProjectAbsLength(point - box.center, Vector::Down());
		float halfHeight = ProjectAbsLength(box.Width() * 0.5f, Vector::Down())
			+ ProjectAbsLength(box.Height() * 0.5f, Vector::Down());
		if (distY > halfHeight) return false;

		distX = ProjectAbsLength(point - box.center, box.dirX);
		if (distX > box.size.x * 0.5f) return false;

		distY = ProjectAbsLength(point - box.center, box.dirY);
		if (distY > box.size.y * 0.5f) return false;

		return true;
	}

	// 점과 삼각형 충돌
	bool IsCollided(Vector point, Triangle tri)
	{
		bool dir0 = CrossZ(tri.p1 - tri.p0, point - tri.p1) > 0;
		bool dir1 = CrossZ(tri.p2 - tri.p1, point - tri.p2) > 0;
		bool dir2 = CrossZ(tri.p0 - tri.p2, point - tri.p0) > 0;
		return dir0 == dir1 && dir0 == dir2;
	}

	// 원과 선 충돌
	bool IsCollided(Circle circle, Line line)
	{
		Vector pos = ClosestPoint(circle.center, line);
		return SqrDistance2(pos, circle.center) <= circle.radius * circle.radius;
	}

	// 원과 원 충돌
	bool IsCollided(Circle c0, Circle c1)
	{
		float totalRadius = c0.radius + c1.radius;
		return SqrDistance2(c0.center, c1.center) <= totalRadius * totalRadius;
	}

	// 원과 박스 충돌
	bool IsCollided(Circle circle, Box2 box)
	{
		if (IsCollided(circle.center, box)) return true;
		if (IsCollided(circle, Line(box.LeftTop(), box.RightTop()))) return true;
		if (IsCollided(circle, Line(box.LeftTop(), box.LeftBottom()))) return true;
		if (IsCollided(circle, Line(box.RightBottom(), box.RightTop()))) return true;
		if (IsCollided(circle, Line(box.RightBottom(), box.LeftBottom()))) return true;
		return false;
	}

	// 원과 삼각형 충돌
	bool IsCollided(Circle circle, Triangle triangle)
	{
		if (IsCollided(circle.center, triangle)) return true;
		if (IsCollided(circle, Line(triangle.p0, triangle.p1))) return true;
		if (IsCollided(circle, Line(triangle.p1, triangle.p2))) return true;
		if (IsCollided(circle, Line(triangle.p2, triangle.p0))) return true;
		return false;
	}

	// 선과 선 충돌
	bool IsCollided(Line lineA, Line lineB)
	{
		// dir = (y - y1) - m(x - x1)
		float dirA1 = (lineA.StartPoint().y - lineB.StartPoint().y)
			- lineB.Slope() * (lineA.StartPoint().x - lineB.StartPoint().x);
		float dirA2 = (lineA.EndPoint().y - lineB.StartPoint().y)
			- lineB.Slope() * (lineA.EndPoint().x - lineB.StartPoint().x);

		if (dirA1 * dirA2 < 0)
		{
			float dirB1 = (lineB.StartPoint().y - lineA.StartPoint().y)
				- lineA.Slope() * (lineB.StartPoint().x - lineA.StartPoint().x);
			float dirB2 = (lineB.EndPoint().y - lineA.StartPoint().y)
				- lineA.Slope() * (lineB.EndPoint().x - lineA.StartPoint().x);
			return dirB1 * dirB2 < 0;
		}
		return false;
	}

	// 선과 선의 충돌점 반환
	Vector GetCollidedPoint(Line lineA, Line lineB)
	{
		// 교점 x = (A기울기 * A점x - A점y - B기울기 * B점x + B점y) / (A기울기 - B기울기)
		float x = (lineA.Slope() * lineA.StartPoint().x - lineA.StartPoint().y
			- lineB.Slope() * lineB.StartPoint().x + lineB.StartPoint().y)
			/ (lineA.Slope() - lineB.Slope());

		// 교점 y = A기울기 * (x - A점x) + A점y
		float y = lineA.Slope() * (x - lineA.StartPoint().x) + lineA.StartPoint().y;

		return Vector(x, y);
	}

	// 선과 박스 충돌
	bool IsCollided(Line line, Box2 box)
	{
		if (IsCollided(line.StartPoint(), box)) return true;
		if (IsCollided(line.EndPoint(), box)) return true;
		if (IsCollided(line, Line(box.LeftTop(), box.RightTop()))) return true;
		if (IsCollided(line, Line(box.LeftTop(), box.LeftBottom()))) return true;
		if (IsCollided(line, Line(box.RightBottom(), box.RightTop()))) return true;
		if (IsCollided(line, Line(box.RightBottom(), box.LeftBottom()))) return true;
		return false;
	}

	// 선과 삼각형 충돌
	bool IsCollided(Line line, Triangle triangle)
	{
		if (IsCollided(line.StartPoint(), triangle)) return true;
		if (IsCollided(line.EndPoint(), triangle)) return true;
		if (IsCollided(line, Line(triangle.p0, triangle.p1))) return true;
		if (IsCollided(line, Line(triangle.p1, triangle.p2))) return true;
		if (IsCollided(line, Line(triangle.p2, triangle.p0))) return true;
		return false;
	}

	// 박스와 박스 충돌
	bool IsCollided(Box2 a, Box2 b)
	{
		float distX = ProjectAbsLength(a.center - b.center, Vector::Right());
		float aHalfWidth = ProjectAbsLength(a.Width() * 0.5f, Vector::Right())
			+ ProjectAbsLength(a.Height() * 0.5f, Vector::Right());
		float bHalfWidth = ProjectAbsLength(b.Width() * 0.5f, Vector::Right())
			+ ProjectAbsLength(b.Height() * 0.5f, Vector::Right());
		if (distX > aHalfWidth + bHalfWidth) return false;

		float distY = ProjectAbsLength(a.center - b.center, Vector::Down());
		float aHalfHeight = ProjectAbsLength(a.Width() * 0.5f, Vector::Down())
			+ ProjectAbsLength(a.Height() * 0.5f, Vector::Down());
		float bHalfHeight = ProjectAbsLength(b.Width() * 0.5f, Vector::Down())
			+ ProjectAbsLength(b.Height() * 0.5f, Vector::Down());
		if (distY > aHalfHeight + bHalfHeight) return false;

		distX = ProjectAbsLength(a.center - b.center, a.dirX);
		aHalfWidth = ProjectAbsLength(a.Width() * 0.5f, a.dirX) + ProjectAbsLength(a.Height() * 0.5f, a.dirX);
		bHalfWidth = ProjectAbsLength(b.Width() * 0.5f, a.dirX) + ProjectAbsLength(b.Height() * 0.5f, a.dirX);
		if (distX > aHalfWidth + bHalfWidth) return false;

		distY = ProjectAbsLength(a.center - b.center, a.dirY);
		aHalfHeight = ProjectAbsLength(a.Width() * 0.5f, a.dirY) + ProjectAbsLength(a.Height() * 0.5f, a.dirY);
		bHalfHeight = ProjectAbsLength(b.Width() * 0.5f, a.dirY) + ProjectAbsLength(b.Height() * 0.5f, a.dirY);
		if (distY > aHalfHeight + bHalfHeight) return false;

		distX = ProjectAbsLength(a.center - b.center, b.dirX);
		aHalfWidth = ProjectAbsLength(a.Width() * 0.5f, b.dirX) + ProjectAbsLength(a.Height() * 0.5f, b.dirX);
		bHalfWidth = ProjectAbsLength(b.Width() * 0.5f, b.dirX) + ProjectAbsLength(b.Height() * 0.5f, b.dirX);
		if (distX > aHalfWidth + bHalfWidth) return false;

		distY = ProjectAbsLength(a.center - b.center, b.dirY);
		aHalfHeight = ProjectAbsLength(a.Width() * 0.5f, b.dirY) + ProjectAbsLength(a.Height() * 0.5f, b.dirY);
		bHalfHeight = ProjectAbsLength(b.Width() * 0.5f, b.dirY) + ProjectAbsLength(b.Height() * 0.5f, b.dirY);
		if (distY > aHalfHeight + bHalfHeight) return false;

		return true;
	}


};