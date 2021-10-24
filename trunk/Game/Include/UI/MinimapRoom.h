#pragma once

#include "UIImage.h"

// ¹Ì´Ï¸Ê¿¡¼­ È°¼ºÈ­µÉ ¸Ê
class CMinimapRoom :
    public CUIImage
{
protected:
	EMinimapRoom_Type	m_eType;
	bool	m_bStart;

public:
	void SetRoomType(EMinimapRoom_Type eType)
	{
		m_eType = eType;
	}

public:
	EMinimapRoom_Type GetRoomType()	const
	{
		return m_eType;
	}

public:
	CMinimapRoom();
	CMinimapRoom(const CMinimapRoom& widget);
	virtual ~CMinimapRoom();

public:
	virtual bool Init();
	virtual void Update(float fTime);
};

