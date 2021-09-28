#pragma once

#include "../GameInfo.h"

class CMap
{
	friend class CScene;

protected:
	CMap();
	virtual ~CMap();

protected:
	class CScene* m_pScene;
	std::string	m_strName;
	Vector2	m_tPos;
	Vector2	m_tSize;

public:
	const std::string& GetName()	const
	{
		return m_strName;
	}

	const Vector2& GetPos()	const
	{
		return m_tPos;
	}

	const Vector2& GetSize()	const
	{
		return m_tSize;
	}

public:
	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
	}

	void SetName(const std::string& strName)
	{
		m_strName = strName;
	}

	void SetPos(const Vector2& tPos)
	{
		m_tPos = tPos;
	}

	void SetPos(float x, float y)
	{
		m_tPos = Vector2(x, y);
	}

	void SetSize(const Vector2& tSize)
	{
		m_tSize = tSize;
	}

	void SetSize(float x, float y)
	{
		m_tSize = Vector2(x, y);
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void PrevRender();
	virtual void Render(HDC hDC);
};

