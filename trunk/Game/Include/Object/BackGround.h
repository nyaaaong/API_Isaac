#pragma once

#include "Obj.h"

class CBackGround :
	public CObj
{
	friend class CScene;

private:
	bool	m_bStartRoom;

public:
	bool IsStartRoom()	const
	{
		return m_bStartRoom;
	}

public:
	void StartRoom()
	{
		m_bStartRoom = true;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Render(HDC hDC);
	virtual CBackGround* Clone();

protected:
	CBackGround();
	CBackGround(const CBackGround& obj);
	virtual ~CBackGround();
};

