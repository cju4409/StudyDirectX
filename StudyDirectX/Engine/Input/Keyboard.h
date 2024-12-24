#pragma once
#include "KeyboardEvent.h"
#include <queue>
using namespace std;

class Keyboard
{
	bool keyStates[256];
	bool autoRepeatKey = false;
	bool autoRepeatChar = false;
	queue<KeyboardEvent> keyBuffer;
	queue<unsigned char> charBuffer;

public:
	Keyboard();
	bool KeyIsPressed(const unsigned char key);
	bool KeyBufferIsEmpty();
	bool CharBufferIsEmpty();
	KeyboardEvent ReadKey();
	unsigned char ReadChar();
	void OnKeyPressed(const unsigned char key);
	void OnKeyRelease(const unsigned char key);
	void OnChar(const unsigned char key);
	void EnableAutoRepeatKey();
	void EnableAutoRepeatChar();
	void DisableAutoRepeatKey();
	void DisableAutoRepeatChar();
	bool IsKeyAutoRepeat();
	bool IsCharAutoRepeat();
};

