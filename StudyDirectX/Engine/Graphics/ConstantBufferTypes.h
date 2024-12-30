#pragma once
#include <DirectXMath.h>
using namespace DirectX;

//cbuffer Transform : register(b0)
//{
//    float2 Offset;
//}

//셰이더의 cbuffer와 동일한 구조여야함
struct CB_VS_Transform {
	XMFLOAT2 Offset;
};

struct CB_VS_VIEWPROJ {
	XMMATRIX viewProj;
};