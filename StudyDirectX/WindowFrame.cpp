#include "WindowFrame.h"

// cpp���� include�� ���� ������ �����. h�� cpp�� ������ ����
#include "WindowContainer.h"

LRESULT CALLBACK NewMessageProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	WindowContainer* const pWin = reinterpret_cast<WindowContainer*>(
		GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWin->WindowProc(hWnd, msg, wp, lp);
}

LRESULT CALLBACK MessageProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg)
	{
		//WM_NCCREATE :������ �����ɶ� ���� ���� �߻��ϴ� �޽���
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

	//�������Ϳ� ���
	RegisterWinClass();
	RECT wr{ 100,100,100 + w, 100 + h };
	DWORD ws{ WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU };

	//�ڵ����� ��Ÿ�Ͽ� �°� ���� âũ��� ���(������ ���� �̸��ٿ� ������ Ʋ������ ���ǵ� ������� �� ũ�Ե�)
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
		// �ش� �����찡 Ȱ��ȭ �Ǿ��ֳ� üũ �Լ�
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
