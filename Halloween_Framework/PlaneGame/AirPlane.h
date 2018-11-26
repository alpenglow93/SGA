#pragma once
//�÷��̾� 
//�̹��� + �浹ü + �̵�
#include "./Render/Sprite.h" //�̹���
#include "./Object/Rect.h" //�浹�� 
#include "Bullet.h"
#include "./Animation/Clip.h"
//���漱�� 
//class BaseEnemy;
#define BULLETMAX 10
//�Ѿ�(bullet)
class AirPlane
{
private:
	Bullet * bullet[BULLETMAX];
	Bomb* bomb;
	Clip* explosion;
protected:
	Sprite * sprite;
	Rect* rect;

	D3DXVECTOR2 position; //�� ��ġ
	D3DXVECTOR2 direction; //�̵��� ����
	float speed; //�̵��ӵ� 
	
	float angle; //ȸ�� (�̹��� + ����)

	float hp;
	class PrograssBar* hpBar;
	class PlaneEnemyManager* enemys; //���� ���� + ���� ���� 
public:
	AirPlane(wstring file);
	virtual ~AirPlane();

	void Update();
	void Render();

	virtual void Move();
	virtual void Attack();

	void Position(float x, float y);
	void Position(D3DXVECTOR2* position);
	void SetLink(class PlaneEnemyManager* link) { enemys = link; }

	Rect* GetRect() { return rect; }
	float GetHp() { return hp; }
	void SetHp(float _hp) { hp = _hp; }

	Sprite* GetSprite() { return sprite; }
};

class AirPlane2 : public AirPlane
{
public:
	AirPlane2(wstring file);


	virtual void Move() override;



};

