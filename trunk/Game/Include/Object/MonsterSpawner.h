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
	std::vector<std::string>	m_vecBossName;
	std::vector<Vector2>		m_vecSpawnStartPos;
	std::vector<Vector2>		m_vecSpawnEndPos;
	Vector2						m_tSpawnPos;
	class CScene*				m_pScene;

public:
	void SetScene(class CScene* pCurScene);
	void CreateMonsterPrototype();
	void CreateBossMonsterPrototype();
	void CreateMonster();
	void CreateBossMonster();
	void EnemyDieNormal(const Vector2& tPos);
	void EnemyDieFly(const Vector2& tPos);
	void AddSpawnLocation();
	void AddBossSpawnLocation();
	
private:
	void CreateSpawnLocation(const Vector2& tSize, const Vector2& tPivot, const Vector2& tOffset); // �����ߴ� ���� ��ġ�� ���� �������� ���͸� ������ ��ǥ�� ���Ѵ�.
	void CreateMonster(const std::string& strName);
	void CreateBossMonster(const std::string& strName);
	bool CheckSpawnPossible(const Vector2& tSize, const Vector2& tPivot, const Vector2& tOffset);
};

