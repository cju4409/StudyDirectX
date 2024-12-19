#include "Shaders.h"
#include "../Debug.h"

bool VertexShader::Initailize(ID3D11Device* device, wstring path, D3D11_INPUT_ELEMENT_DESC* layout, UINT size)
{
	HRESULT hr = D3DReadFileToBlob(path.c_str(), buffer.GetAddressOf());
	if (FAILED(hr)) {
		wstring msg = L"������ �о� ���� ���߽��ϴ�.";
		msg += L"path: " + path;
		Debug::Error(hr, msg);
		return false;
	}

	hr = device->CreateVertexShader(buffer->GetBufferPointer(), buffer->GetBufferSize(),
		nullptr, shader.GetAddressOf());
	if (FAILED(hr)) {
		Debug::Error(hr, L"���ؽ����̴� ������ �����߽��ϴ�.");
		return false;
	}

	hr = device->CreateInputLayout(layout, size, buffer->GetBufferPointer(),
		buffer->GetBufferSize(), inputLayout.GetAddressOf());

	if (FAILED(hr)) {
		Debug::Error(hr, L"��ǲ���̾ƿ� ������ �����߽��ϴ�.");
		return false;
	}

	return true;
}

ID3D11VertexShader* VertexShader::GetShader()
{
	return shader.Get();
}

ID3D10Blob* VertexShader::GetBuffer()
{
	return buffer.Get();
}

ID3D11InputLayout* VertexShader::GetInputLayout()
{
	return inputLayout.Get();
}


bool PixelShader::Initailize(ID3D11Device* device, wstring path)
{
	HRESULT hr = D3DReadFileToBlob(path.c_str(), buffer.GetAddressOf());
	if (FAILED(hr)) {
		wstring msg = L"������ �о� ���� ���߽��ϴ�.";
		msg += L"path: " + path;
		Debug::Error(hr, msg);
		return false;
	}

	hr = device->CreatePixelShader(buffer->GetBufferPointer(), buffer->GetBufferSize(), nullptr,
		shader.GetAddressOf());
	if (FAILED(hr)) {
		Debug::Error(hr, L"�ȼ����̴� ������ �����߽��ϴ�.");
		return false;
	}

	return true;
}

ID3D11PixelShader* PixelShader::GetShader()
{
	return shader.Get();
}

ID3D10Blob* PixelShader::GetBuffer()
{
	return buffer.Get();
}

