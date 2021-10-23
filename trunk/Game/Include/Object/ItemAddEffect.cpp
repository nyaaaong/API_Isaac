
#include "ItemAddEffect.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

CItemAddEffect::CItemAddEffect()
{
}

CItemAddEffect::CItemAddEffect(const CItemAddEffect& obj)	:
	CObj(obj)
{
}

CItemAddEffect::~CItemAddEffect()
{
}

bool CItemAddEffect::Init()
{
	if (!CObj::Init())
		return false;

	SetZOrder(EZOrder::Effect);

	SetPivot(0.5f, 0.5f);

	AddAnimation("ItemAddEffect", true, 0.3f);

	return true;
}
CItemAddEffect* CItemAddEffect::Clone()
{
	return new CItemAddEffect(*this);
}