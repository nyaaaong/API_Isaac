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
	float	fHypotenuse = Distance(pSrc, pDest); // ������ ����
	float	fBase = pDest.x - pSrc.x; // �غ��� ����

	float	fAngle = fBase / fHypotenuse; // cos�� �� �����ش� (-1 ~ 1)

	// ��(����)�� ���ϱ� ���ؼ��� acos(���Լ�)�� cos�ȸ� �־���� �Ѵ�. �׸��� Radian�� �����ϱ� ������ ��ȯ �Լ��� ������ش�.
	fAngle = RadianToDegree(acosf(fAngle));

	// cos�ȴ� 180�� ���ؿ����ۿ� ������ �ʴ´�. 
	// �׷��Ƿ� �ڽź��� ����� �� ���� �ִ� ��� 360���� ������ ���ش�.

	if (pDest.y < pSrc.y)
		fAngle = 360.f - fAngle;

	return fAngle;
}
