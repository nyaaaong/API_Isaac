#pragma once

#include "Obj.h"

class CBackGround :
	public CObj
{
	friend class CScene;

public:
	virtual bool Init();
	virtual void Render(HDC hDC);
	virtual CBackGround* Clone();

protected:
	CBackGround();
	CBackGround(const CBackGround& obj);
	virtual ~CBackGround();
};

