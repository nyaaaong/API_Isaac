
#include "ItemGlasses.h"
#include "Player.h"
#include "../Collision/ColliderBox.h"

CItemGlasses::CItemGlasses()
{
}

CItemGlasses::CItemGlasses(const CItemGlasses& obj)	:
	CItem(obj)
{
}

CItemGlasses::~CItemGlasses()
{
}

bool CItemGlasses::Init()
{
	if (!CItem::Init())
		return false;

	SetTexture("ItemGlasses", TEXT("Item/Item_Glasses.bmp"));
	SetTextureColorKey();

	return true;
}

void CItemGlasses::Start()
{
	CItem::Start();

	SetTexture("ItemGlasses");
}
