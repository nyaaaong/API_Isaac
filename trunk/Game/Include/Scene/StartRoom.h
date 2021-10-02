#pragma once

#include "RoomBase.h"

class CStartRoom :
    public CRoomBase
{
	friend class CSceneManager;

public:
	virtual bool Init();
	virtual bool Update(float fTime);
	virtual bool PostUpdate(float fTime);
	virtual bool Collision(float fTime);
	virtual bool Render(HDC hDC);

protected:
	CStartRoom();
	virtual ~CStartRoom();
};

