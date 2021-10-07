
#include "Obj.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/SceneCollision.h"
#include "../Resource/AnimationSequence.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderSphere.h"

void CObj::SetTexture(const std::string& strName)
{
	m_pTexture = m_pScene->GetSceneResource()->FindTexture(strName);

	if (m_pTexture)
	{
		m_tSize.x = static_cast<float>(m_pTexture->GetWidth());
		m_tSize.y = static_cast<float>(m_pTexture->GetHeight());
	}
}

void CObj::SetTexture(const std::string& strName, const TCHAR* cFileName, const std::string& strPathName)
{
	m_pScene->GetSceneResource()->LoadTexture(strName, cFileName, strPathName);

	m_pTexture = m_pScene->GetSceneResource()->FindTexture(strName);

	if (m_pTexture)
	{
		m_tSize.x = static_cast<float>(m_pTexture->GetWidth());
		m_tSize.y = static_cast<float>(m_pTexture->GetHeight());
	}
}

void CObj::SetTexture(const std::string& strName, const std::vector<std::wstring>& vecFileName, const std::string& strPathName)
{
	m_pScene->GetSceneResource()->LoadTexture(strName, vecFileName, strPathName);

	m_pTexture = m_pScene->GetSceneResource()->FindTexture(strName);

	if (m_pTexture)
	{
		m_tSize.x = static_cast<float>(m_pTexture->GetWidth());
		m_tSize.y = static_cast<float>(m_pTexture->GetHeight());
	}
}

void CObj::SetTextureFullPath(const std::string& strName, const TCHAR* cFullPath)
{
	m_pScene->GetSceneResource()->LoadTextureFullPath(strName, cFullPath);

	m_pTexture = m_pScene->GetSceneResource()->FindTexture(strName);

	if (m_pTexture)
	{
		m_tSize.x = static_cast<float>(m_pTexture->GetWidth());
		m_tSize.y = static_cast<float>(m_pTexture->GetHeight());
	}
}

void CObj::SetTextureColorKey(const unsigned char r, const unsigned char g, const unsigned char b, int iIdx)
{
	if (m_pTexture)
		m_pTexture->SetColorKey(r, g, b, iIdx);
}

float CObj::GetBottom() const
{
	Vector2	tSize = m_tSize;

	if (m_pAnimation)
	{
		AnimationInfo* pAnimInfo = m_pAnimation->m_pCurrentAnimation;
		const AnimationFrameData& pFrameData = pAnimInfo->pSequence->GetFrameData(pAnimInfo->iFrame);

		tSize = pFrameData.tSize;
	}

	return m_tPos.y + (1.f - m_tPivot.y) * tSize.y + m_tOffset.y;
}

void CObj::SetScene(CScene* pScene)
{
	m_pScene = pScene;

	if (m_pAnimation)
		m_pAnimation->m_pScene = pScene;
}

void CObj::Move(const Vector2& tDir, bool bUseField)
{
	Move(tDir, m_fMoveSpeed, bUseField);
}

void CObj::Move(const Vector2& tDir, float fSpeed, bool bUseField)
{
	Vector2	tCurMove = tDir * fSpeed * CGameManager::GetInst()->GetDeltaTime() * m_fTimeScale;
	m_tVelocity += tCurMove;
	m_tPrevPos = m_tPos;
	m_tPos += tCurMove;

	if (bUseField)
	{
		Vector2	tFieldLT = m_pScene->GetFieldLT();
		Vector2	tFieldRB = m_pScene->GetFieldRB();
		
		if (m_tPos.x - m_tSize.x * m_tPivot.x + m_tOffset.x < tFieldLT.x)
			m_tPos.x = tFieldLT.x + m_tSize.x * m_tPivot.x - m_tOffset.x;

		else if (m_tPos.y - m_tSize.y * m_tPivot.y + m_tOffset.y < tFieldLT.y)
			m_tPos.y = tFieldLT.y + m_tSize.y * m_tPivot.y - m_tOffset.y;

		else if (m_tPos.x + m_tSize.x * m_tPivot.x + m_tOffset.x > tFieldRB.x)
			m_tPos.x = tFieldRB.x - m_tSize.x * m_tPivot.x - m_tOffset.x;

		else if (m_tPos.y + m_tSize.y * m_tPivot.y + m_tOffset.y > tFieldRB.y)
			m_tPos.y = tFieldRB.y - m_tSize.y * m_tPivot.y - m_tOffset.y;
	}
}

float CObj::SetDamage(float fDamage)
{
	if (!m_bEnableDamage)
		return 0.f;

	return fDamage;
}

void CObj::CollisionBegin(CCollider* pSrc, CCollider* pDest, float fTime)
{
}

void CObj::Start()
{
	m_bStart = true;

	m_fFallStartY = m_tPos.y;
}

bool CObj::Init()
{
	return true;
}

void CObj::Update(float fTime)
{
	if (!m_bStart)
		Start();

	if (m_pAnimation)
		m_pAnimation->Update(fTime);

	if (!m_bIsGround && m_bPhysics)
	{
		m_fFallTime += fTime * m_fGravityAcc;

		/*
		9.8 m/s^2
		V: 속도, A: 가속도, G : 중력
		y = V * A - 0.5 * G * t * t
		0 = 0.5GA^2 * VA - y
		-b += 루트(b^2 - 4ac) / 2a
		*/

		float	fVelocity = 0.f;

		if (m_bIsJump)
			fVelocity = m_fJumpVelocity * m_fFallTime;

		m_tPos.y = m_fFallStartY - (fVelocity - 0.5f * GRAVITY * m_fFallTime * m_fFallTime);
	}

	std::list<CSharedPtr<CCollider>>::iterator	iter = m_ColliderList.begin();
	std::list<CSharedPtr<CCollider>>::iterator	iterEnd = m_ColliderList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
			continue;
		}

		else if ((*iter)->IsEnable())
			(*iter)->Update(fTime);

		++iter;
	}
}

void CObj::PostUpdate(float fTime)
{
	if (m_pAnimation)
	{
		AnimationInfo* pInfo = m_pAnimation->m_pCurrentAnimation;

		if (pInfo)
		{
			const AnimationFrameData& pFrameData = pInfo->pSequence->GetFrameData(pInfo->iFrame);

			m_tSize = pFrameData.tSize;
		}
	}

	std::list<CSharedPtr<CCollider>>::iterator	iter = m_ColliderList.begin();
	std::list<CSharedPtr<CCollider>>::iterator	iterEnd = m_ColliderList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
			continue;
		}

		else if ((*iter)->IsEnable())
			(*iter)->PostUpdate(fTime);

		++iter;
	}

	if (m_bPhysics && !m_bIsGround && m_tPos.y - m_tPrevPos.y > 0.f)
	{
		float	tPosY = m_tPos.y + (1.f - m_tPivot.y) * m_tSize.y;
		float	tPrevPosY = m_tPrevPos.y + (1.f - m_tPivot.y) * m_tSize.y;

		if (m_fFallEndY <= tPosY || m_fFallEndY <= tPrevPosY)
		{
			m_fFallTime = 0.f;
			m_tPos.y = m_fFallEndY;
			m_bIsGround = true;
			m_bIsJump = false;
		}
	}
}

void CObj::Collision(float fTime)
{
	std::list<CSharedPtr<CCollider>>::iterator	iter = m_ColliderList.begin();
	std::list<CSharedPtr<CCollider>>::iterator	iterEnd = m_ColliderList.end();

	for (; iter != iterEnd; ++iter)
	{
		m_pScene->GetSceneCollision()->AddCollider((*iter));
	}
}

void CObj::PrevRender()
{
	CCamera* pCamera = m_pScene->GetCamera();

	m_tRenderPos = m_tPos - pCamera->GetPos();

	Vector2	tSize = m_tSize;

	if (m_pAnimation)
	{
		AnimationInfo* pAnimInfo = m_pAnimation->m_pCurrentAnimation;

		if (pAnimInfo)
		{
			const AnimationFrameData& pFrameData = pAnimInfo->pSequence->GetFrameData(pAnimInfo->iFrame);

			tSize = pFrameData.tSize;
		}
	}

	Vector2	tLT = m_tRenderPos - m_tPivot * tSize + m_tOffset;

	m_bCameraCull = false;

	if (tLT.x + tSize.x < 0.f)
		m_bCameraCull = true;

	else if (tLT.x > pCamera->GetResolution().x)
		m_bCameraCull = true;

	else if (tLT.y + tSize.x < 0.f)
		m_bCameraCull = true;

	else if (tLT.y > pCamera->GetResolution().y)
		m_bCameraCull = true;
}

void CObj::Render(HDC hDC)
{
	if (m_pAnimation)
	{
		AnimationInfo* pAnimInfo = m_pAnimation->m_pCurrentAnimation;

		if (!pAnimInfo)
			return;

		const AnimationFrameData& pFrameData = pAnimInfo->pSequence->GetFrameData(pAnimInfo->iFrame);

		Vector2 tLT = m_tRenderPos - m_tPivot * pFrameData.tSize + m_tOffset;

		if (pAnimInfo->pSequence->GetTextureType() == ETexture_Type::ATLAS)
			pAnimInfo->pSequence->GetTexture()->Render(hDC, tLT, pFrameData.tStartPos, pFrameData.tSize);

		else
			pAnimInfo->pSequence->GetTexture()->Render(hDC, tLT, pFrameData.tStartPos, pFrameData.tSize, pAnimInfo->iFrame);
	}

	else
	{
		Vector2 tLT = m_tRenderPos - m_tPivot * m_tSize + m_tOffset;

		if (m_pTexture)
			m_pTexture->Render(hDC, tLT, m_tImgStart, m_tSize);
	}

	std::list<CSharedPtr<CCollider>>::iterator	iter = m_ColliderList.begin();
	std::list<CSharedPtr<CCollider>>::iterator	iterEnd = m_ColliderList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
			continue;
		}

		else if ((*iter)->IsEnable())
			(*iter)->Render(hDC);

		++iter;
	}

	m_tPrevPos = m_tPos;
	m_tVelocity = Vector2(0.f, 0.f);
}

CObj* CObj::Clone()
{
	return nullptr;
}

CObj::CObj() :
	m_pScene(nullptr),
	m_pAnimation(nullptr),
	m_pPlayerBody(nullptr),
	m_fMoveSpeed(200.f),
	m_fTimeScale(1.f),
	m_bCameraCull(false),
	m_bStart(false),
	m_iZOrder(0),
	m_eObjectType(EObjectType::Object),
	m_bEnableDamage(true),
	m_pColliderBox(nullptr),
	m_pColliderSphere(nullptr),
	m_bInvisible(false),
	m_bIsGround(true),
	m_bPhysics(false),
	m_bIsJump(false),
	m_fFallTime(0.f),
	m_fFallStartY(0.f),
	m_fFallEndY(0.f),
	m_fJumpVelocity(0.f),
	m_fGravityAcc(10.f)
{
}

CObj::CObj(const CObj& obj)	:
	m_pPlayerBody(nullptr),
	m_pColliderBox(nullptr),
	m_pColliderSphere(nullptr)
{
	m_pScene = obj.m_pScene;

	if (obj.m_pAnimation)
	{
		m_pAnimation = obj.m_pAnimation->Clone();
		m_pAnimation->m_pOwner = this;
	}

	m_ColliderList.clear();

	std::list<CSharedPtr<CCollider>>::const_iterator	iter = obj.m_ColliderList.begin();
	std::list<CSharedPtr<CCollider>>::const_iterator	iterEnd = obj.m_ColliderList.end();

	for (; iter != iterEnd; ++iter)
	{
		CCollider* pCollider = (*iter)->Clone();

		pCollider->SetOwner(this);
		pCollider->SetScene(m_pScene);

		m_ColliderList.push_back(pCollider);
	}

	m_tPos = obj.m_tPos;
	m_tPrevPos = obj.m_tPrevPos;
	m_tSize = obj.m_tSize;
	m_tPivot = obj.m_tPivot;
	m_tVelocity = obj.m_tVelocity;
	m_tImgStart = obj.m_tImgStart;
	m_tOffset = obj.m_tOffset;
	m_fMoveSpeed = obj.m_fMoveSpeed;
	m_fTimeScale = obj.m_fTimeScale;
	m_bCameraCull = obj.m_bCameraCull;
	m_bStart = false;
	m_iZOrder = obj.m_iZOrder;
	m_pTexture = obj.m_pTexture;
	m_eObjectType = obj.m_eObjectType;
	m_bEnableDamage = obj.m_bEnableDamage;
	m_bInvisible = obj.m_bInvisible;
	m_fGravityAcc = obj.m_fGravityAcc;
	m_bPhysics = obj.m_bPhysics;
	m_bIsGround = obj.m_bIsGround;
	m_fFallTime = obj.m_fFallTime;
	m_fFallStartY = obj.m_fFallStartY;
	m_fFallEndY = obj.m_fFallEndY;
	m_bIsJump = obj.m_bIsJump;
	m_fJumpVelocity = obj.m_fJumpVelocity;

	if (obj.m_pColliderBox)
	{
		m_pColliderBox = AddCollider<CColliderBox>(obj.m_pColliderBox->GetName());
		m_pColliderBox->SetExtent(obj.m_pColliderBox->GetExtent());
		m_pColliderBox->SetOffset(obj.m_pColliderBox->GetOffset());
		m_pColliderBox->SetCollisionProfile(obj.m_pColliderBox->GetProfile()->strName);
	}

	if (obj.m_pColliderSphere)
	{
		m_pColliderSphere = AddCollider<CColliderSphere>(obj.m_pColliderSphere->GetName());
		m_pColliderSphere->SetRadius(obj.m_pColliderSphere->GetRadius());
		m_pColliderSphere->SetOffset(obj.m_pColliderSphere->GetOffset());
		m_pColliderSphere->SetCollisionProfile(obj.m_pColliderSphere->GetProfile()->strName);
	}
}

CObj::~CObj()
{
	SAFE_DELETE(m_pAnimation);

	std::list<CSharedPtr<CCollider>>::iterator	iter = m_ColliderList.begin();
	std::list<CSharedPtr<CCollider>>::iterator	iterEnd = m_ColliderList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->ClearCollisionList();
	}

	m_ColliderList.clear();
}

CCollider* CObj::FindCollider(const std::string& strName)
{
	std::list<CSharedPtr<CCollider>>::iterator iter = m_ColliderList.begin();
	std::list<CSharedPtr<CCollider>>::iterator iterEnd = m_ColliderList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == strName)
			return *iter;
	}

	return nullptr;
}

void CObj::CreateAnimation()
{
	if (!m_pAnimation)
	{
		m_pAnimation = new CAnimation;
		m_pAnimation->m_pOwner = this;
		m_pAnimation->m_pScene = m_pScene;
	}
}

void CObj::AddAnimation(const std::string& strSequenceName, bool bLoop, float fPlayTime, float fPlayScale, bool bReverse)
{
	CreateAnimation();

	m_pAnimation->AddAnimation(strSequenceName, bLoop, fPlayTime, fPlayScale, bReverse);
}

void CObj::SetAnimationPlayTime(const std::string& strName, float fPlayTime)
{
	if (!m_pAnimation)
		return;

	m_pAnimation->SetAnimationPlayTime(strName, fPlayTime);
}

void CObj::SetAnimationPlayScale(const std::string& strName, float fPlayScale)
{
	if (!m_pAnimation)
		return;

	m_pAnimation->SetAnimationPlayScale(strName, fPlayScale);
}

void CObj::SetAnimationReverse(const std::string& strName, bool bReverse)
{
	if (!m_pAnimation)
		return;

	m_pAnimation->SetAnimationReverse(strName, bReverse);
}

void CObj::SetAnimationLoop(const std::string& strName, bool bLoop)
{
	if (!m_pAnimation)
		return;

	m_pAnimation->SetAnimationLoop(strName, bLoop);
}

void CObj::SetCurrentAnimation(const std::string& strName)
{
	if (!m_pAnimation)
		return;

	m_pAnimation->SetCurrentAnimation(strName);
}

void CObj::ChangeAnimation(const std::string& strName)
{
	if (!m_pAnimation)
		return;

	m_pAnimation->ChangeAnimation(strName);
}

bool CObj::CheckCurrentAnimation(const std::string& strName)
{
	return m_pAnimation->CheckCurrentAnimation(strName);
}
