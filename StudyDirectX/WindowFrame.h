#pragma once
#include <Windows.h>
#include <string>
using namespace std;


//include�ÿ� �ߺ� ��ȯ������ �������� Ŭ���� ���� ������ ���ؼ� ��������
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

