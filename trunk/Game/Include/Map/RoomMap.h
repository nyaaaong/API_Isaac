#pragma once

#include "../GameInfo.h"
#include "../Resource/Texture.h"
#include "RoomObj.h"

class CRoomMap
{
	friend class CScene;
	friend class CMapManager;
	friend class CMonsterSpawner;

protected:
	CRoomMap();
	virtual ~CRoomMap();

protected:
	CSharedPtr<CTexture>	m_pBackGround;
	std::string	m_strName;
	Vector2	m_tPos;
	Vector2	m_tSize;
	bool	m_bEnable;
	bool	m_bActive;
	bool	m_bIsSpecial;
	int		m_iRoomNum;
	std::list<CRoomObj*>	m_RoomObjList;
	ESpecial_RoomType	m_eSpecialRoomType;
	bool	m_bIsClear;

public:
	ESpecial_RoomType GetSpecialRoomType()	const
	{
		return m_eSpecialRoomType;
	}

	bool IsSpecialRoomMap()	const
	{
		return m_bIsSpecial;
	}

	int GetRoomNumber()	const
	{
		return m_iRoomNum;
	}

	bool IsActive()	const
	{
		return m_bActive;
	}

	bool IsEnable()	const
	{
		return m_bEnable;
	}

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
	void SetSpecialRoomType(ESpecial_RoomType eType)
	{
		m_eSpecialRoomType = eType;
	}

	void SetSpecialRoomMap(bool bIsSpecial)
	{
		m_bIsSpecial = bIsSpecial;
	}

	void SetRoomNumber(int iNum)
	{
		m_iRoomNum = iNum;
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
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Render(HDC hDC);

public:
	bool IsObj(class CScene* pCurScene, const Vector2& tPos, EMapObject_Type eType = MT_MAX); // ��ġ�� ������Ʈ�� �ִ���
	bool IsObj(class CScene* pCurScene, const Vector2& tStartPos, const Vector2& tEndPos, EMapObject_Type eType = MT_MAX); // StartPos ~ EndPos ��� üũ�� �Ѵ�.
	bool IsObj(class CScene* pCurScene, float x, float y, EMapObject_Type eType = MT_MAX);
	bool IsSetObj(class CScene* pCurScene, const Vector2& tPos, const Vector2& tObjSize = Vector2(75.f, 75.f)); // ��ġ�� ������ ��������
	void Create(class CScene* pCurScene, EMapObject_Type eObj, const Vector2& tPos, const Vector2& tObjSize = Vector2(75.f, 75.f));
	void Delete(class CScene* pCurScene, const Vector2& tPos);
	void DeleteSpawn(class CScene* pCurScene, const Vector2& tPos);
	void Clear();
	void Save(FILE* pFile);
	void Load(class CScene* pCurScene, FILE* pFile);
	CRoomObj* GetRoomObj(class CScene* pCurScene, const Vector2& tPos)	const;

protected:
	void SaveFile(const char* cFileName, const std::string& strPath = MAP_PATH);
	void SaveFullPath(const char* cFullPath);
	void LoadFile(class CScene* pCurScene, const char* cFileName, const std::string& strPath = MAP_PATH);
	void LoadFullPath(class CScene* pCurScene, const char* cFullPath);
};

