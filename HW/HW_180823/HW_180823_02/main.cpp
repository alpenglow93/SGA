#include <iostream>
using namespace std;

void main()
{
	//구구단 출력하기
	//1 x 1 = 1		2 x 1 = 2		3 x 1 = 3
	int i, j;

	for (i = 1; i < 9; i += 3)
	{
		for (j = 1; j < 10; j++)
		{
			cout << i << " x " << j << " = " << i * j << "	" <<
				i + 1 << " x " << j << " = " << (i + 1) * j << "	" <<
				i + 2 << " x " << j << " = " << (i + 2) * j << "	" << endl;
		}

		cout << endl << endl;

	}

}