#include <iostream>

using namespace std;

void main()
{
	for (int k = 1; k < 10; k += 3)
	{
		for (int j = 1; j < 10; j++)
		{
			for (int i = k; i < k + 3; i++)
			{
				//\t : space bar 8´­¸° ³à¼® 
				cout << i << " x " << j << " = " << i * j << "\t";
			}
			cout << endl;
		}
		cout << endl;
	}
}