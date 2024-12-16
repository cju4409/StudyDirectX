#include "WindowFrame.h"

// cpp에서 include는 무한 참조가 예방됨. h와 cpp를 나누는 이유
#include "WindowContainer.h"

LRESULT CALLBACK NewMessageProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	WindowContainer* const pWin = reinterpret_cast<WindowContainer*>(
		GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWin->WindowProc(hWnd, msg, wp, lp);
}

LRESULT CALLBACK MessageProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg)
	{
		//WM_NCCREATE :윈도우 생성될때 가장 먼저 발생하는 메시지
	case WM_NCCREATE:
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lp);
		WindowContainer* pWin = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);
		if (pWin == nullptr) {
			exit(-1);
		}
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWin));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(NewMessageProc));
		return pWin->WindowProc(hWnd, msg, wp, lp);
	}
	break;
	}

	return DefWindowProc(hWnd, msg, wp, lp);
}

void WindowFrame::RegisterWinClass() {
	WNDCLASSEX wc{};
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.hInstance = hInst;
	wc.lpszClassName = winClass.c_str();
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = MessageProc;
	RegisterClassEx(&wc);
}

bool WindowFrame::Initialize(WindowContainer* pWin, HINSTANCE hInst, wstring title, wstring winClass, int w, int h)
{
	this->hInst = hInst;
	ScreenWidth = w;
	ScreenHeight = h;
	Title = title;
	this->winClass = winClass;

	//레지스터에 등록
	RegisterWinClass();
	RECT wr{ 100,100,100 + w, 100 + h };
	DWORD ws{ WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU };

	//자동으로 스타일에 맞게 실제 창크기로 계산(원래는 위에 이름바와 테투리 틀때문에 정의돈 사이즈보다 더 크게됨)
	AdjustWindowRect(&wr, ws, false);

	handle = CreateWindowEx(0, winClass.c_str(), Title.c_str(), ws,
		wr.left, wr.top, wr.right - wr.left, wr.bottom - wr.top, NULL, NULL, hInst, pWin);

	if (handle == NULL) return false;

	ShowWindow(handle, SW_SHOW);
	SetForegroundWindow(handle);
	SetFocus(handle);

	return true;
}

bool WindowFrame::ProcessMessage()
{
	MSG msg{};
	while (PeekMessage(&msg, handle, NULL, NULL, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (msg.message == WM_NULL) {
		// 해당 윈도우가 활성화 되어있나 체크 함수
		if (!IsWindow(handle)) {
			handle = 0;
			UnregisterClass(winClass.c_str(), hInst);
			return false;
		}
	}

	return true;
}

WindowFrame::~WindowFrame()
{
	if (handle != NULL) {
		UnregisterClass(winClass.c_str(), hInst);
		DestroyWindow(handle);
	}
}

HWND WindowFrame::GetHandle()
{
	return handle;
}
