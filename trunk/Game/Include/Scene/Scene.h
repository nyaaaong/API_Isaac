#pragma once

#include "../GameInfo.h"
#include "../Object/Obj.h"
#include "../UI/UIWindow.h"

class CScene
{
	friend class CSceneManager;

private:
	std::list<CSharedPtr<CObj>>	m_ObjList;
	std::unordered_map<std::string, CSharedPtr<CObj>>	m_mapPrototype;
	class CSceneResource* m_pResource;
	class CSceneCollision* m_pCollision;
	class CCamera* m_pCamera;
	CSharedPtr<CObj>	m_pPlayer;
	CObj** m_pArrRender;
	int		m_iRenderCount;
	int		m_iRenderCapacity;
	CUIWindow** m_pArrUI;
	int		m_iUICount;
	int		m_iUICapacity;
	Vector2	m_tActivityLT;	// 벽을 제외한 나머지 구역
	Vector2	m_tActivityRB;
	std::vector<class CRoomMap*>	m_vecRoomMap;
	std::unordered_map<ESpecial_RoomType, class CRoomMap*>	m_mapSpecialRoomMap;
	class CRoomMap* m_pCurMap;

protected:
	const int		m_iMaxRoomCount = 20;

public:
	void SetActivityLT(const Vector2& tPos)
	{
		m_tActivityLT = tPos;
	}

	void SetActivityRB(const Vector2& tSize)
	{
		m_tActivityRB = tSize;
	}

public:
	class CRoomMap* GetCurrentMap()	const
	{
		return m_pCurMap;
	}

	CObj* GetPlayer()	const
	{
		return m_pPlayer;
	}

	const Vector2& GetActivityLT()	const
	{
		return m_tActivityLT;
	}

	const Vector2& GetActivityRB()	const
	{
		return m_tActivityRB;
	}

public:
	void SetMap(const std::string& strName, int iRoomNum);
	void SetSpecialMap(ESpecial_RoomType eType);

private:
	CObj* FindPrototype(const std::string& strName);

public:
	CObj* FindObject(const std::string& strName);
	void SetPlayer(const std::string& strName);
	void SetPlayer(CObj* pPlayer);

public:
	class CSceneResource* GetSceneResource()	const;
	class CSceneCollision* GetSceneCollision()	const;
	class CCamera* GetCamera()	const;

public:
	static int SortY(const void* pSrc, const void* pDest);
	static int SortUIZOrder(const void* pSrc, const void* pDest);
	static int SortObjZOrder(const void* pSrc, const void* pDest);

public:
	virtual bool Init();
	virtual bool Update(float fTime);
	virtual bool PostUpdate(float fTime);
	virtual bool Collision(float fTime);
	virtual bool Render(HDC hDC);

private:
	void CreateTextureObject();

protected:
	virtual void SaveFile(const char* cFileName, const std::string& strPath = MAP_PATH);
	virtual void SaveFullPath(const char* cFullPath);
	virtual void LoadFile(const char* cFileName, const std::string& strPath = MAP_PATH);
	virtual void LoadFullPath(const char* cFullPath);

protected:
	CScene();
	virtual ~CScene();

public:
	template <typename T>
	T* CreateObject(const std::string& strName, const Vector2& tPos = Vector2(0.f, 0.f), const Vector2& tSize = Vector2(100.f, 100.f))
	{
		T* pObj = new T;

		pObj->SetScene(this);
		pObj->SetName(strName);
		pObj->SetPos(tPos);
		pObj->SetSize(tSize);

		if (!pObj->Init())
		{
			SAFE_DELETE(pObj);
			return nullptr;
		}

		m_ObjList.push_back(pObj);

		return pObj;
	}

	template <typename T>
	T* CreateObject(const std::string& strName, const std::string& strPrototypeName, const Vector2& tPos = Vector2(0.f, 0.f), const Vector2& tSize = Vector2(100.f, 100.f))
	{
		CObj* pPrototype = FindPrototype(strPrototypeName);

		if (!pPrototype)
			return nullptr;

		T* pObj = static_cast<T*>(pPrototype->Clone());

		pObj->SetScene(this);
		pObj->SetPos(tPos);
		pObj->SetSize(tSize);
		pObj->SetName(strName);

		m_ObjList.push_back(pObj);

		return pObj;
	}

	template <typename T>
	T* CreatePrototype(const std::string& strName)
	{
		T* pObj = new T;

		pObj->SetScene(this);
		pObj->SetName(strName);

		if (!pObj->Init())
		{
			SAFE_DELETE(pObj);
			return nullptr;
		}

		m_mapPrototype.insert(std::make_pair(strName, pObj));

		return pObj;
	}

	template <typename T>
	T* CreateUIWindow(const std::string& strName)
	{
		T* pWindow = new T;

		pWindow->SetName(strName);
		pWindow->SetScene(this);

		if (!pWindow->Init())
		{
			SAFE_DELETE(pWindow);
			return nullptr;
		}

		if (m_iUICount == m_iUICapacity)
		{
			m_iUICapacity *= 2;

			CUIWindow** pArr = new CUIWindow * [m_iUICapacity];

			memcpy(pArr, m_pArrUI, sizeof(CUIWindow*) * m_iUICount);

			SAFE_DELETE_ARRAY(m_pArrUI);

			m_pArrUI = pArr;
		}

		m_pArrUI[m_iUICount] = pWindow;
		++m_iUICount;

		return pWindow;
	}

	template <typename T>
	T* FindUIWindow(const std::string& strName)
	{
		for (int i = 0; i < m_iUICount; ++i)
		{
			if (m_pArrUI[i]->GetName() == strName)
				return static_cast<T*>(m_pArrUI[i]);
		}

		return nullptr;
	}

	template <typename T>
	T* CreateRoomMap(const std::string& strName, int iRoomNum, const Vector2& tPos = Vector2(0.f, 0.f), const Vector2& tSize = Vector2(1280.f, 720.f))
	{
		T* pMap = new T;

		pMap->SetScene(this);
		pMap->SetRoomNumber(iRoomNum);
		pMap->SetPos(tPos);
		pMap->SetSize(tSize);
		pMap->SetName(strName);

		if (!pMap->Init())
		{
			SAFE_DELETE(pMap);
			return nullptr;
		}

		pMap->Start();

		m_vecRoomMap.push_back(pMap);

		return pMap;
	}

	template <typename T>
	T* CreateSpecialRoomMap(ESpecial_RoomType eType, const Vector2& tPos = Vector2(0.f, 0.f), const Vector2& tSize = Vector2(1280.f, 720.f))
	{
		T* pMap = new T;

		pMap->SetScene(this);
		pMap->SetPos(tPos);
		pMap->SetSize(tSize);
		pMap->SetSpecialRoomMap(true);
		pMap->SetSpecialRoomType(eType);

		if (!pMap->Init())
		{
			SAFE_DELETE(pMap);
			return nullptr;
		}

		pMap->Start();

		m_mapSpecialRoomMap.insert(std::make_pair(eType, pMap));

		return pMap;
	}
};

