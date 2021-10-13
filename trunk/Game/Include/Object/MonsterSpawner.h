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
	void SetMonsterSpawnLocation(const Vector2& tLocation); // �÷��̾� ��ġ�� �ݴ������ ���ڷ� �־��༭ ���� ��ġ�� �����Ѵ�.
	void EnemyDie1(const Vector2& tPos);
	
private:
	void CreateSpawnLocation(const Vector2& tSize, const Vector2& tPivot, const Vector2& tOffset); // �����ߴ� ���� ��ġ�� ���� �������� ���͸� ������ ��ǥ�� ���Ѵ�.
	void CreateMonster(const std::string& strName);
};

