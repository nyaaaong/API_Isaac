#pragma once

#include "../GameInfo.h"
#include "../Resource/Texture.h"
#include "RoomObj.h"

class CRoomMap
{
	friend class CScene;

protected:
	CRoomMap();
	virtual ~CRoomMap();

protected:
	class CScene* m_pScene;
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
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Render(HDC hDC);

public:
	bool IsObj(const Vector2& tPos); // 위치에 오브젝트가 있는지
	bool IsObj(float x, float y);
	bool IsSetObj(const Vector2& tPos, const Vector2& tObjSize = Vector2(75.f, 75.f)); // 설치가 가능한 구역인지
	void Create(EMapObject_Type eObj, const Vector2& tPos, const Vector2& tObjSize = Vector2(75.f, 75.f));
	void Delete(const Vector2& tPos);
	void Clear();
	void Save(FILE* pFile);
	void Load(FILE* pFile);
	CRoomObj* GetRoomObj(const Vector2& tPos)	const;

protected:
	virtual void SaveFile(const char* cFileName, const std::string& strPath = MAP_PATH);
	virtual void SaveFullPath(const char* cFullPath);
	virtual void LoadFile(const char* cFileName, const std::string& strPath = MAP_PATH);
	virtual void LoadFullPath(const char* cFullPath);
};

