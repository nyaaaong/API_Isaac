#include "Math.h"

Vector2	Vector2::UP = Vector2(0.f, -1.f);
Vector2	Vector2::DOWN = Vector2(0.f, 1.f);
Vector2	Vector2::LEFT = Vector2(-1.f, 0.f);
Vector2	Vector2::RIGHT = Vector2(1.f, 0.f);

Vector2::Vector2()	:
	x(0.f),
	y(0.f)
{
}

Vector2::Vector2(float _x, float _y)	:
	x(_x),
	y(_y)
{
}

Vector2::Vector2(const Vector2& v)	:
	x(v.x),
	y(v.y)
{
}

float RadianToDegree(float fRadian)
{
    return fRadian * 180.f / PI;
}

float DegreeToRadian(float fDegree)
{
    return fDegree * PI / 180.f;
}

float Distance(const Vector2& pSrc, const Vector2& pDest)
{
	Vector2	tResult = pSrc - pDest;

    return tResult.Length();
}

float GetAngle(const Vector2& pSrc, const Vector2& pDest)
{
	float	fHypotenuse = Distance(pSrc, pDest); // 빗변의 길이
	float	fBase = pDest.x - pSrc.x; // 밑변의 길이

	float	fAngle = fBase / fHypotenuse; // cosΘ 를 구해준다 (-1 ~ 1)

	// Θ(각도)를 구하기 위해서는 acos(역함수)에 cosΘ를 넣어줘야 한다. 그리고 Radian을 리턴하기 때문에 변환 함수를 사용해준다.
	fAngle = RadianToDegree(acosf(fAngle));

	// cosΘ는 180도 기준에서밖에 나오지 않는다. 
	// 그러므로 자신보다 대상이 더 위에 있는 경우 360도에 각도를 빼준다.

	if (pDest.y < pSrc.y)
		fAngle = 360.f - fAngle;

	return fAngle;
}
