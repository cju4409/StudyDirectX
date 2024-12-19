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
