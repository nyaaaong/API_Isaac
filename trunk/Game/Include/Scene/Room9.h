#pragma once

#include "RoomBase.h"

class CRoom9 :
    public CRoomBase
{
	friend class CSceneManager;

public:
	virtual bool Init();
	virtual void Start();

public:
	virtual void DoorFunc(EDoorDir eDoorDir);

protected:
	CRoom9();
	virtual ~CRoom9();
};

