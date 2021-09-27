
#include "Camera.h"

bool CCamera::Init()
{
	return true;
}

void CCamera::Update(float fTime)
{
	if (m_pTarget)
	{
		if (!m_pTarget->IsActive())
			m_pTarget = nullptr;

		else
			m_tPos = m_pTarget->GetPos() - m_tTargetPivot * m_tResolution + m_tTargetOffset;
	}

	if (m_tPos.x < 0.f)
		m_tPos.x = 0.f;

	else if (m_tPos.x + m_tResolution.x > m_tWorldResolution.x)
		m_tPos.x = m_tWorldResolution.x - m_tResolution.x;

	if (m_tPos.y < 0.f)
		m_tPos.y = 0.f;

	else if (m_tPos.y + m_tResolution.y > m_tWorldResolution.y)
		m_tPos.y = m_tWorldResolution.y - m_tResolution.y;
}

CCamera::CCamera()	:
	m_tResolution(1280.f, 720.f),
	m_tWorldResolution(1280.f, 720.f)
{
}

CCamera::~CCamera()
{
}
