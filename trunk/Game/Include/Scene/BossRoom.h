#pragma once

#include "RoomBase.h"

class CBossRoom :
    public CRoomBase
{
	friend class CSceneManager;

private:
	void Next(float fTime);

public:
	virtual bool Init();
	virtual void Start();
	virtual bool Update(float fTime);
	virtual bool PostUpdate(float fTime);
	virtual bool Collision(float fTime);
	virtual bool Render(HDC hDC);

protected:
	virtual void CreateMonster();

protected:
	CBossRoom();
	virtual ~CBossRoom();
};

