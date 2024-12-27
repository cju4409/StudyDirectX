#include "Mouse.h"

void Mouse::OnLeftPressed(int x, int y)
{
	eventBuffer.push(MouseEvent(MouseEvent::EventType::LPress, x, y));
	isLeftDown = true;
}

void Mouse::OnLeftReleased(int x, int y)
{
	eventBuffer.push(MouseEvent(MouseEvent::EventType::LRelease, x, y));
	isLeftDown = false;
}

void Mouse::OnRightPressed(int x, int y)
{
	eventBuffer.push(MouseEvent(MouseEvent::EventType::RPress, x, y));
	isRightDown = true;
}

void Mouse::OnRightReleased(int x, int y)
{
	eventBuffer.push(MouseEvent(MouseEvent::EventType::RRelease, x, y));
	isRightDown = false;
}

void Mouse::OnMiddlePressed(int x, int y)
{
	eventBuffer.push(MouseEvent(MouseEvent::EventType::MPress, x, y));
	isMiddleDown = true;
}

void Mouse::OnMiddleReleased(int x, int y)
{
	eventBuffer.push(MouseEvent(MouseEvent::EventType::MRelease, x, y));
	isMiddleDown = false;
}

void Mouse::OnWheelUp(int x, int y)
{
	eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelUp, x, y));
}

void Mouse::OnWheelDown(int x, int y)
{
	eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelDown, x, y));
}

void Mouse::OnMouseMove(int x, int y)
{
	eventBuffer.push(MouseEvent(MouseEvent::EventType::Move, x, y));
	pos = { x,y };
}

void Mouse::OnMouseMoveRaw(int x, int y)
{
	eventBuffer.push(MouseEvent(MouseEvent::EventType::MoveRaw, x, y));
}

bool Mouse::IsLeftDown()
{
	return isLeftDown;
}

bool Mouse::IsRightDown()
{
	return isRightDown;
}

bool Mouse::IsMiddleDown()
{
	return isMiddleDown;
}

MousePoint Mouse::GetPos()
{
	return pos;
}

bool Mouse::EventBufferIsEmpty()
{
	return eventBuffer.empty();
}

MouseEvent Mouse::ReadEvent()
{
	if (!EventBufferIsEmpty()) {
		MouseEvent e = eventBuffer.front();
		eventBuffer.pop();
		return e;
	}
	return MouseEvent();
}
