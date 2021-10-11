#pragma once

#include "../GameInfo.h"
#include "../Object/Obj.h"
#include "../UI/UIWindow.h"

class CScene
{
	friend class CSceneManager;
	friend class CMapManager;

private:
	std::list<CSharedPtr<CObj>>	m_ObjList;
	std::unordered_map<std::string, CSharedPtr<CObj>>	m_mapPrototype;
	class CSceneResource* m_pResource;
	class CSceneCollision* m_pCollision;
	class CCamera* m_pCamera;
	class CRoomMap* m_pCurMap;
	CObj** m_pArrRender;
	CUIWindow** m_pArrUI;
	CSharedPtr<CObj>	m_pPlayer;
	CSharedPtr<CObj>	m_pPlayerBody;
	Vector2	m_tFieldLT;	// 벽을 제외한 나머지 구역
	Vector2	m_tFieldRB;
	int		m_iRenderCount;
	int		m_iRenderCapacity;
	int		m_iUICount;
	int		m_iUICapacity;
	bool	m_bStart;

protected:
	const int		m_iMaxRoomCount = 10;

public:
	void SetFieldLT(const Vector2& tPos)
	{
		m_tFieldLT = tPos;
	}

	void SetFieldRB(const Vector2& tSize)
	{
		m_tFieldRB = tSize;
	}

public:
	bool IsStart()	const
	{
		return m_bStart;
	}

	class CRoomMap* GetCurrentMap()	const
	{
		return m_pCurMap;
	}

	CObj* GetPlayerBody()	const
	{
		return m_pPlayerBody;
	}

	CObj* GetPlayer()	const
	{
		return m_pPlayer;
	}

	const Vector2& GetFieldLT()	const
	{
		return m_tFieldLT;
	}

	const Vector2& GetFieldRB()	const
	{
		return m_tFieldRB;
	}

	class CSceneResource* GetSceneResource()	const
	{
		return m_pResource;
	}

	class CSceneCollision* GetSceneCollision()	const
	{
		return m_pCollision;
	}

	class CCamera* GetCamera()	const
	{
		return m_pCamera;
	}

public:
	void LoadMapObject();

private:
	CObj* FindPrototype(const std::string& strName);

public:
	CObj* FindObject(const std::string& strName);
	void SetPlayer(CObj* pPlayerHead, CObj* pPlayerBody);
	void SetPlayerPos(const Vector2& tPos);
	void SetPlayerPos(float x, float y);
	void SetPlayerPosX(float x);
	void SetPlayerPosY(float y);
	void SetPlayerMove(const Vector2& tPos);
	void SetPlayerMove(float x, float y);
	void SetPlayerMoveX(float x);
	void SetPlayerMoveY(float y);
	bool CheckFieldPos(CObj* pCharacter);
	bool IsObj(const Vector2& tPos);
	bool IsObj(float x, float y);

public:
	static int SortY(const void* pSrc, const void* pDest);
	static int SortUIZOrder(const void* pSrc, const void* pDest);
	static int SortObjZOrder(const void* pSrc, const void* pDest);

public:
	virtual bool Init();
	virtual void Start();
	virtual bool Update(float fTime);
	virtual bool PostUpdate(float fTime);
	virtual bool Collision(float fTime);
	virtual bool Render(HDC hDC);

private:
	void Init_CreateTextureObject();

protected:
	void SaveFile(const char* cFileName, const std::string& strPath = MAP_PATH);
	void SaveFullPath(const char* cFullPath);
	void LoadFile(const char* cFileName, const std::string& strPath = MAP_PATH);
	void LoadFullPath(const char* cFullPath);

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

	
};

