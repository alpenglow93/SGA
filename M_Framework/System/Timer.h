#pragma once
//GettickCount -> 1�� == 1000
//tick-> 1 / 1000; 
class Timer
{
private:
	__int64 tick; //
	__int64 start; 

	__int64 elapsed; //1�����Ӵ� ��� �ð� 
	__int64 last;

public:
	Timer();
	~Timer();

	void Update();

	float Running();
	float Elapsed();
};
