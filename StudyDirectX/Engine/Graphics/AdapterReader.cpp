#include "AdapterReader.h"
#include "../Debug.h"

vector<AdapterData> AdapterReader::adapters{};

AdapterData::AdapterData(IDXGIAdapter* adapter) : pAdapter(adapter)
{
	HRESULT hr = pAdapter->GetDesc(&desc);
	if (FAILED(hr)) {
		//����� ������ �о� ���� ������
		Debug::Error(hr, L"����� ������ �������� ���߽��ϴ�.");
	}
}

vector<AdapterData> AdapterReader::GetAdapters()
{
	if (adapters.size() == 0) {
		ComPtr<IDXGIFactory> pFactory{};
		HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf()));
		if (FAILED(hr)) {
			Debug::Error(L"DXGIFactory ������ ���� �Ͽ����ϴ�.");
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
