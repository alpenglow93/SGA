#pragma once
//GettickCount -> 1초 == 1000
//tick-> 1 / 1000; 
class Timer
{
private:
	__int64 tick; //
	__int64 start; 

	__int64 elapsed; //1프레임당 경과 시간 
	__int64 last;

public:
	Timer();
	~Timer();

	void Update();

	float Running();
	float Elapsed();
};
