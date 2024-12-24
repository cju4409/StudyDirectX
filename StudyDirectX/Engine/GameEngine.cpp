#include "GameEngine.h"

bool GameEngine::Initialize(HINSTANCE hInst, wstring title, wstring winClass, int w, int h)
{
	if (!window.Initialize(this, hInst, title, winClass, w, h)) return false;
	return gfx.Initialize(window.GetHandle(), w, h);
}

bool GameEngine::ProcessMessage()
{
	return window.ProcessMessage();
}

void GameEngine::Render()
{
	gfx.Render();
}

void GameEngine::Update()
{
	/*while (!keyboard.KeyBufferIsEmpty())
	{
		KeyboardEvent e = keyboard.ReadKey();
		wstring temp = L"";
		if (e.IsPress()) {
			temp += L"Press ";
		}
		else if (e.IsRelease()) {
			temp += L"Release ";
		}

		temp += e.GetKeyCode();
		temp += L"\n";
		OutputDebugString(temp.c_str());
	}

	while (!keyboard.CharBufferIsEmpty())
	{
		unsigned char c = keyboard.ReadChar();
		wstring temp = L"";

		temp += c;
		temp += L"\n";
		OutputDebugString(temp.c_str());
	}*/

	if (keyboard.KeyIsPressed(VK_LEFT)) {
		gfx.cb.data.Offset.x -= 0.01f;
	}
	if (keyboard.KeyIsPressed(VK_RIGHT)) {
		gfx.cb.data.Offset.x += 0.01f;
	}
}
