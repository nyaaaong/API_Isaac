#pragma once

#include "../GameInfo.h"
#include "../Object/Obj.h"
#include "../UI/UIWindow.h"

class CScene
{
	friend class CSceneManager;

protected:
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
	Vector2	m_tActivityPos;	// ���� ������ ������ ����
	Vector2	m_tActivitySize;

public:
	CObj* GetPlayer()	const
	{
		return m_pPlayer;
	}

	const Vector2& GetActivityPos()	const
	{
		return m_tActivityPos;
	}

	const Vector2& GetActivitySize()	const
	{
		return m_tActivitySize;
	}

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
