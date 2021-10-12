#pragma once

#include "../Ref.h"
#include "../Resource/Texture.h"
#include "../Animation/Animation.h"
#include "../Collision/Collider.h"

class CObj :
	public CRef
{
	friend class CScene;
	friend class CObjManager;

protected:
	class CScene*			m_pScene;
	class CColliderBox*		m_pColliderBox;
	class CColliderSphere*	m_pColliderSphere;
	CAnimation*				m_pAnimation;
	CSharedPtr<CTexture>	m_pTexture;
	std::list<CSharedPtr<CCollider>>	m_ColliderList;
	Vector2					m_tPos;
	Vector2					m_tRenderPos;
	Vector2					m_tPrevPos;
	Vector2					m_tSize;
	Vector2					m_tPivot;
	Vector2					m_tVelocity;
	Vector2					m_tImgStart;
	Vector2					m_tOffset;
	int						m_iZOrder;
	float					m_fMoveSpeed;
	float					m_fTimeScale;
	float					m_fGravityAcc;
	float					m_fFallTime;
	float					m_fFallStartY;
	float					m_fFallEndY;
	float					m_fJumpVelocity;
	bool					m_bCameraCull;
	bool					m_bStart;
	bool					m_bEnableDamage;
	bool					m_bInvisible;
	bool					m_bPhysics;
	bool					m_bIsGround;
	bool					m_bIsJump;

public:
	bool IsCull()	const
	{
		return m_bCameraCull;
	}

	bool IsInvisible()	const
	{
		return m_bInvisible;
	}

public:
	bool IsEnableDamage()	const
	{
		return m_bEnableDamage;
	}

	int GetZOrder()	const
	{
		return m_iZOrder;
	}

	const Vector2& GetOffset()	const
	{
		return m_tOffset;
	}

	const Vector2& GetPos()	const
	{
		return m_tPos;
	}

	const Vector2& GetPrevPos()	const
	{
		return m_tPrevPos;
	}

	const Vector2& GetSize()	const
	{
		return m_tSize;
	}

	const Vector2& GetPivot()	const
	{
		return m_tPivot;
	}

	const Vector2& GetVelocity()	const
	{
		return m_tVelocity;
	}

	float GetMoveSpeed()	const
	{
		return m_fMoveSpeed;
	}

	float GetMoveSpeedFrame()	const
	{
		return m_tVelocity.Length();
	}

public:
	void SetVelocity(const Vector2& tVelocity)
	{
		m_tVelocity = tVelocity;
	}

	void Jump(float fFallEndY)
	{
		if (!m_bIsJump)
		{
			m_bIsJump = true;
			m_bIsGround = false;

			m_fFallTime = 0.f;
			m_fFallStartY = m_tPos.y;
			m_fFallEndY = fFallEndY;
		}
	}

	void SetGravityAcc(float fAcc)
	{
		m_fGravityAcc = fAcc;
	}

	void SetPhysics(bool bPhysics)
	{
		m_bPhysics = bPhysics;
	}

	void SetJumpVelocity(float fJumpVelocity)
	{
		m_fJumpVelocity = fJumpVelocity;
	}

	void Invisible(bool bInvisible)
	{
		m_bInvisible = bInvisible;
	}

	void EnableDamage(bool bEnable)
	{
		m_bEnableDamage = bEnable;
	}

	void SetZOrder(int iZOrder)
	{
		m_iZOrder = iZOrder;
	}

	void SetZOrder(EZOrder eZOrder)
	{
		m_iZOrder = static_cast<int>(eZOrder);
	}

	void SetTexture(CTexture* pTexture)
	{
		m_pTexture = pTexture;

		if (m_pTexture)
		{
			m_tSize.x = static_cast<float>(m_pTexture->GetWidth());
			m_tSize.y = static_cast<float>(m_pTexture->GetHeight());
		}
	}

	void SetImgStart(float x, float y)
	{
		m_tImgStart.x = x;
		m_tImgStart.y = y;
	}

	void SetImgStart(const Vector2& tImgStart)
	{
		m_tImgStart = tImgStart;
	}

	void SetOffset(float x, float y)
	{
		m_tOffset = Vector2(x, y);
	}

	void SetOffset(const Vector2& tOffset)
	{
		m_tOffset = tOffset;
	}

	void SetPos(float _x, float _y)
	{
		m_tPrevPos.x = _x;
		m_tPrevPos.y = _y;
		m_tPos.x = _x;
		m_tPos.y = _y;
	}

	void SetPos(const Vector2& tPos)
	{
		m_tPrevPos = m_tPos;
		m_tPos = tPos;
	}

	void SetSize(float _x, float _y)
	{
		m_tSize.x = _x;
		m_tSize.y = _y;
	}

	void SetSize(const Vector2& tSize)
	{
		m_tSize = tSize;
	}

	void SetPivot(float _x, float _y)
	{
		m_tPivot.x = _x;
		m_tPivot.y = _y;
	}

	void SetPivot(const Vector2& tPivot)
	{
		m_tPivot = tPivot;
	}

	void SetMoveSpeed(float fSpeed)
	{
		m_fMoveSpeed = fSpeed;
	}

	void SetTimeScale(float fScale)
	{
		m_fTimeScale = fScale;
	}

public:
	CCollider* FindCollider(const std::string& strName);

public:
	void CreateAnimation();
	void AddAnimation(const std::string& strSequenceName, bool bLoop = true, float fPlayTime = 1.f, float fPlayScale = 1.f, bool bReverse = false);
	void SetAnimationPlayTime(const std::string& strName, float fPlayTime);
	void SetAnimationPlayScale(const std::string& strName, float fPlayScale);
	void SetAnimationReverse(const std::string& strName, bool bReverse);
	void SetAnimationLoop(const std::string& strName, bool bLoop);
	void SetCurrentAnimation(const std::string& strName);
	void ChangeAnimation(const std::string& strName);
	bool CheckCurrentAnimation(const std::string& strName);
	void SetScene(class CScene* pScene);

public:
	virtual void Move(const Vector2& tDir, bool bUseField);	// bUseField = true는 활동 범위 내부에서만 움직이게 할 것인지를 뜻한다.
	virtual void Move(const Vector2& tDir, float fSpeed, bool bUseField);
	virtual float SetDamage(float fDamage);
	virtual void CollisionBegin(class CCollider* pSrc, class CCollider* pDest, float fTime);
	virtual void CollisionColliding(class CCollider* pSrc, class CCollider* pDest, float fTime);

public:
	void SetTexture(const std::string& strName);
	void SetTexture(const std::string& strName, const TCHAR* cFileName, const std::string& strPathName = TEXTURE_PATH);
	void SetTexture(const std::string& strName, const std::vector<std::wstring>& vecFileName, const std::string& strPathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& strName, const TCHAR* cFullPath);
	void SetTextureColorKey(const unsigned char r = 255, const unsigned char g = 0, const unsigned char b = 255, int iIdx = 0);

public:
	float GetBottom()	const;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void PrevRender();
	virtual void Render(HDC hDC);
	virtual CObj* Clone();

public:
	CObj();
	CObj(const CObj& obj);
	virtual ~CObj();

public:
	template <typename T>
	void SetAnimationEndNotify(const std::string& strSequenceName, T* pObj, void(T::* pFunc)())
	{
		m_pAnimation->SetEndNotify<T>(strSequenceName, pObj, pFunc);
	}

	template <typename T>
	void AddAnimationNotify(const std::string& strSequenceName, int iFrame, T* pObj, void(T::* pFunc)())
	{
		m_pAnimation->AddNotify<T>(strSequenceName, iFrame, pObj, pFunc);
	}

	template <typename T>
	T* AddCollider(const std::string& strName)
	{
		T* pCollider = new T;

		pCollider->SetName(strName);
		pCollider->SetOwner(this);
		pCollider->SetScene(m_pScene);

		if (!pCollider->Init())
		{
			SAFE_DELETE(pCollider);
			return nullptr;
		}

		m_ColliderList.push_back(pCollider);

		return pCollider;
	}
};

