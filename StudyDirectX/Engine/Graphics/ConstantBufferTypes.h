#pragma once
#include <DirectXMath.h>
using namespace DirectX;

//cbuffer Transform : register(b0)
//{
//    float2 Offset;
//}

//���̴��� cbuffer�� ������ ����������
struct CB_VS_Transform {
	XMFLOAT2 Offset;
};

struct CB_VS_VIEWPROJ {
	XMMATRIX viewProj;
};