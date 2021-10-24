
#include "Minimap.h"

CMinimap::CMinimap()
{
}

CMinimap::CMinimap(const CMinimap& widget)	:
	CUIImage(widget)
{
}

CMinimap::~CMinimap()
{
}

bool CMinimap::Init()
{
	if (!CUIImage::Init())
		return false;

	SetTexture("Minimap", TEXT("UI/Minimap/Minimap.bmp"));
	SetTextureColorKey();

	SetZOrder(EZOrder::UI);

	return true;
}
