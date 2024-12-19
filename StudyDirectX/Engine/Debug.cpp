#include "Debug.h"
#include <comdef.h>

void Debug::Error(wstring msg)
{
	MessageBox(NULL, msg.c_str(), L"Error", MB_ICONERROR);
}

void Debug::Error(HRESULT hr, wstring msg)
{
	_com_error errHr(hr);
	wstring err = L"Error: " + msg + L"\n" + errHr.ErrorMessage();
	Error(err);
}

void Debug::Log(wstring msg)
{
	MessageBox(NULL, msg.c_str(), L"Log", MB_ICONINFORMATION);
}
