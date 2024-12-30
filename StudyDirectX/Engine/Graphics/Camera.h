#pragma once
#include <DirectXMath.h>
using namespace DirectX;

class Camera {
	XMFLOAT3 pos, rot;
	XMVECTOR vPos, vRot; //병렬 프로그래밍을 위한 변수, x,y,z값을 동시에 연산
	XMMATRIX view, proj;

	const XMVECTOR DEFAULT_FORWARD_VECTOR = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const XMVECTOR DEFAULT_UP_VECTOR = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	const XMVECTOR DEFAULT_RIGHT_VECTOR = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	void UpdateView();

public:
	Camera();
	Camera(float x, float y, float z);

	void SetProjection(float fov, float aspect, float near, float far);

	const XMMATRIX& GetViewMatrix() const;
	const XMMATRIX& GetProjectionMatrix() const;
	const XMMATRIX& GetViewProjection() const;

	const XMVECTOR& GetPosVector() const;
	const XMFLOAT3& GetPos() const;

	const XMVECTOR& GetRotVector() const;
	const XMFLOAT3& GetRot() const;

	void SetPos(const XMVECTOR& posVec);
	void SetPos(float x, float y, float z);
	void SetPos(const XMFLOAT3& pos);

	void Translate(const XMVECTOR& deltaVec);
	void Translate(float x, float y, float z);
	void Translate(const XMFLOAT3& delta);

	void SetRot(const XMVECTOR& rotVec);
	void SetRot(float x, float y, float z);
	void SetRot(const XMFLOAT3& rot);

	void Rotate(const XMVECTOR& deltaVec);
	void Rotate(float x, float y, float z);
	void Rotate(const XMFLOAT3& rot);
};