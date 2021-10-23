#pragma once

#include "RoomBase.h"

class CStartRoom :
    public CRoomBase
{
	friend class CSceneManager;

public:
	virtual bool Init();
	virtual void Start();

public:
	virtual void DoorFunc(EDoorDir eDoorDir);

protected:
	CStartRoom();
	virtual ~CStartRoom();
};

