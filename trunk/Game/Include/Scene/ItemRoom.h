#pragma once

#include "RoomBase.h"

class CItemRoom :
    public CRoomBase
{
	friend class CSceneManager;

protected:
	CItemRoom();
	virtual ~CItemRoom();

public:
	virtual bool Init();
	virtual void Start();

public:
	virtual void DoorFunc(EDoorDir eDoorDir);
};

