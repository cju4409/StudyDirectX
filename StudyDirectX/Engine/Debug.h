#pragma once
#include <Windows.h>
#include <string>
using namespace std;

class Debug
{
public:
	static void Error(wstring msg);
	static void Error(HRESULT hr, wstring msg);
	static void Log(wstring msg);
};

