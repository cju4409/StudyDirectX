#include "WindowContainer.h"
#include "Engine/Debug.h"
#include <memory>

WindowContainer::WindowContainer()
{
	static bool rawInputInitialize = false;
	if (!rawInputInitialize) {
		rawInputInitialize = true;
		RAWINPUTDEVICE rid{};
		rid.usUsagePage = 0x01; //마우스 원시 입력
		rid.usUsage = 0x02;
		if (!RegisterRawInputDevices(&rid, 1, sizeof(rid))) {
			Debug::Error(L"마우스 원시 입력 초기화를 실패했습니다.");
			//프로그램 종료
			exit(-1);
		}
	}
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WindowContainer::WindowProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wp, lp)) return true;
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		mouse.OnLeftPressed(LOWORD(lp), HIWORD(lp));
		break;
	case WM_LBUTTONUP:
		mouse.OnLeftReleased(LOWORD(lp), HIWORD(lp));
		break;
	case WM_RBUTTONDOWN:
		mouse.OnRightPressed(LOWORD(lp), HIWORD(lp));
		break;
	case WM_RBUTTONUP:
		mouse.OnRightReleased(LOWORD(lp), HIWORD(lp));
		break;
	case WM_MBUTTONDOWN:
		mouse.OnMiddlePressed(LOWORD(lp), HIWORD(lp));
		break;
	case WM_MBUTTONUP:
		mouse.OnMiddleReleased(LOWORD(lp), HIWORD(lp));
		break;
	case WM_MOUSEWHEEL:
		if (GET_WHEEL_DELTA_WPARAM(wp) > 0) {
			mouse.OnWheelUp(LOWORD(lp), HIWORD(lp));
		}
		else if (GET_WHEEL_DELTA_WPARAM(wp) < 0) {
			mouse.OnWheelDown(LOWORD(lp), HIWORD(lp));
		}
		break;
	case WM_MOUSEMOVE:
		mouse.OnMouseMove(LOWORD(lp), HIWORD(lp));
		break;
	case WM_INPUT: {
		UINT size = 0;
		GetRawInputData(reinterpret_cast<HRAWINPUT>(lp), RID_INPUT, NULL, &size, sizeof(RAWINPUTHEADER));
		if (size > 0) {
			unique_ptr<BYTE[]> rawdata = make_unique<BYTE[]>(size);
			if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lp), RID_INPUT, rawdata.get(), &size,
				sizeof(RAWINPUTHEADER)) == size) {
				RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(rawdata.get());
				if (raw->header.dwType == RIM_TYPEMOUSE) {
					mouse.OnMouseMoveRaw(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
				}
			}
		}
		break;
	}
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
