#include "Graphics.h"
#include "../Debug.h"


// 렌더링 파이프라인에서
// 정규화 한다: 길이를 1으로 바꾼다?
// IA(인풋어셈블러) => VS(버텍스셰이더) => RS(래스터라이저 스테이트) => PS(픽셀셰이더) => OM(아웃풋머져)
// RS: 3차원 정보들을 픽셀화 (2D화 함)

bool Graphics::InitializeDirectX(HWND hWnd, int w, int h)
{
	vector<AdapterData> adapters = AdapterReader::GetAdapters();
	if (adapters.size() == 0) {
		Debug::Error(L"그래픽 카드를 발견하지 못했습니다.");
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
	//창모드 처리 여부/ true: 창모드
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
		Debug::Error(hr, L"DirectX 초기화를 실패하였습니다.");
		return false;
	}

	ComPtr<ID3D11Texture2D> backBuffer;
	hr = swap->GetBuffer(0, __uuidof(ID3D11Texture2D),
		reinterpret_cast<void**>(backBuffer.GetAddressOf()));

	if (FAILED(hr)) {
		Debug::Error(hr, L"백버퍼를 가져오지 못했습니다.");
		return false;
	}

	hr = device->CreateRenderTargetView(backBuffer.Get(), 0, rtv.GetAddressOf());
	if (FAILED(hr)) {
		Debug::Error(hr, L"렌더 타겟뷰 생성을 실패했습니다.");
		return false;
	}

	D3D11_RASTERIZER_DESC rsd{};

	// FillMode - SOLID: 꽉채움, WIREFRAME: 선에 해당하는 픽셀만 만들어짐
	rsd.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	// CullMode - CULL_BACK: 뒷면 제거, CULL_FRONT: 앞면 제거
	rsd.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;

	hr = device->CreateRasterizerState(&rsd, rs.GetAddressOf());
	if (FAILED(hr)) {
		Debug::Error(L"레스터라이저 스테이트 생성을 실패했습니다.");
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
	//레스터라이저 스테이트 설정
	dc->RSSetState(rs.Get());

	swap->Present(1, 0);
}
