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

	while (!mouse.EventBufferIsEmpty()) {
		MouseEvent e = mouse.ReadEvent();
		wstring temp = L"";
		switch (e.GetType()) {

		case MouseEvent::EventType::LPress: {
			temp = L"LBT Down";
			break;
		}
		case MouseEvent::EventType::LRelease: {
			temp = L"LBT Up";
			break;
		}
		case MouseEvent::EventType::RPress: {
			temp = L"RBT Down";
			break;
		}
		case MouseEvent::EventType::RRelease: {
			temp = L"RBT Up";
			break;
		}
		case MouseEvent::EventType::MPress: {
			temp = L"MBT Down";
			break;
		}
		case MouseEvent::EventType::MRelease: {
			temp = L"MBT Up";
			break;
		}
		case MouseEvent::EventType::WheelUp: {
			temp = L"Wheel Up";
			break;
		}
		case MouseEvent::EventType::WheelDown: {
			temp = L"Wheel Down";
			break;
		}
		case MouseEvent::EventType::Move: {
			temp = L"Move";
			break;
		}
		case MouseEvent::EventType::MoveRaw: {
			wstring debugOut = L"X:" + to_wstring(e.GetPos().x) + L", Y:" + to_wstring(e.GetPos().y) + L"\n";
			OutputDebugString(debugOut.c_str());
			temp = L"MoveRaw";

			//카메라 회전 코드. 마우스 우클릭 후 마우스 움직임
			if (mouse.IsRightDown()) {
				gfx.cam.Rotate(e.GetPos().y * 0.01f, e.GetPos().x * 0.01f, 0);
			}

			break;
		}

		}

		temp += L"(";
		temp += to_wstring(e.GetPos().x);
		temp += L", ";
		temp += to_wstring(e.GetPos().y);
		temp += L")";

		SetWindowText(window.GetHandle(), temp.c_str());
	}
	if (keyboard.KeyIsPressed('A')) {
		gfx.cam.Translate(-0.01f, 0, 0);
	}
	if (keyboard.KeyIsPressed('D')) {
		gfx.cam.Translate(0.01f, 0, 0);
	}
	if (keyboard.KeyIsPressed('W')) {
		gfx.cam.Translate(0, 0, 0.01f);
	}
	if (keyboard.KeyIsPressed('S')) {
		gfx.cam.Translate(0, 0, -0.01f);
	}
	if (keyboard.KeyIsPressed('Q')) {
		gfx.cam.Translate(0, 0.01f, 0);
	}
	if (keyboard.KeyIsPressed('E')) {
		gfx.cam.Translate(0, -0.01f, 0);
	}
}
