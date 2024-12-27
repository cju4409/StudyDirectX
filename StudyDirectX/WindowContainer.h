#pragma once
#include "WindowFrame.h"
#include "Engine/Input/Keyboard.h"
#include "Engine/Input/Mouse.h"

class WindowContainer
{
protected:
	WindowFrame window;
	Keyboard keyboard;
	Mouse mouse;
public:
	WindowContainer();
	LRESULT WindowProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
};

