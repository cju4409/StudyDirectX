#pragma once
#include <d3d11.h>
#include <vector>
#include <wrl/client.h>
using namespace std;
using namespace Microsoft::WRL;

struct AdapterData {
	IDXGIAdapter* pAdapter = nullptr;
	DXGI_ADAPTER_DESC desc;
	AdapterData(IDXGIAdapter* adapter);
};

class AdapterReader
{
	static vector<AdapterData> adapters;
public:
	static vector<AdapterData> GetAdapters();
};

