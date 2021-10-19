#pragma once

#include "RoomBase.h"

class CRoom1 :
    public CRoomBase
{
	friend class CSceneManager;

public:
	virtual bool Init();
	virtual void Start();

public:
	virtual void DoorFunc(EDoorDir eDoorDir);

protected:
	CRoom1();
	virtual ~CRoom1();
};

