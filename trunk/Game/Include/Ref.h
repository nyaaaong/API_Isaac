#pragma once

#include "GameInfo.h"

class CRef
{
protected:
	std::string m_strName;
	bool	m_bActive;
	int		m_iRefCount;

public:
	void AddRef()
	{
		++m_iRefCount;
	}

	int GetRefCount()	const
	{
		return m_iRefCount;
	}

	int Release()
	{
		--m_iRefCount;

		if (m_iRefCount <= 0)
		{
			delete	this;
			return 0;
		}

		return m_iRefCount;
	}

	void Destroy()
	{
		m_bActive = false;
	}

	bool IsActive()	const
	{
		return m_bActive;
	}

	std::string GetName()	const
	{
		return m_strName;
	}

	void SetName(const std::string& strName)
	{
		m_strName = strName;
	}

public:
	CRef();
	CRef(const CRef& ref);
	virtual ~CRef();
};

