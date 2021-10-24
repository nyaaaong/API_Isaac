#pragma once

#include "UIImage.h"

// �̴ϸʿ��� Ȱ��ȭ�� ��
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

