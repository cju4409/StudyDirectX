#include "WindowContainer.h"

WindowContainer::WindowContainer()
{
}

LRESULT WindowContainer::WindowProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}
