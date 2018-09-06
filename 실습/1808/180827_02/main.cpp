#include <iostream>
using namespace std;

//숙제풀이
//2. 구구단 출력
void main()
{
	for (int k = 1; k < 10; k += 3)
	{
		for (int j = 1; j < 10; j++)
		{
			for (int i = k; i < k + 3; i++)
			{
				//\t: 한 탭을 옮기는 명령어
				cout << i << " x " << j << " = " << i * j << "\t";
			}
			cout << endl;
		}
		cout << endl;
	}
}