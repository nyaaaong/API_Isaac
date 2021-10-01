#pragma once

#include "../GameInfo.h"
#include "../Resource/Texture.h"

class CMapObj
{
	friend class CMap;

private:
	CMapObj();
	~CMapObj();

private:
	Vector2	m_tPos;
	Vector2	m_tSize;
	CSharedPtr<CTexture>	m_pTexture;
	EObject	m_eObject;
	class CScene* m_pScene;
	int		m_iZOrder;

public:
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

	void SetMapObj(EObject eObj)
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
	bool IsObj(const Vector2& tPos);
	bool IsObj(const Vector2& tPos, const Vector2& tSize);

public:
	void Save(FILE* pFile);
	void Load(FILE* pFile);
};

