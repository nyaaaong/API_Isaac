
#pragma once

#include <Windows.h>
#include <math.h>

#define PI	3.141592f

float RadianToDegree(float fRadian);
float DegreeToRadian(float fDegree);

struct Vector2
{
public:
	float x;
	float y;

public:
	const Vector2& operator = (const Vector2& v)
	{
		x = v.x;
		y = v.y;

		return *this;
	}

	const Vector2& operator  = (const POINT& v)
	{
		x = static_cast<float>(v.x);
		y = static_cast<float>(v.y);

		return *this;
	}

	Vector2 operator + (const Vector2& v)	const
	{
		Vector2 _v;
		_v.x = x + v.x;
		_v.y = y + v.y;
		return _v;
	}

	Vector2 operator + (const POINT& v)	const
	{
		Vector2 _v;
		_v.x = x + static_cast<float>(v.x);
		_v.y = y + static_cast<float>(v.y);
		return _v;
	}

	Vector2 operator + (float f)	const
	{
		Vector2 _v;
		_v.x = x + f;
		_v.y = y + f;
		return _v;
	}

	Vector2 operator + (int i)	const
	{
		Vector2 _v;
		_v.x = x + static_cast<float>(i);
		_v.y = y + static_cast<float>(i);
		return _v;
	}

	const Vector2& operator += (const Vector2& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	const Vector2& operator += (const POINT& v)
	{
		x += static_cast<float>(v.x);
		y += static_cast<float>(v.y);
		return *this;
	}

	const Vector2& operator += (float f)
	{
		x += f;
		y += f;
		return *this;
	}

	const Vector2& operator += (int i)
	{
		x += static_cast<float>(i);
		y += static_cast<float>(i);
		return *this;
	}

	//

	Vector2 operator - (const Vector2& v)	const
	{
		Vector2 _v;
		_v.x = x - v.x;
		_v.y = y - v.y;
		return _v;
	}

	Vector2 operator - (const POINT& v)	const
	{
		Vector2 _v;
		_v.x = x - static_cast<float>(v.x);
		_v.y = y - static_cast<float>(v.y);
		return _v;
	}

	Vector2 operator - (float f)	const
	{
		Vector2 _v;
		_v.x = x - f;
		_v.y = y - f;
		return _v;
	}

	Vector2 operator - (int i)	const
	{
		Vector2 _v;
		_v.x = x - static_cast<float>(i);
		_v.y = y - static_cast<float>(i);
		return _v;
	}

	const Vector2& operator -= (const Vector2& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	const Vector2& operator -= (const POINT& v)
	{
		x -= static_cast<float>(v.x);
		y -= static_cast<float>(v.y);
		return *this;
	}

	const Vector2& operator -= (float f)
	{
		x -= f;
		y -= f;
		return *this;
	}

	const Vector2& operator -= (int i)
	{
		x -= static_cast<float>(i);
		y -= static_cast<float>(i);
		return *this;
	}

	//

	Vector2 operator * (const Vector2& v)	const
	{
		Vector2 _v;
		_v.x = x * v.x;
		_v.y = y * v.y;
		return _v;
	}

	Vector2 operator * (const POINT& v)	const
	{
		Vector2 _v;
		_v.x = x * static_cast<float>(v.x);
		_v.y = y * static_cast<float>(v.y);
		return _v;
	}

	Vector2 operator * (float f)	const
	{
		Vector2 _v;
		_v.x = x * f;
		_v.y = y * f;
		return _v;
	}

	Vector2 operator * (int i)	const
	{
		Vector2 _v;
		_v.x = x * static_cast<float>(i);
		_v.y = y * static_cast<float>(i);
		return _v;
	}

	const Vector2& operator *= (const Vector2& v)
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}

	const Vector2& operator *= (const POINT& v)
	{
		x *= static_cast<float>(v.x);
		y *= static_cast<float>(v.y);
		return *this;
	}

	const Vector2& operator *= (float f)
	{
		x *= f;
		y *= f;
		return *this;
	}

	const Vector2& operator *= (int i)
	{
		x *= static_cast<float>(i);
		y *= static_cast<float>(i);
		return *this;
	}

	//

	Vector2 operator / (const Vector2& v)	const
	{
		Vector2 _v;
		_v.x = x / v.x;
		_v.y = y / v.y;
		return _v;
	}

	Vector2 operator / (const POINT& v)	const
	{
		Vector2 _v;
		_v.x = x / static_cast<float>(v.x);
		_v.y = y / static_cast<float>(v.y);
		return _v;
	}

	Vector2 operator / (float f)	const
	{
		Vector2 _v;
		_v.x = x / f;
		_v.y = y / f;
		return _v;
	}

	Vector2 operator / (int i)	const
	{
		Vector2 _v;
		_v.x = x / static_cast<float>(i);
		_v.y = y / static_cast<float>(i);
		return _v;
	}

	const Vector2& operator /= (const Vector2& v)
	{
		x /= v.x;
		y /= v.y;
		return *this;
	}

	const Vector2& operator /= (const POINT& v)
	{
		x /= static_cast<float>(v.x);
		y /= static_cast<float>(v.y);
		return *this;
	}

	const Vector2& operator /= (float f)
	{
		x /= f;
		y /= f;
		return *this;
	}

	const Vector2& operator /= (int i)
	{
		x /= static_cast<float>(i);
		y /= static_cast<float>(i);
		return *this;
	}

	bool operator == (const Vector2& v)
	{
		return x == v.x && y == v.y;
	}

	bool operator != (const Vector2& v)
	{
		return x != v.x && y != v.y;
	}

	float Length()	const
	{
		return sqrtf(x * x + y * y);
	}

	void Normalize()
	{
		float	length = Length();
		x /= length;
		y /= length;
	}

public:
	static Vector2 UP;
	static Vector2 DOWN;
	static Vector2 LEFT;
	static Vector2 RIGHT;

public:
	Vector2();
	Vector2(float _x, float _y);
	Vector2(const Vector2& v);
};

float Distance(const Vector2& pSrc, const Vector2& pDest);
float GetAngle(const Vector2& pSrc, const Vector2& pDest);