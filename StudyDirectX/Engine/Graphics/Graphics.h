#pragma once
#include "AdapterReader.h"
#include "Shaders.h"
#include "Buffers.h"
#include "Vertex.h"
#include "ConstantBufferTypes.h"
#include "Camera.h"

class Graphics
{
	int ScreenWidth, ScreenHeight;
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> dc;
	ComPtr<IDXGISwapChain> swap;


	ComPtr<ID3D11RenderTargetView> rtv;
	//래스터라이저 스테이트를 참조
	ComPtr<ID3D11RasterizerState> rs;

	//깊이버퍼
	ComPtr<ID3D11DepthStencilView> dsv;
	ComPtr<ID3D11Texture2D> dsb;
	ComPtr<ID3D11DepthStencilState> dss;

	VertexShader vs;
	PixelShader ps;

	VertexBuffer<Vertex> vb;
	IndexBuffer<DWORD> ib;

	ComPtr<ID3D11ShaderResourceView> tex;
	ComPtr<ID3D11SamplerState> sam;

	bool InitializeDirectX(HWND hWnd, int w, int h);
	bool InitializeShaders();
	void InitializeScene();
public:
	Camera cam;
	ConstantBuffer<CB_VS_VIEWPROJ> cb;
	bool Initialize(HWND hWnd, int w, int h);
	void Render();
};

