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
	bool	m_bUsePattern;		// 패턴을 사용할지
	bool	m_bDelayCheck;		// 패턴 딜레이 체크를 시작할지
	float	m_fAccTime;			// 패턴 딜레이 체크를 위한 누적 시간
	float	m_fPatternDelay;	// 패턴이 끝난 후 다음 패턴까지의 딜레이

private:
	void ShufflePattern();	// 패턴이 1개 이상인 경우 무작위로 섞는다.

protected:
	void GetM2PDir();	// Monster To Player : 몬스터 기준 플레이어의 방향을 구해준다

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

