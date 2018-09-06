#include <iostream>
using namespace std;

void main()
{
	//조건문: 특정조건을 만족하거나 불만족시 다른 코드를 실행하겠다.

	//if, switch

	//if( 조건 ) 조건 -> 참일경우 
	//{
	//	조건이 참일경우 {} 사이의 코드를 실행
	//}
	//else
	//{
	//	조건이 거짓일때 {} 사이의 코드를 실행
	//}

	int nNum1 = 10;
	int nNum2 = 10;

	if (nNum1 > nNum2)
	{
		cout << nNum1 << "은 " << nNum2 << "보다 큽니다." << endl;
		//c++언어 방식의 출력방법
	}
	else if (nNum1 == nNum2)
	{
		cout << nNum1 << "와 " << nNum2 << "은 값이 같습니다." << endl;
	}
	else if (nNum1 < 0)
	{
		cout << nNum1 << "은 0보다 작습니다." << endl;
	}
	else
	{
		printf("%d는 %d보다 작습니다. \n", nNum1, nNum2);
		//c언어 방식의 출력방법
	}

	//switch( 변수 )
	//{
	//	case 변수가 가질 수 있는 값:
	//	break;
	//	case 변수가 가질 수 있는 값:
	//	break;
	//	case 변수가 가질 수 있는 값:
	//	break;
	//	case 변수가 가질 수 있는 값:
	//	break;
	//}

	char ch;
	
	ch = 'd';

	//cout << "문자 입력" << endl;
	//cin >> ch;

	//break -> {} 를 빠져나가는 명령어
	//반복문(for, while), switch;

	switch (ch)
	{
	case 'a':
		cout << "왼쪽으로 이동" << endl;
		break;
	case 'd':
		cout << "오른쪽으로 이동" << endl;
		break;
	case 'w':
		cout << "윗쪽으로 이동" << endl;
		break;
	case 's':
		cout << "아래쪽으로 이동" << endl;
		break;
	default:	//명시된 케이스 외의 나머지 녀석이 변수에 대입됐을때
		cout << "잘못 입력하였습니다" << endl;
		break;
	}

	int nNum3 = 4;
	switch(nNum3)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
		cout << "출력" << endl;
		break;
	default:
		break;
	}
	//같은
	if (0 <= nNum3 && nNum3 < 4)
	{
		cout << "출력" << endl;
	}
	//의미

	if (0 <= nNum3)
	{
		if (nNum3 < 4)
		{
			cout << "출력" << endl;
		}
	}

	//1.
	cout << "=================" << endl;
	int nSumNum = 5;

	nSumNum = nSumNum + 1;

	cout << nSumNum << endl;

	//
	nSumNum += 1;
	cout << nSumNum << endl;

	nSumNum *= 2;
	cout << nSumNum << endl;

	bool bCheck = true;
	bCheck &= false;
	bCheck |= true;

	//+1 -1
	nSumNum++;
	cout << nSumNum << endl;	//15
	
	//++nSumNum과 nSumNum++ 의 차이
	cout << ++nSumNum << endl;
	//1 증가 후 화면에 출력

	cout << nSumNum++ << endl;
	//출력 후 1 증가
	cout << nSumNum << endl;
}