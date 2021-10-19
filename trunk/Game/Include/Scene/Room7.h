#pragma once

#include "RoomBase.h"

class CRoom7 :
    public CRoomBase
{
	friend class CSceneManager;

public:
	virtual bool Init();
	virtual void Start();

public:
	virtual void DoorFunc(EDoorDir eDoorDir);

protected:
	CRoom7();
	virtual ~CRoom7();
};
