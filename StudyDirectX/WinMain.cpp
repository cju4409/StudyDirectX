#include "Engine/GameEngine.h"
#include <memory>

// ���̷�ƮX - �ʿ� 2���� => ����̽� : �׷���ī��, ����̽����ؽ�Ʈ : ������ ����������
// DXGI�� �ϵ���� ���� �ʿ�

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, PSTR lpCmd, INT nShow) {
	GameEngine engine;
	if (engine.Initialize(hInst, L"StudyDirectX", L"dxEngine", 800, 600)) {
		while (engine.ProcessMessage()) {
			engine.Render();
		}
	}

	return 0;
}