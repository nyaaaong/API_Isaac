#pragma once

#include "../GameInfo.h"
#include "../Resource/Texture.h"

class CMapObj
{
	friend class CMap;

private:
	CMapObj();
	~CMapObj();

private:
	Vector2	m_tPos;
	Vector2	m_tSize;
	CSharedPtr<CTexture>	m_pTexture;
	EObject	m_eObject;

public:
	bool Init();
	void Update(float fTime);
	void PostUpdate(float fTime);
	void PrevUpdate(float fTime);
	void Render(HDC hDC);

public:
	void SetObject(EObject eObject);
};

