#include "WindowContainer.h"
#include <iostream>

WindowContainer::WindowContainer()
{
}

LRESULT WindowContainer::WindowProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_KEYDOWN:
	{
		unsigned char key = static_cast<unsigned char>(wp);
		if (keyboard.IsKeyAutoRepeat()) {
			keyboard.OnKeyPressed(key);
		}
		else {
			const bool wasPressed = lp & 0x40000000;
			if (!wasPressed) {
				keyboard.OnKeyPressed(key);
			}
		}
	}
	break;
	case WM_KEYUP:
	{
		//(자료형)괄호 캐스트는 런타임에서 일어나서 성능 부하 더있음
		//static_cast는 컴파일에서 일어나서 런타임에서 부하가 줄어듬
		unsigned char key = static_cast<unsigned char>(wp);
		keyboard.OnKeyRelease(key);
	}
	break;
	case WM_CHAR:
	{
		unsigned char key = static_cast<unsigned char>(wp);
		if (keyboard.IsCharAutoRepeat()) {
			keyboard.OnChar(key);
		}
		else {
			const bool wasPressed = lp & 0x40000000;
			if (!wasPressed) {
				keyboard.OnChar(key);
			}
		}
	}
	break;
	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}
