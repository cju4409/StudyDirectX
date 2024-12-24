#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include "../Debug.h"
// wrf/client.h: 다이렉트X용 스마트포인터
using namespace Microsoft::WRL;

template<typename T>
class Buffer {
protected:
	ComPtr<ID3D11Buffer> buffer;
	UINT size = 0;

	HRESULT Initialize(ID3D11Device* device, T* data, UINT size, UINT bindFlag) {
		Buffer::size = size;

		D3D11_BUFFER_DESC desc{};
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(T) * size;
		desc.BindFlags = bindFlag;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA rd{};
		rd.pSysMem = data;

		return device->CreateBuffer(&desc, &rd, buffer.GetAddressOf());
	}

	HRESULT Initialize(ID3D11Device* device, const D3D11_BUFFER_DESC& desc) {
		return device->CreateBuffer(&desc, 0, buffer.GetAddressOf());
	}

public:
	Buffer() {}
	ID3D11Buffer* Get() const {
		return buffer.Get();
	}

	ID3D11Buffer* const* GetAddressOf() const {
		return buffer.GetAddressOf();
	}

	UINT Size() const {
		return size;
	}
};

template<typename T>
class VertexBuffer : public Buffer<T> {
	UINT stride = 0;
public:
	HRESULT Initialize(ID3D11Device* device, T* data, UINT size) {

		stride = sizeof(T);
		return Buffer<T>::Initialize(device, data, size, D3D11_BIND_VERTEX_BUFFER);
	}

	const UINT Stride() const {
		return stride;
	}
	const UINT* StridePtr() const {
		return &stride;
	}
};

template<typename T>
class IndexBuffer :public Buffer<T> {
public:
	HRESULT Initialize(ID3D11Device* device, T* data, UINT size) {
		return Buffer<T>::Initialize(device, data, size, D3D11_BIND_INDEX_BUFFER);
	}
};

template<typename T>
class ConstantBuffer :public Buffer<T> {
	ID3D11DeviceContext* dc = nullptr;
public:
	T data;
	ConstantBuffer():Buffer<T>(){}
	HRESULT Initialize(ID3D11Device* device, ID3D11DeviceContext* dc) {
		this->dc = dc;

		D3D11_BUFFER_DESC desc{};
		// D3D11_USAGE_DYNAMIC : 동적 (실시간으로 동작) 사용
		desc.Usage = D3D11_USAGE_DYNAMIC;
		// 무조건 16바이트 단위로 사용해야함
		desc.ByteWidth = sizeof(T) + (16 - sizeof(T) % 16);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		return Buffer<T>::Initialize(device, desc);
	}

	bool Update() {
		D3D11_MAPPED_SUBRESOURCE map;
		HRESULT hr = dc->Map(Buffer<T>::buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
		if (FAILED(hr)) {
			Debug::Error(hr, L"콘스탄트 버퍼를 사용 할 수 없습니다.");
			return false;
		}
		CopyMemory(map.pData, &data, sizeof(data));
		dc->Unmap(Buffer<T>::buffer.Get(), 0);
		return true;
	}
};