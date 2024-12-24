#pragma once
#include <DirectXMath.h>
using namespace DirectX;

struct Vertex {
	XMFLOAT3 pos;
	XMFLOAT4 color;
	XMFLOAT2 uv;
	Vertex() : pos(0, 0, 0), color(1, 1, 1, 1), uv(0, 0) {}
	Vertex(XMFLOAT3 pos) : pos(pos), color(1, 1, 1, 1), uv(0, 0) {}
	Vertex(XMFLOAT3 pos, XMFLOAT4 color) :pos(pos), color(color), uv(0, 0) {}
	Vertex(XMFLOAT3 pos, XMFLOAT4 color, XMFLOAT2 uv) :pos(pos), color(color), uv(uv) {}
};