#pragma once
#include <Windows.h>
#include <string>
using namespace std;


//include시에 중복 순환참조를 막기위해 클래스 가상 선언을 통해서 방지가능
class WindowContainer;

class WindowFrame
{
	HWND handle = nullptr;
	HINSTANCE hInst = NULL;
	wstring Title{};
	wstring winClass{};
	int ScreenWidth = 0;
	int ScreenHeight = 0;
	void RegisterWinClass();
public:
	bool Initialize(WindowContainer* pWin, HINSTANCE hInst, wstring title, wstring winClass, int w, int h);
	bool ProcessMessage();
	~WindowFrame();
	HWND GetHandle();
};

