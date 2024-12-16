#include "GameEngine.h"

bool GameEngine::Initialize(HINSTANCE hInst, wstring title, wstring winClass, int w, int h)
{
	return window.Initialize(this, hInst, title, winClass, w, h);
}

bool GameEngine::ProcessMessage()
{
	return window.ProcessMessage();
}
