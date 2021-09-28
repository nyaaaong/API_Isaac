#pragma once

#include "Map.h"

class CObjTileMap :
	public CMap
{
	friend class CScene;

protected:
	CObjTileMap();
	virtual ~CObjTileMap();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void PrevRender();
	virtual void Render(HDC hDC);
};

