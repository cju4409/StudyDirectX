#include "MouseEvent.h"

MouseEvent::MouseEvent() : type(EventType::Invalid), pos({})
{
}

MouseEvent::MouseEvent(const EventType type, const int x, const int y) : type(type), pos({ x,y })
{
}

bool MouseEvent::IsValid() const
{
	return type != EventType::Invalid;
}

MouseEvent::EventType MouseEvent::GetType() const
{
	return type;
}

MousePoint MouseEvent::GetPos() const
{
	return pos;
}
