#pragma once
#include "WindowFrame.h"
#include "Engine/Input/Keyboard.h"

class WindowContainer
{
protected:
	WindowFrame window;
	Keyboard keyboard;
public:
	WindowContainer();
	LRESULT WindowProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
};

