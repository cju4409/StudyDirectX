#include "KeyboardEvent.h"

//0u: unsigned 0 ÀÇ¹Ì
KeyboardEvent::KeyboardEvent() : type(EventType::Invalid), key(0u)
{
}

KeyboardEvent::KeyboardEvent(const EventType type, const unsigned char key) : type(type), key(key)
{
}

bool KeyboardEvent::IsPress() const
{
	return type == EventType::Press;
}

bool KeyboardEvent::IsRelease() const
{
	return type == EventType::Release;
}

unsigned char KeyboardEvent::GetKeyCode() const
{
	return key;
}
