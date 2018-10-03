#pragma once
#include <iostream>
using namespace std;

//Ŭ������ ���� ����
//1. C ��� -> C++ ��ȭ
//2. �������� -> ��ü ����(Ư�� ��ü�� �����ϸ� ��)
//3. �������� ����� (�ð��� ���� �ɸ���)
//��ü ���� �ڵ� _�⺻���� Ŭ���� ����

//.h(��� ����) -> ��κ��� �������� �ۼ�

//ex) player class -> hp, mp, att, def, Attack, Move
//hp, mp, att, def -> private
//attack, move -> public

class MainGame
{
	//���� ������: ���� �ܰ踦 �����ϴ� Ű����
private:	//�� Ŭ���� ���ο����� ��� ����
	//��� ����: Ŭ���� ���ο� �ִ� ������
	int data;
	float distance;

	int *pInt;
protected:	//Ŭ���� ��� ���迡�� �� Ŭ������ �ڽı����� ����� �� �ִ� ������
	bool bCheck;

public:		//������ �׳� ������ �� �� �ִ� ������
	int nInt;

	int hp;
	int att;
	MainGame();		//������: ��ü�� �����ɶ� ����Ǵ� �Լ�
	~MainGame();	//�Ҹ���: ��ü�� �Ҹ�ɶ� ����Ǵ� �Լ�

	void SetDistance(float f);
	float GetDistance();

	void SetDamage(MainGame* target);
};

