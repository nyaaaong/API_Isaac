#pragma once

#include "RoomBase.h"

class CRoom4 :
    public CRoomBase
{
	friend class CSceneManager;


public:
	virtual bool Init();
	virtual void Start();
	virtual bool Update(float fTime);
	virtual bool PostUpdate(float fTime);
	virtual bool Collision(float fTime);
	virtual bool Render(HDC hDC);

protected:
	CRoom4();
	virtual ~CRoom4();
};

