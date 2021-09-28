#pragma once

#include "Character.h"

class CMonsterBase :
	public CCharacter
{
	friend class CScene;

protected:
	Vector2	m_tDir;
	Vector2	m_tM2PDir;
	float	m_fFireTime;
	float	m_fFireTimeMax;
	int		m_iCount;
	std::vector<std::function<void(float)>>	m_vecPattern;
	bool	m_bUsePattern;		// ������ �������
	bool	m_bDelayCheck;		// ���� ������ üũ�� ��������
	float	m_fAccTime;			// ���� ������ üũ�� ���� ���� �ð�
	float	m_fPatternDelay;	// ������ ���� �� ���� ���ϱ����� ������

private:
	void ShufflePattern();	// ������ 1�� �̻��� ��� �������� ���´�.

protected:
	void GetM2PDir();	// Monster To Player : ���� ���� �÷��̾��� ������ �����ش�

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC);
	virtual CMonsterBase* Clone();

protected:
	CMonsterBase();
	CMonsterBase(const CMonsterBase& obj);
	virtual ~CMonsterBase();

protected:
	template<typename T>
	bool AddMonsterPattern(T* pObj, void(T::* pFunc)(float))
	{
		m_bUsePattern = true;

		m_vecPattern.push_back(std::bind(pFunc, pObj, std::placeholders::_1));

		ShufflePattern();

		return true;
	}
};

