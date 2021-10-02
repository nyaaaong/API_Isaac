#pragma once

#include "../GameInfo.h"
#include "../Resource/Texture.h"

class CRoomMapObj
{
	friend class CRoomMap;

private:
	CRoomMapObj();
	~CRoomMapObj();

private:
	Vector2	m_tPos;
	Vector2	m_tSize;
	CSharedPtr<CTexture>	m_pTexture;
	EObject	m_eObject;
	class CScene* m_pScene;
	int		m_iZOrder;

public:
	bool IsObj(const Vector2& tPos)
	{
		return IsObj(tPos, m_tSize);
	}

	bool IsObj(const Vector2& tPos, const Vector2& tSize) 
	{
		if (m_tPos.x < tPos.x + tSize.x && m_tPos.x + m_tSize.x > tPos.x &&
			m_tPos.y < tPos.y + tSize.y && m_tPos.y + m_tSize.y > tPos.y)
			return true;

		return false;
	}

	int GetZOrder()	const
	{
		return m_iZOrder;
	}

public:
	void SetObject(EObject eObject)
	{
		m_eObject = eObject;
	}

	void SetZOrder(int iZOrder)
	{
		m_iZOrder = iZOrder;
	}

	void SetPos(const Vector2& tPos)
	{
		m_tPos = tPos;
	}

	void SetSize(const Vector2& tSize)
	{
		m_tSize = tSize;
	}

	void SetRoomMapObj(EObject eObj)
	{
		m_eObject = eObj;
	}

	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
	}

public:
	bool Init();
	void Update(float fTime);
	void PostUpdate(float fTime);
	void Render(HDC hDC);

public:
	void Save(FILE* pFile);
	void Load(FILE* pFile);
};

