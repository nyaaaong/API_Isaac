#pragma once

#include "RoomBase.h"

class CRoom4 :
    public CRoomBase
{
	friend class CSceneManager;

public:
	virtual bool Init();
	virtual void Start();

public:
	virtual void DoorFunc(EDoorDir eDoorDir);

protected:
	CRoom4();
	virtual ~CRoom4();
};
