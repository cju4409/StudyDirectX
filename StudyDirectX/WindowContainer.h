#pragma once
#include "WindowFrame.h"

class WindowContainer
{
protected:
	WindowFrame window;
public:
	WindowContainer();
	LRESULT WindowProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
};

