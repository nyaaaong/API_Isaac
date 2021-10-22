#pragma once

#include "RoomBase.h"

class CBossRoom :
    public CRoomBase
{
	friend class CSceneManager;

public:
	virtual bool Init();
	virtual void Start();
	virtual bool Update(float fTime);

protected:
	virtual void DoorFunc(EDoorDir eDoorDir);

protected:
	CBossRoom();
	virtual ~CBossRoom();
};

