#include "Graphics.h"
#include "../Debug.h"


// ������ ���������ο���
// ����ȭ �Ѵ�: ���̸� 1���� �ٲ۴�?
// IA(��ǲ�����) => VS(���ؽ����̴�) => RS(�����Ͷ����� ������Ʈ) => PS(�ȼ����̴�) => OM(�ƿ�ǲ����)
// RS: 3���� �������� �ȼ�ȭ (2Dȭ ��)

bool Graphics::InitializeDirectX(HWND hWnd, int w, int h)
{
	vector<AdapterData> adapters = AdapterReader::GetAdapters();
	if (adapters.size() == 0) {
		Debug::Error(L"�׷��� ī�带 �߰����� ���߽��ϴ�.");
		return false;
	}
	DXGI_SWAP_CHAIN_DESC scd{};
	scd.BufferDesc.Width = w;
	scd.BufferDesc.Height = h;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 1;
	scd.OutputWindow = hWnd;
	//â��� ó�� ����/ true: â���
	scd.Windowed = true;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT hr = D3D11CreateDeviceAndSwapChain
	(
		adapters[0].pAdapter,
		D3D_DRIVER_TYPE_UNKNOWN,
		0, 0, 0, 0,
		D3D11_SDK_VERSION,
		&scd, swap.GetAddressOf(),
		device.GetAddressOf(),
		NULL, dc.GetAddressOf()
	);

	if (FAILED(hr)) {
		Debug::Error(hr, L"DirectX �ʱ�ȭ�� �����Ͽ����ϴ�.");
		return false;
	}

	ComPtr<ID3D11Texture2D> backBuffer;
	hr = swap->GetBuffer(0, __uuidof(ID3D11Texture2D),
		reinterpret_cast<void**>(backBuffer.GetAddressOf()));

	if (FAILED(hr)) {
		Debug::Error(hr, L"����۸� �������� ���߽��ϴ�.");
		return false;
	}

	hr = device->CreateRenderTargetView(backBuffer.Get(), 0, rtv.GetAddressOf());
	if (FAILED(hr)) {
		Debug::Error(hr, L"���� Ÿ�ٺ� ������ �����߽��ϴ�.");
		return false;
	}

	D3D11_RASTERIZER_DESC rsd{};

	// FillMode - SOLID: ��ä��, WIREFRAME: ���� �ش��ϴ� �ȼ��� �������
	rsd.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	// CullMode - CULL_BACK: �޸� ����, CULL_FRONT: �ո� ����
	rsd.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;

	hr = device->CreateRasterizerState(&rsd, rs.GetAddressOf());
	if (FAILED(hr)) {
		Debug::Error(L"�����Ͷ����� ������Ʈ ������ �����߽��ϴ�.");
		return false;
	}

	dc->OMSetRenderTargets(1, rtv.GetAddressOf(), nullptr);

	return true;
}

bool Graphics::InitializeShaders()
{
	wstring shaderFolder = L"";
#ifdef _DEBUG
	{
#ifdef _WIN64
		shaderFolder = L"../x64/Debug/";
#else //Win32 (x86)
		shaderFolder = L"../Debug/";
#endif
	}
#else //Release
	{
#ifdef _WIN64
		shaderFolder = L"../x64/Release/";
#else //Win32 (x86)
		shaderFolder = L"../Release/";
#endif
}
#endif
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0,0,
		D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,0}
	};

	if (!vs.Initailize(device.Get(), shaderFolder + L"vs.cso", layout, ARRAYSIZE(layout))) {
		return false;
	}
	if (!ps.Initailize(device.Get(), shaderFolder + L"ps.cso")) {
		return false;
	}
	return true;
}

bool Graphics::Initialize(HWND hWnd, int w, int h)
{
	if (!InitializeDirectX(hWnd, w, h))return false;
	return InitializeShaders();
}

void Graphics::Render()
{
	float bgColor[] = { 0,0,0,1 };
	dc->ClearRenderTargetView(rtv.Get(), bgColor);
	//�����Ͷ����� ������Ʈ ����
	dc->RSSetState(rs.Get());

	swap->Present(1, 0);
}
