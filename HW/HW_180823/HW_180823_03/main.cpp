#include <iostream>
#include <time.h>

using namespace std;

void main()
{
	//숙제 숫자야구
	//배열 가르쳐주고 시킨걸 보니 배열 이용하는게 편한가봄

	int answer[3];	//컴퓨터가 무작위로 고르는 (정답)숫자를 저장하는 변수
	int cnt = 0;	//10번의 기회 카운트
	int input_value[3] = { 0, 0, 0 };	//플레이어가 입력한 숫자를 저장하는 변수
	int temp;

	//게임에 필요한 인수
	int strike = 0;
	int ball = 0;
	int out = 0;

	while (1)
	{
		//컴퓨터가 무작위로 숫자를 고른다
		srand(time(NULL));
		answer[0] = rand() % 10;
		answer[1] = rand() % 10;
		answer[2] = rand() % 10;

		//테스트출력
		//cout << "컴퓨터가 무작위로 고른 수(테스트출력): " << answer[0] << " " << answer[1] << " " << answer[2] << endl;

		//룰 부터가 중복숫자 금지인 것 같더라 (젠장)
		//그래서 컴퓨터가 뽑은 숫자 중복숫자 체크한 뒤 중복이 있으면 안 나올때까지 랜덤숫자 뽑는걸 반복.

		if (answer[0] != answer[1] && answer[0] != answer[2] && answer[1] != answer[2])
			break;
	}

	//10번의 기회
	for (cnt = 0; cnt < 10; cnt++)
	{
		strike = 0;
		ball = 0;
		out = 0;

		cout << "숫자 세개를 입력하시오" << endl;
		cin >> temp;
		input_value[0] = temp / 100;
		//cout << "테스트 출력: " << input_value[0] << " " << input_value[1] << " " << input_value[2] << " // " << temp << endl;
		temp = temp - (input_value[0] * 100);
		//cout << "테스트 출력: " << input_value[0] << " " << input_value[1] << " " << input_value[2] << " // " << temp << endl;
		input_value[1] = temp / 10;
		//cout << "테스트 출력: " << input_value[0] << " " << input_value[1] << " " << input_value[2] << " // " << temp << endl;
		temp = temp - (input_value[1] * 10);
		//cout << "테스트 출력: " << input_value[0] << " " << input_value[1] << " " << input_value[2] << " // " << temp << endl;
		input_value[2] = temp;
		//cout << "테스트 출력: " << input_value[0] << " " << input_value[1] << " " << input_value[2] << " // " << temp << endl;

		//숫자 비교
		//answer[], input_value[]
		for (int i = 0; i < 3; i++)
		{
			if (answer[i] == input_value[i])
			{
				strike++;
			}
			else if (answer[i] == input_value[0] || answer[i] == input_value[1] || answer[i] == input_value[2])
			{
				ball++;
			}
			else
			{
				out++;
			}
		}

		cout << "strike: " << strike << endl;
		cout << "ball: " << ball << endl;
		cout << "out: " << out << endl << endl;
		cout << "남은 기회: " << 9 - cnt << "번" << endl << endl;

		if (strike == 3)
			break;

	}

	if (strike == 3)
	{
		cout << "정답!" << endl << "게임 승리!" << endl;
	}
	else
	{
		cout << "10번의 게임 기회를 모두 소진" << endl << "게임 오버" << endl;
	}
}