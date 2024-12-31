#pragma once
#include <chrono>
using namespace std;
using namespace chrono;

class Time
{
	bool isRunning = false;
	static double deltaTime;
#ifdef _WIN64
	time_point<system_clock> start;
	time_point<system_clock> stop;
#else
	time_point<steady_clock> start;
	time_point<steady_clock> stop;
#endif
public:
	Time();
	double GetMilisecElapsed();
	bool Start();
	bool Stop();
	void Restart();
	void UpdateDeltaTime();
	static double DeltaTime();
};

