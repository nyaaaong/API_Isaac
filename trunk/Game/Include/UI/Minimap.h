#pragma once

#include "UIImage.h"

class CMinimap :
    public CUIImage
{
public:
	CMinimap();
	CMinimap(const CMinimap& widget);
	virtual ~CMinimap();

public:
	virtual bool Init();
};

