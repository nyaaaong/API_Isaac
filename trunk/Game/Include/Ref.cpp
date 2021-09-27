#include "Ref.h"

CRef::CRef()	:
	m_bActive(true),
	m_iRefCount(0)
{
}

CRef::CRef(const CRef& ref)	:
	m_bActive(true),
	m_iRefCount(0),
	m_strName(ref.m_strName)
{
}

CRef::~CRef()
{
}
