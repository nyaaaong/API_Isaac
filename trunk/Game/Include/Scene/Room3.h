#pragma once

#include "RoomBase.h"

class CRoom3 :
    public CRoomBase
{
	friend class CSceneManager;

public:
	virtual bool Init();
	virtual void Start();

public:
	virtual void DoorFunc(EDoorDir eDoorDir);

protected:
	CRoom3();
	virtual ~CRoom3();
};

