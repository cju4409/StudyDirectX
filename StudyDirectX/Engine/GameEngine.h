#pragma once
#include "../WindowContainer.h"
#include "Graphics//Graphics.h"
#include "Time.h"

class GameEngine :
    public WindowContainer
{
    Graphics gfx;
    Time time;
public:
    bool Initialize(HINSTANCE hInst, wstring title, wstring winClass, int w, int h);
    bool ProcessMessage();
    void Render();
    void Update();
};

