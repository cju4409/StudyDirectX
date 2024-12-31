#include "Graphics.h"
#include "../Debug.h"
//텍스쳐 불러옴
#include <WICTextureLoader.h>
#include "../Time.h"


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


	//뷰포트 설정
	D3D11_VIEWPORT vp{};
	vp.Width = w;
	vp.Height = h;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;

	dc->RSSetViewports(1, &vp);

	//Create Sampler State
	D3D11_SAMPLER_DESC samDesc{};
	//LINEAR:약간 흐릿하게 표현. 픽셀깨짐 X
	//POINT: 선명하게 표현
	samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	// D3D11_TEXTURE_ADDRESS_WRAP : 그림이 이어져서 여러개 나옴
	// D3D11_TEXTURE_ADDRESS_CLAMP : 그림이 한번만 나옴
	// D3D11_TEXTURE_ADDRESS_MIRROR : 그림의 방향이 뒤집혀서 이어져서 여러개 나옴
	samDesc.AddressU = samDesc.AddressV = samDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samDesc.MinLOD = 0;
	samDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = device->CreateSamplerState(&samDesc, sam.GetAddressOf());
	if (FAILED(hr)) {
		Debug::Error(hr, L"샘플러 스테이트 생성을 실패했습니다.");
		return false;
	}

	//깊이버퍼
	D3D11_DEPTH_STENCIL_DESC dsDesc{};
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
	hr = device->CreateDepthStencilState(&dsDesc, dss.GetAddressOf());
	if (FAILED(hr)) {
		Debug::Error(hr, L"뎁스 스텐실 스테이트 생성을 실패했습니다.");
		return false;
	}

	D3D11_TEXTURE2D_DESC dsbDesc{};
	dsbDesc.Width = w;
	dsbDesc.Height = h;
	dsbDesc.MipLevels = 1;
	dsbDesc.ArraySize = 1;
	dsbDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsbDesc.SampleDesc.Count = 1;
	dsbDesc.SampleDesc.Quality = 0;
	dsbDesc.Usage = D3D11_USAGE_DEFAULT;
	dsbDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	dsbDesc.CPUAccessFlags = 0;
	dsbDesc.MiscFlags = 0;

	hr = device->CreateTexture2D(&dsbDesc, nullptr, dsb.GetAddressOf());
	if (FAILED(hr)) {
		Debug::Error(hr, L"뎁스 스텐실 버퍼 생성을 실패했습니다.");
		return false;
	}

	hr = device->CreateDepthStencilView(dsb.Get(), nullptr, dsv.GetAddressOf());
	if (FAILED(hr)) {
		Debug::Error(hr, L"뎁스 스텐실 뷰 생성을 실패했습니다.");
		return false;
	}
	dc->OMSetRenderTargets(1, rtv.GetAddressOf(), dsv.Get());

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
		{"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
		D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,0},
		// 12 적힌곳 => 버퍼에 저장하기 시작지점. (x,y,z) 4*3 = 12. 포지션이 12바이트라서
		// D3D11_APPEND_ALIGNED_ELEMENT: 자동으로 시작지점 알려줌
		{"COLOR", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
		D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT,
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

void Graphics::InitializeScene()
{
	Vertex v[] = {
		Vertex({-0.5f, -0.5f, 0.0f},{1,1,1,1}, {0,1}),
		Vertex({-0.5f,  0.5f, 0.0f},{1,1,1,1}, {0,0}),
		Vertex({ 0.5f,  0.5f, 0.0f},{0,0,0,1}, {1,0}),
		Vertex({ 0.5f, -0.5f, 0.0f},{0,0,0,1}, {1,1})

		//Vertex({-0.5f, -0.5f, 0.0f},{1,0,0,1}),
		//Vertex({0.0f, 0.5f, 0.0f},{0,1,0,1}),
		//Vertex({0.5f, -0.5f, 0.0f},{0,0,1,1})
	};


	HRESULT hr = vb.Initialize(device.Get(), v, ARRAYSIZE(v));
	if (FAILED(hr)) {
		Debug::Error(hr, L"버텍스 버퍼 생성을 실패했습니다.");
	}

	DWORD idx[] = {
		0,1,2,
		0,2,3
	};

	hr = ib.Initialize(device.Get(), idx, ARRAYSIZE(idx));
	if (FAILED(hr)) {
		Debug::Error(hr, L"인덱스 버퍼 생성을 실패했습니다.");
	}

	hr = cb.Initialize(device.Get(), dc.Get());
	if (FAILED(hr)) {
		Debug::Error(hr, L"콘스탄트 버퍼 생성을 실패했습니다.");
	}

	hr = CreateWICTextureFromFile(device.Get(), L"Assets/Textures/texture.png", nullptr,
		tex.GetAddressOf());
	if (FAILED(hr)) {
		Debug::Error(hr, L"텍스쳐 로딩을 실패했습니다.");
	}

	cam.SetPos(0, 0, -2);
	cam.SetProjection(90.0f, (float)ScreenWidth / (float)ScreenHeight, 0.1f, 1000.0f);

	//스프라이트 폰트
	spBatch = make_unique<SpriteBatch>(dc.Get());
	spFont = make_unique<SpriteFont>(device.Get(), L"Assets\\Fonts\\arial.spf");
}

bool Graphics::Initialize(HWND hWnd, int w, int h)
{
	ScreenWidth = w;
	ScreenHeight = h;
	if (!InitializeDirectX(hWnd, w, h)) return false;
	InitializeScene();

	//ImGUI SetUp
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(device.Get(), dc.Get());
	ImGui::StyleColorsDark();

	return InitializeShaders();
}

void Graphics::Render()
{
	float bgColor[] = { 0.3f,0.4f,0.9f,1 };
	// 원래 그려져있던 것을 지워줌
	dc->ClearRenderTargetView(rtv.Get(), bgColor);
	dc->ClearDepthStencilView(dsv.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	//인풋어셈블러
	UINT offset = 0;
	dc->IASetInputLayout(vs.GetInputLayout());
	dc->IASetVertexBuffers(0, 1, vb.GetAddressOf(), vb.StridePtr(), &offset);
	dc->IASetIndexBuffer(ib.Get(), DXGI_FORMAT_R32_UINT, 0);
	//콘스탄트 버퍼
	//XMMatrixTranspose: 왼손 좌표계를 오른손 좌표계로 변환해줌. 쉐이더에서는 오른손 좌표계를 쓰므로
	cb.data.viewProj = XMMatrixTranspose(cam.GetViewProjection());
	cb.Update();
	dc->VSSetConstantBuffers(0, 1, cb.GetAddressOf());

	//버텍스셰이더
	dc->VSSetShader(vs.GetShader(), nullptr, 0);
	//레스터라이저 스테이트 설정
	dc->RSSetState(rs.Get());
	//픽셀셰이더
	dc->PSSetShader(ps.GetShader(), nullptr, 0);
	dc->PSSetShaderResources(0, 1, tex.GetAddressOf());
	dc->PSSetSamplers(0, 1, sam.GetAddressOf());

	dc->OMSetDepthStencilState(dss.Get(), 0);
	//드로우콜
	dc->DrawIndexed(ib.Size(), 0, 0);

	//FPS
	static wstring strFPS = L"FPS: 0";
	static int fpsCounter = 0;
	++fpsCounter;
	static double playTime = 0.0;
	playTime += Time::DeltaTime();
	if (playTime >= 1.0) {
		playTime = 0.0;
		strFPS = L"FPS: " + to_wstring(fpsCounter);
		fpsCounter = 0;
	}

	//Draw Sprite Font
	spBatch->Begin();
	spFont->DrawString(spBatch.get(), strFPS.c_str(), XMFLOAT2(0, 0), Colors::White, 0, XMFLOAT2(1, 1));
	spBatch->End();

	//ImGUI
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	//Create Popup
	ImGui::Begin("Test");
	ImGui::Button("Button");
	ImGui::End();
	//Draw Call
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	//Present(1,0):모니터의 주사율과 동기화함. 최대 프레임이 정해짐. 수직동기화. 계단현상 방지
	swap->Present(1, 0);
}
