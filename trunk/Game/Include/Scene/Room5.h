#pragma once

#include "RoomBase.h"

class CRoom5 :
    public CRoomBase
{
	friend class CSceneManager;

public:
	virtual bool Init();
	virtual void Start();

public:
	virtual void DoorFunc(EDoorDir eDoorDir);

protected:
	CRoom5();
	virtual ~CRoom5();
};

