#pragma once
#include "./Render/Sprite.h"
#include "./Object/Rect.h"
#include "./Bullet.h"
#include "./AirPlane.h"
#include "./Utilities/Intersect.h"
#include "./Object/PrograssBar.h"
//에너미 이미지 + 충돌 + 총알 + 플레이어 
//AI ->가만히 -> 이동 -> 발사 -> 죽는다. 

//상태
enum class STATE
{
	Idle = 0, Move, Attack, Death
};
class BaseEnemy //기본 에너미 
{
protected:
	Sprite * sprite;
	Rect* rect;

	STATE state;

	D3DXVECTOR2 position;
	D3DXVECTOR2 rectPosition;

	D3DXVECTOR2 direction;
	float speed;
	float angle;

	float hp;
	PrograssBar* hpBar;

	UINT prevTime;  //딜레이용 
	UINT currTime;
	UINT delayTime;

	AirPlane* plane;
	float playerToDistance;  //플레이어와 거리

	bool bFire;
private:

	virtual void Idle(); //idle 상태 일때 
	virtual void Move(); //move 상태 일때 
	virtual void Attack(); //attack 상태 일때 
	virtual void Death();

public:
	BaseEnemy(AirPlane* link);
	virtual ~BaseEnemy();

	void Update();
	void Render();

	Rect* GetRect() { return rect; }
	STATE GetState() { return state; }

	float GetHP() { return hp; }
	void SetHP(float _hp) { hp = _hp; if (hp < 0.0f) { state = STATE::Death; prevTime = GetTickCount(); } }

	void Position(D3DXVECTOR2 vec);
	void Position(float x, float y);

	bool GetFire() { return bFire; }
	void SetFire(bool _bFire);

	D3DXVECTOR2 GetDirection() { return direction; }
	D3DXVECTOR2 GetPosition() { return position; }
	float GetAngle() { return angle; }
};


///////////////////////////////////////////////////////////////////////
//이미지 같은 이미지 + 크기를 키운다.
//AI 
//idle -> 처음 리스폰 장소 ,일정 시간 지날시 체력 회복
//Run -> 일정 사거리 안이면 이동(회전 x)
//Attack -> 처음 (나중에 패턴 )
//Death -> 일정 몬스터 수 계산 

typedef void(*FP)();
class BossEnemy : public BaseEnemy
{
private:

private:	
	D3DXVECTOR2 respwanPoint;
	static int deathCount;

	vector<FP> vPatten;
public:
	BossEnemy(AirPlane* link);
	~BossEnemy();

	virtual void Idle() override;
	virtual void Move() override;
	virtual void Attack() override;
	virtual void Death() override;

	static int GetDeathCount() { return deathCount; }
	static void SetDeathCount(int count) { deathCount = count; }

	void Push(FP& temp) { vPatten.push_back(temp); }

public:
	void Patten1();
};
