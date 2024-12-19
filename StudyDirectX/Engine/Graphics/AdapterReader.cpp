#include "AdapterReader.h"
#include "../Debug.h"

vector<AdapterData> AdapterReader::adapters{};

AdapterData::AdapterData(IDXGIAdapter* adapter) : pAdapter(adapter)
{
	HRESULT hr = pAdapter->GetDesc(&desc);
	if (FAILED(hr)) {
		//어댑터 정보를 읽어 오지 못했음
		Debug::Error(hr, L"어댑터 정보를 가져오지 못했습니다.");
	}
}

vector<AdapterData> AdapterReader::GetAdapters()
{
	if (adapters.size() == 0) {
		ComPtr<IDXGIFactory> pFactory{};
		HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf()));
		if (FAILED(hr)) {
			Debug::Error(L"DXGIFactory 생성을 실패 하였습니다.");
			exit(-1);
		}

		IDXGIAdapter* pAdapter = nullptr;
		UINT idx = 0;
		//wstring temp{};
		while (SUCCEEDED(pFactory->EnumAdapters(idx++, &pAdapter))) {
			adapters.push_back(AdapterData(pAdapter));
			/*temp += adapters[idx - 1].desc.Description;
			temp += L"\n";*/
		}
		//Debug::Log(temp);

	}
	return adapters;
}
