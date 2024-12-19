#include "Engine/GameEngine.h"
#include <memory>

// 다이렉트X - 필요 2가지 => 디바이스 : 그래픽카드, 디바이스컨텍스트 : 렌더링 파이프라인
// DXGI로 하드웨어 연동 필요

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, PSTR lpCmd, INT nShow) {
	GameEngine engine;
	if (engine.Initialize(hInst, L"StudyDirectX", L"dxEngine", 800, 600)) {
		while (engine.ProcessMessage()) {
			engine.Render();
		}
	}

	return 0;
}