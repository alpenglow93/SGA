#include "stdafx.h"
#include "Timer.h"
//GettickCount -> 1 �� = 1000
//timeGetTime  -> 

Timer::Timer()
{
	//���� Ÿ�̸� �� ����Ҽ� �̳�?
	//���� Ÿ�̸Ӷ� -> 1�� = 1,000,000
	//tick -> 1 / 1,000,000;
	QueryPerformanceFrequency((LARGE_INTEGER*)&tick);
	//tick = 1 / 1000;
	QueryPerformanceCounter((LARGE_INTEGER*)&start);
	//start = GetTickCount(); or timeGetTime();

	last = 0;
}


Timer::~Timer()
{
}

void Timer::Update()
{
	__int64 current;
	QueryPerformanceCounter((LARGE_INTEGER*)&current);

	elapsed = current - last;
	
	last = current;
}

float Timer::Running()
{
	__int64 current;
	QueryPerformanceCounter((LARGE_INTEGER*)&current);

	return (float)((double)(current - start) / tick);
}

float Timer::Elapsed()
{
	return (float)((double)elapsed / tick);
}
