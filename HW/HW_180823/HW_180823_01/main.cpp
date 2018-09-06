#include <iostream>
#include <time.h>
#include <string>
using namespace std;

void main()
{
	//가위바위보 게임 제작

	//컴퓨터와 플레이어의 가위바위보 데이터를 저장할 변수
	int nCNum;
	string sCNum;
	int nPNum;
	string sPNum;
	//승패 전적 카운트 변수
	int win = 0;
	int lose = 0;
	int same = 0;

	srand(time(NULL));

	//게임을 총 다섯판 진행할 것이다
	cout << "가위바위보 게임은 총 다섯판 진행됩니다" << endl;

	for (int i = 0; i < 5; i++)
	{

		//컴퓨터가 낼 가위바위보
		nCNum = rand() % 3;

		//플레이어가 가위바위보 입력
		cout << i + 1 << "번째 게임" << endl;
		cout << "가위(0), 바위(1), 보(2) 에 해당하는 숫자를 입력하고 엔터를 치시오." << endl;
		cin >> nPNum;

		//예외처리 겸 문자열 저장
		//switch(nPNum)
		//{
		//case 0:
		//	sPNum = "가위";
		//	break;
		//case 1:
		//	sPNum = "바위";
		//	break;
		//case 2:
		//	sPNum = "보";
		//	break;
		//default:
		//	cout << "가위(0), 바위(1), 보(2) 에 해당하는 바른 숫자를 입력하시오." << endl;
		//	i--;		//가위바위보 한 횟수로 치지 않기 위한 증감식
		//	break;
		//}

		if (nPNum == 0 || nPNum == 1 || nPNum == 2)
		{
			switch (nPNum)
			{
			case 0:
				sPNum = "가위";
				break;
			case 1:
				sPNum = "바위";
				break;
			case 2:
				sPNum = "보";
				break;
				//default:
				//	cout << "가위(0), 바위(1), 보(2) 에 해당하는 바른 숫자를 입력하시오." << endl;
				//	i--;		//가위바위보 한 횟수로 치지 않기 위한 증감식
				//	break;
			}


			switch (nCNum)
			{
			case 0:
				sCNum = "가위";
				break;
			case 1:
				sCNum = "바위";
				break;
			case 2:
				sCNum = "보";
				break;
			}

			cout << "컴퓨터가 낸 것: " << sCNum << endl;
			cout << "플레이어가 낸 것: " << sPNum << endl;

			//결과 비교
			if (nCNum == nPNum)
			{
				cout << "비겼습니다" << endl << endl;
				same++;
			}
			else if (nCNum == 0)	//컴퓨터가 가위
			{
				if (nPNum == 1)	//플레이어가 바위
				{
					cout << "졌습니다" << endl << endl;
					lose++;
				}
				else	//nPNum ==2 //플레이어가 보
				{
					cout << "이겼습니다" << endl << endl;
					win++;
				}
			}
			else if (nCNum == 1)	//컴퓨터가 바위
			{
				if (nPNum == 0)	//플레이어가 가위
				{
					cout << "졌습니다" << endl << endl;
					lose++;
				}
				else	//nPNum == 2 //플레이어가 보
				{
					cout << "이겼습니다" << endl << endl;
					win++;
				}
			}
			else	//nCNum == 2	//컴퓨터가 보
			{
				if (nPNum == 0)	//플레이어가 가위
				{
					cout << "이겼습니다" << endl << endl;
					win++;
				}
				else	//nPNum == 1	//플레이어가 바위
				{
					cout << "졌습니다" << endl << endl;
					lose++;
				}
			}
		}
		else
		{
			cout << "가위(0), 바위(1), 보(2) 에 해당하는 바른 숫자를 입력하시오." << endl;
			i--;		//가위바위보 한 횟수로 치지 않기 위한 증감식
		}

		//0 1 2 가 아닌 숫자를 입력할 경우 아랫쪽의 작업은 실행하면 안됨



		//테스트출력
		//cout << nCNum << endl;

	}

	cout << "이긴 횟수: " << win << endl;
	cout << "진 횟수: " << lose << endl;
	cout << "비긴 횟수: " << same << endl;

}