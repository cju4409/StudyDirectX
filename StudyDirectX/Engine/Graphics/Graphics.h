#pragma once
#include "AdapterReader.h"
#include "Shaders.h"

class Graphics
{
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> dc;
	ComPtr<IDXGISwapChain> swap;


	ComPtr<ID3D11RenderTargetView> rtv;
	//�����Ͷ����� ������Ʈ�� ����
	ComPtr<ID3D11RasterizerState> rs;

	VertexShader vs;
	PixelShader ps;

	bool InitializeDirectX(HWND hWnd, int w, int h);
	bool InitializeShaders();
public:
	bool Initialize(HWND hWnd, int w, int h);
	void Render();
};

