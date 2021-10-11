#pragma once

#include "../GameInfo.h"
#include "../Resource/Texture.h"

class CRoomObj
{
	friend class CRoomMap;
	friend class CBlock;

private:
	CRoomObj();
	~CRoomObj();

private:
	Vector2	m_tPos;
	Vector2	m_tSize;
	CSharedPtr<CTexture>	m_pTexture;
	EMapObject_Type	m_eType;
	class CScene* m_pScene;
	int		m_iZOrder;
	float		m_fLife; // 0이 되면 씬에서의 오브젝트 제거. RoomObj 자체를 제거하지는 않는다.
	float		m_fMaxLife;

public:
	const Vector2& GetPos()	const
	{
		return m_tPos;
	}

	const Vector2& GetSize()	const
	{
		return m_tSize;
	}

	EMapObject_Type GetType()	const
	{
		return m_eType;
	}

	bool IsObj(const Vector2& tPos)
	{
		return IsObj(tPos, m_tSize);
	}

	bool IsObj(const Vector2& tPos, const Vector2& tSize) 
	{
		if (m_fLife != 0.f && (m_tPos.x < tPos.x + tSize.x && m_tPos.x + m_tSize.x > tPos.x &&
			m_tPos.y < tPos.y + tSize.y && m_tPos.y + m_tSize.y > tPos.y))
			return true;

		return false;
	}

	int GetZOrder()	const
	{
		return m_iZOrder;
	}

public:
	void SetObject(EMapObject_Type eType)
	{
		m_eType = eType;
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

private:
	void RockUpdater();
	void PoopUpdater();
};

