#pragma once
#include "MouseEvent.h"
#include <queue>
using namespace std;

class Mouse
{
	queue<MouseEvent> eventBuffer;
	bool isLeftDown = false;
	bool isRightDown = false;
	bool isMiddleDown = false;
	MousePoint pos;

public:
	void OnLeftPressed(int x, int y);
	void OnLeftReleased(int x, int y);
	void OnRightPressed(int x, int y);
	void OnRightReleased(int x, int y);
	void OnMiddlePressed(int x, int y);
	void OnMiddleReleased(int x, int y);
	void OnWheelUp(int x, int y);
	void OnWheelDown(int x, int y);
	void OnMouseMove(int x, int y);
	void OnMouseMoveRaw(int x, int y);

	bool IsLeftDown();
	bool IsRightDown();
	bool IsMiddleDown();

	MousePoint GetPos();

	bool EventBufferIsEmpty();
	MouseEvent ReadEvent();
};

