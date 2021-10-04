
#include "Scene.h"

int CScene::SortY(const void* pSrc, const void* pDest)
{
	CObj* pSrcObj = *(CObj**)pSrc;
	CObj* pDestObj = *(CObj**)pDest;

	float	fSrcY = pSrcObj->GetBottom();
	float	fDestY = pDestObj->GetBottom();

	if (fSrcY < fDestY)
		return -1;

	else if (fSrcY > fDestY)
		return 1;

	return 0;
}

int CScene::SortUIZOrder(const void* pSrc, const void* pDest)
{
	CUIWindow* pSrcObj = *(CUIWindow**)pSrc;
	CUIWindow* pDestObj = *(CUIWindow**)pDest;

	int iSrcZ = pSrcObj->GetZOrder();
	int iDestZ = pDestObj->GetZOrder();

	if (iSrcZ > iDestZ)
		return -1;

	else if (iSrcZ < iDestZ)
		return 1;

	return 0;
}

int CScene::SortObjZOrder(const void* pSrc, const void* pDest)
{
	CObj* pSrcObj = *(CObj**)pSrc;
	CObj* pDestObj = *(CObj**)pDest;

	int iSrcZ = pSrcObj->GetZOrder();
	int iDestZ = pDestObj->GetZOrder();

	if (iSrcZ > iDestZ)
		return -1;

	else if (iSrcZ < iDestZ)
		return 1;

	return 0;
}