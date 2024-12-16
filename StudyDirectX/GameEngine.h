#pragma once
#include "WindowContainer.h"
class GameEngine :
    public WindowContainer
{
public:
    bool Initialize(HINSTANCE hInst, wstring title, wstring winClass, int w, int h);
    bool ProcessMessage();
};

