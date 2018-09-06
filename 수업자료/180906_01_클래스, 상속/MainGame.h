#pragma once
#include <iostream>
using namespace std;
//Ŭ������ ���� ����
//1. C��� -> C++ ��ȭ 
//2. ���� ���� -> ��ü ����(Ư�� ��ü)
//3. ���� ���� ����� (�ð� ���� �ɸ���)
//4. ���α׷� �ΰǺ� 1�ð� 3�ð� 
//��ü ���� �ڵ� _ �⺻���� Ŭ���� ���� 

//.h(��� ����) -> ��κ��� �������� �ۼ� 
//ex) player class -> hp, mp, att, def , Attack, Move
//hp, mp, att, def -> private;
//attack, move -> public
class MainGame
{
	//���� ������  : ���� �ܰ踦 ���� �ϴ� �༮ 
private: //�� Ŭ���� ���ο����� ��� �����Ѱ� ����
	//�ɹ� ���� : Ŭ���� ���ο� �ִ� ������ 
	int data;
	float distance;

	int* pInt;
protected: //Ŭ���� ��� ���迡�� �� Ŭ������ �ڽı����� 
		   //����Ҽ� �ִ� ������ 
	bool bCheck;
public: //������ �׳� ������ ���
	int nInt;

	int hp;
	int att;

public: //��
	MainGame();   //������ : Ŭ������ �����ɶ� ����Ǵ� �Լ�
	~MainGame(); //�Ҹ��� : Ŭ������ �Ҹ�ɶ� ����Ǵ� �Լ�

	void SetDistance(float f);
	float GetDistance();

	void SetDamage(MainGame* target);
};

