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
		//(�ڷ���)��ȣ ĳ��Ʈ�� ��Ÿ�ӿ��� �Ͼ�� ���� ���� ������
		//static_cast�� �����Ͽ��� �Ͼ�� ��Ÿ�ӿ��� ���ϰ� �پ��
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
