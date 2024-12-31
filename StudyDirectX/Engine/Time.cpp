#include "Time.h"

double Time::deltaTime = 0.0;

Time::Time() {
	stop = start = high_resolution_clock::now();
}

double Time::GetMilisecElapsed()
{
	duration<double, milli> elapsed;
	if (isRunning) {
		elapsed = duration<double, milli>(high_resolution_clock::now() - start);
	}
	else {
		elapsed = duration<double, milli>(stop - start);
	}
	return elapsed.count();
}

bool Time::Start()
{
	if (isRunning) return false;
	isRunning = true;
	start = high_resolution_clock::now();
	return true;
}

bool Time::Stop()
{
	if (!isRunning) return false;
	isRunning = false;
	stop = high_resolution_clock::now();
	return true;
}

void Time::Restart()
{
	isRunning = true;
	start = high_resolution_clock::now();
}

void Time::UpdateDeltaTime()
{
	deltaTime = GetMilisecElapsed() / 1000.0;
	Restart();
}

double Time::DeltaTime()
{
	return deltaTime;
}
