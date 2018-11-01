#pragma once
#include "./PlaneGameEnemy.h"
class PlaneEnemyManager
{
private:
	vector<BaseEnemy*> enemys;	//보유한 에너미 전체
	vector<BaseEnemy*> cullingEnemys;	//화면안에 있는 에너미
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

