#pragma once
#include "AdapterReader.h"
#include "Shaders.h"
#include "Buffers.h"
#include "Vertex.h"
#include "ConstantBufferTypes.h"

class Graphics
{
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> dc;
	ComPtr<IDXGISwapChain> swap;


	ComPtr<ID3D11RenderTargetView> rtv;
	//�����Ͷ����� ������Ʈ�� ����
	ComPtr<ID3D11RasterizerState> rs;

	//���̹���
	ComPtr<ID3D11DepthStencilView> dsv;
	ComPtr<ID3D11Texture2D> dsb;
	ComPtr<ID3D11DepthStencilState> dss;

	VertexShader vs;
	PixelShader ps;

	VertexBuffer<Vertex> vb;
	VertexBuffer<Vertex> vb2;
	IndexBuffer<DWORD> ib;

	ComPtr<ID3D11ShaderResourceView> tex;
	ComPtr<ID3D11SamplerState> sam;

	bool InitializeDirectX(HWND hWnd, int w, int h);
	bool InitializeShaders();
	void InitializeScene();
public:
	ConstantBuffer<CB_VS_Transform> cb;
	bool Initialize(HWND hWnd, int w, int h);
	void Render();
};

