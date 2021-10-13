#pragma once

#include "../GameInfo.h"

class CMonsterSpawner
{
private:
	CMonsterSpawner();
	~CMonsterSpawner();

private:
	static CMonsterSpawner* m_pInst;

public:
	static CMonsterSpawner* GetInst()
	{
		if (!m_pInst)
			m_pInst = new CMonsterSpawner;

		return m_pInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
	}

public:
	bool Init();

private:
	std::vector<std::string>	m_vecName;
	std::vector<Vector2>		m_vecSize;
	std::vector<Vector2>		m_vecPivot;
	std::vector<Vector2>		m_vecOffset;
	Vector2		m_tSpawnLocationLT;
	Vector2		m_tSpawnLocationRB;
	Vector2		m_tSpawnLocation;
	class CScene* m_pScene;

public:
	void SetScene(class CScene* pCurScene);
	void CreateMonsterPrototype();
	void CreateMonster();
	void SetMonsterSpawnLocation(const Vector2& tLocation); // 플레이어 위치의 반대방향을 인자로 넣어줘서 스폰 위치를 지정한다.
	void EnemyDie1(const Vector2& tPos);
	
private:
	void CreateSpawnLocation(const Vector2& tSize, const Vector2& tPivot, const Vector2& tOffset); // 지정했던 스폰 위치를 통해 랜덤으로 몬스터를 생성할 좌표를 구한다.
	void CreateMonster(const std::string& strName);
};

