#pragma once

#include "../GameInfo.h"
#include "../Resource/Texture.h"

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
	bool	m_bEnable;
	bool	m_bActive;
	int		m_iRoomNum;
	CSharedPtr<CTexture>	m_pBackGround;
	std::list<class CMapObj*>	m_ObjList;

public:
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
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Render(HDC hDC);

public:
	void Create(EObject eObj, const Vector2& tPos, const Vector2& tObjSize = Vector2(75.f, 75.f));
	void Delete(const Vector2& tPos);
	void Clear();
	void Save(FILE* pFile);
	void Save(const char* cFileName, const std::string& strPath = MAP_PATH);
	void SaveFullPath(const char* cFullPath);
	void Load(FILE* pFile);
	void Load(const char* cFileName, const std::string& strPath = MAP_PATH);
	void LoadFullPath(const char* cFullPath);
};

