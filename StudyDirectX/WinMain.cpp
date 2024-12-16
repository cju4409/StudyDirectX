#include "GameEngine.h"

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, PSTR lpCmd, INT nShow) {
	GameEngine engine;
	if (
		engine.Initialize(hInst, L"StudyDirectX", L"dxEngine", 800, 600)
		) {
		while (engine.ProcessMessage()) {

		}
	}
	return 0;
}