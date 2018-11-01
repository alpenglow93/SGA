#pragma once
#include "./PlaneGameEnemy.h"
class PlaneEnemyManager
{
private:
	vector<BaseEnemy*> enemys;	//������ ���ʹ� ��ü
	vector<BaseEnemy*> cullingEnemys;	//ȭ��ȿ� �ִ� ���ʹ�
	Bullet* bullet[BULLETMAX];

	AirPlane* player;
	class Space* background;
public:
	PlaneEnemyManager();
	~PlaneEnemyManager();

	void Update();
	void Render();

	void SetEnemys(class AirPlane* link);
	void SetBackground(class Space* link) { background = link; }

	vector<BaseEnemy*> GetEnemys() { return cullingEnemys; }
	vector<BaseEnemy*> GetAllEnemys() { return enemys; }
	Bullet** GetBullet() { return bullet; }
};

