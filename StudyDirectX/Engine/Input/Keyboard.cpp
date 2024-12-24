#include "Keyboard.h"

Keyboard::Keyboard()
{
	for (int i = 0; i < 256; ++i) {
		keyStates[i] = false;
	}
}

bool Keyboard::KeyIsPressed(const unsigned char key)
{
	return keyStates[key];
}

bool Keyboard::KeyBufferIsEmpty()
{
	return keyBuffer.empty();
}

bool Keyboard::CharBufferIsEmpty()
{
	return charBuffer.empty();
}

KeyboardEvent Keyboard::ReadKey()
{
	if (KeyBufferIsEmpty()) return KeyboardEvent();
	KeyboardEvent e = keyBuffer.front();
	keyBuffer.pop();
	return e;
}

unsigned char Keyboard::ReadChar()
{
	if (CharBufferIsEmpty()) return 0u;

	unsigned char c = charBuffer.front();
	charBuffer.pop();
	return c;
}

void Keyboard::OnKeyPressed(const unsigned char key)
{
	keyStates[key] = true;
	keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Press, key));
}

void Keyboard::OnKeyRelease(const unsigned char key)
{
	keyStates[key] = false;
	keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Release, key));
}

void Keyboard::OnChar(const unsigned char key)
{
	charBuffer.push(key);
}

void Keyboard::EnableAutoRepeatKey()
{
	autoRepeatKey = true;
}

void Keyboard::EnableAutoRepeatChar()
{
	autoRepeatChar = true;
}

void Keyboard::DisableAutoRepeatKey()
{
	autoRepeatKey = false;
}

void Keyboard::DisableAutoRepeatChar()
{
	autoRepeatChar = false;
}

bool Keyboard::IsKeyAutoRepeat()
{
	return autoRepeatKey;
}

bool Keyboard::IsCharAutoRepeat()
{
	return autoRepeatChar;
}
