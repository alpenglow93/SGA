#include <iostream>

using namespace std;

void main()
{
	//조건문 : 특정 조건을 만족하거나 불만족시 다른 코드를 실행하겠다.

	//if, switch

	//if( 조건 ) 
	//{
	//	조건일 참일경우 {} 사이의 코드를 실행 
	//}
	//else
	//{
	//	조건이 거짓일때 {} 사이의 코드를 실행
	//}

	int nNum1 = 10;
	int nNum2 = 10;

	if (nNum1 > nNum2)
	{
		cout << nNum1 << "은 " << nNum2 << "보다 큽니다." <<endl;
	}
	else if (nNum1 == nNum2)
	{
		printf("%d는 %d보다 같습니다. \n", nNum1, nNum2);
	}
	else if (nNum1 < 0)
	{

	}
	else
	{
		printf("%d는 %d보다 작습니다. \n", nNum1, nNum2);
	}

	//switch( 변수 )
	//{
	//	case 변수가 가질수 있는 값:
	//	break;
	//	case 변수가 가질수 있는 값:
	//	break;
	//	case 변수가 가질수 있는 값:
	//	break;
	//	case 변수가 가질수 있는 값:
	//	break;
	//}
	char ch = 'd';
	//break -> {} 를 빠져 나가는 녀석
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
	default:   //나머지 녀석이 변수에 대입됬을때 
		cout << "값을 잘못 넣었습니다." << endl;
		break;
	}
	//->

	int nNum3 = 7;
	switch (nNum3)
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
	if (0 <= nNum3 && nNum3 < 4 && true)
	{
		cout << "출력" << endl;
	}
	if (0 <= nNum3)
	{
		if (nNum3 < 4)
		{
			cout << "출력" << endl;
		}
	}
	//1. 
	cout << "====================" << endl;
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

	//+1 -1;
	++nSumNum;
	cout << nSumNum << endl; //15

	//1증가후 화면에 출력
	cout << ++nSumNum << endl;
	//화면에 출력후 1증가 
	cout << nSumNum++ << endl;
	cout << nSumNum << endl;

}