#include <iostream>
#include <time.h>
#include <Windows.h>

using namespace std;

void ShowCard(int shape, int number)
{
	switch (shape)
	{
	case 0:
		cout << "♠";
		break;
	case 1:
		cout << "♣";
		break;
	case 2:
		cout << "◆";
		break;
	case 3:
		cout << "♥";
		break;
	}
	//tab -> space bar * 8번 
	//숫자 셋팅(\t tap을 누른 만큼 이동) 
	switch (number)
	{
	case 0:
		cout << "A \t";
		break;
	case 10:
		cout << "J \t";
		break;
	case 11:
		cout << "Q \t";
		break;
	case 12:
		cout << "K \t";
		break;
	default:
		cout << number + 1 << " \t";
		break;
	}
}

void main()
{
	srand(time(NULL));

	int card[52];		//카도 총 52장
	int shape[3];		//화면에 보여줄 카드 3장의 모양
	int number[3];		//화면에 보여줄 카드 3장의 숫자

	int dest, sour, temp; // 셔플용 변수

	int betting;		//배팅용 변수(입력용)
	int money = 10000;  //소지금
	int turn = 0;		//사용한 카드를 버리는 변수, 나중에 3씩추가
	int gameCount = 0;  //게임 카운트

	//카드 초기화
	for (int i = 0; i < 52; i++)
	{
		card[i] = i;				//0~51;
	}
	//셔플
	for (int i = 0; i < 999; i++)
	{
		dest = rand() % 52;
		sour = rand() % 52;

		temp = card[dest];
		card[dest] = card[sour];
		card[sour] = temp;
	}
	//게임 만들기
	while (true)
	{
		for (int i = 0; i < 3; i++)
		{
			shape[i] = card[i + turn] / 13; //문양 
			number[i] = card[i + turn] % 13; //숫자 

			if (i == 2) cout << "치트 : ";
			//모양 셋팅
			ShowCard(shape[i], number[i]);
			//0  + 0, 1 + 0 , 2 + 0 -> 0 ,1 ,2
			//0  + 3, 1 + 3 , 2 + 3 -> 3 ,4 ,5
		}
		cout << endl;

		//총 금액을 보여주고 배팅금액 입력 받기
		cout << "소지금 : " << money << endl;
		cout << "배팅하자 : ";
		cin >> betting;

		//내 보유 금액이 1000 미만이라면 종료 
		if (money < 1000)
		{
			cout << "파산!!!! 인생끝!!!!" << endl;
			Sleep(1000);   //1초간 딜레이를 줌
			break;
		}
		
		//배팅 금액이 1000미만 또는 소지금 보다 많을 경우 다시 배팅
		if (1000 > betting || betting > money)
		{
			cout << "다시 배팅해라!!" << endl;
			Sleep(1000);
			continue;
		}

		//검사 
		//C번째 카드 -> A B사이
		//A < C < B , B < C < A

		if (number[0] < number[1])
		{
			int temp = number[0];
			number[0] = number[1];
			number[1] = temp;
		}
		//if(number[1] < number[2] && number[2] < number[0] ||
		//number[0] < number[2] && number[2] < number[1] )
		if (number[1] < number[2] && number[2] < number[0])
		{
			cout << "카드 숫자 : ";
			ShowCard(shape[2], number[2]);
			cout << endl;
			money += betting;
			cout << betting << "돈 획득" << endl;
			Sleep(1000);
		}
		else
		{
			cout << "카드 숫자 : ";
			ShowCard(shape[2], number[2]);
			cout << endl;
			money -= betting;
			cout << betting << "돈 읽음 " << endl;
			Sleep(1000);
		}
		system("cls");
		turn += 3;//사용한 카드 버리기
		gameCount++; //게임 카운트 증가
		if (gameCount == 17)
		{
			cout << "더 이상 카드가 없다 " << endl;
			Sleep(1000);
			break;
		}
	}
}