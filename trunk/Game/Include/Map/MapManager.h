#pragma once

#include "../GameInfo.h"
#include "RoomMap.h"

class CMapManager
{
private:
	CMapManager();
	~CMapManager();

private:
	static	CMapManager* m_pInst;

public:
	static CMapManager* GetInst()
	{
		if (!m_pInst)
			m_pInst = new CMapManager;

		return m_pInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
	}

private:
	std::unordered_map<ESpecial_RoomType, CRoomMap*>	m_mapSpecialRoomMap;
	std::vector<CRoomMap*>	m_vecRoomMap;

public:
	bool HasRoomMap()	const
	{
		return !m_vecRoomMap.empty();
	}

public:
	bool Init();
	//void Start();
	void RoomUpdater();
	//void Update(float fTime);
	//void PostUpdate(float fTime);
	//void Collision(float fTime);
	//void Render(HDC hDC);

public:
	void SetMap(class CScene* pCurScene, int iRoomNum);
	void SetSpecialMap(class CScene* pCurScene, ESpecial_RoomType eType);
	
public:
	void SaveFullPath(const char* cFullPath);
	void LoadFullPath(class CScene* pCurScene, const char* cFullPath);

public:
	void CreateRoomMap(class CScene* pCurScene, const std::string& strName, int iRoomNum, const Vector2& tPos = Vector2(0.f, 0.f), const Vector2& tSize = Vector2(1280.f, 720.f));
	void CreateSpecialRoomMap(class CScene* pCurScene, ESpecial_RoomType eType, const Vector2& tPos = Vector2(0.f, 0.f), const Vector2& tSize = Vector2(1280.f, 720.f));

private:
	void RoomShuffle();
};

