#pragma once

#include "../GameInfo.h"
#include "../Object/Obj.h"

class CCamera
{
	friend class CScene;

private:
	Vector2		m_tPos;
	Vector2		m_tResolution;
	Vector2		m_tWorldResolution;
	CSharedPtr<CObj>	m_pTarget;
	Vector2		m_tTargetOffset;
	Vector2		m_tTargetPivot;

public:
	const Vector2& GetPos()	const
	{
		return m_tPos;
	}

	const Vector2& GetResolution()	const
	{
		return m_tResolution;
	}

	const Vector2& GetWorldResolution()	const
	{
		return m_tWorldResolution;
	}

	const Vector2& GetTargetOffset()	const
	{
		return m_tTargetOffset;
	}

	const Vector2& GetTargetPivot()	const
	{
		return m_tTargetPivot;
	}

public:
	void SetPos(const Vector2& tPos)
	{
		m_tPos = tPos;
	}

	void SetPos(float x, float y)
	{
		m_tPos = Vector2(x, y);
	}

	void SetResolution(const Vector2& tResolution)
	{
		m_tResolution = tResolution;
	}

	void SetResolution(float x, float y)
	{
		m_tResolution = Vector2(x, y);
	}

	void SetWorldResolution(const Vector2& tWorldResolution)
	{
		m_tWorldResolution = tWorldResolution;
	}

	void SetWorldResolution(float x, float y)
	{
		m_tWorldResolution = Vector2(x, y);
	}

	void SetTargetOffset(const Vector2& tTargetOffset)
	{
		m_tTargetOffset = tTargetOffset;
	}

	void SetTargetOffset(float x, float y)
	{
		m_tTargetOffset = Vector2(x, y);
	}

	void SetTargetPivot(const Vector2& tTargetPivot)
	{
		m_tTargetPivot = tTargetPivot;
	}

	void SetTargetPivot(float x, float y)
	{
		m_tTargetPivot = Vector2(x, y);
	}

	void SetTarget(CObj* pTarget)
	{
		m_pTarget = pTarget;
	}

	void Move(const Vector2& tMovePos)
	{
		m_tPos += tMovePos;
	}

public:
	bool Init();
	void Update(float fTime);

private:
	CCamera();
	~CCamera();
};

