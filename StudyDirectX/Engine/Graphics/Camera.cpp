#include "Camera.h"

void Camera::UpdateView()
{
	XMMATRIX matRot = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
	XMVECTOR eyeDir = XMVector3TransformNormal(DEFAULT_FORWARD_VECTOR, matRot);
	XMVECTOR eyeFocus = vPos + eyeDir;
	XMVECTOR eyeUp = XMVector3TransformNormal(DEFAULT_UP_VECTOR, matRot);
	view = XMMatrixLookAtLH(vPos, eyeFocus, eyeUp);
}

Camera::Camera()
{
	SetPos(0, 0, 0);
	SetRot(0, 0, 0);
}

Camera::Camera(float x, float y, float z)
{
	SetPos(x, y, z);
	SetRot(0, 0, 0);
}

void Camera::SetProjection(float fov, float aspect, float near, float far)
{
	//투영행렬
	//LH:왼손좌표계 사용, 언리얼과 유니티의 좌표계가 다른 이유, 다이렉트X는 LH 사용
	float rad = (fov / 360.0f) * XM_2PI; //라디안 = 2pi * (각도) / 360
	proj = XMMatrixPerspectiveFovLH(rad, aspect, near, far);
}

const XMMATRIX& Camera::GetViewMatrix() const
{
	return view;
}

const XMMATRIX& Camera::GetProjectionMatrix() const
{
	return proj;
}

const XMMATRIX& Camera::GetViewProjection() const
{
	return view * proj;
}

const XMVECTOR& Camera::GetPosVector() const
{
	return vPos;
}

const XMFLOAT3& Camera::GetPos() const
{
	return pos;
}

const XMVECTOR& Camera::GetRotVector() const
{
	return vRot;
}

const XMFLOAT3& Camera::GetRot() const
{
	return rot;
}

void Camera::SetPos(const XMVECTOR& posVec)
{
	vPos = posVec;
	XMStoreFloat3(&pos, vPos);
	UpdateView();
}

void Camera::SetPos(float x, float y, float z)
{
	pos = { x,y,z };
	vPos = XMLoadFloat3(&pos);
	UpdateView();
}

void Camera::SetPos(const XMFLOAT3& pos)
{
	SetPos(pos.x, pos.y, pos.z);
}

void Camera::Translate(const XMVECTOR& deltaVec)
{
	vPos += deltaVec;
	XMStoreFloat3(&pos, vPos);
	UpdateView();
}

void Camera::Translate(float x, float y, float z)
{
	pos.x += x;
	pos.y += y;
	pos.z += z;
	vPos = XMLoadFloat3(&pos);
	UpdateView();
}

void Camera::Translate(const XMFLOAT3& delta)
{
	Translate(delta.x, delta.y, delta.z);
}

void Camera::SetRot(const XMVECTOR& rotVec)
{
	vRot = rotVec;
	XMStoreFloat3(&rot, vRot);
	UpdateView();
}

void Camera::SetRot(float x, float y, float z)
{
	rot = { x,y,z };
	vRot = XMLoadFloat3(&rot);
	UpdateView();
}

void Camera::SetRot(const XMFLOAT3& rot)
{
	SetRot(rot.x, rot.y, rot.z);
}

void Camera::Rotate(const XMVECTOR& deltaVec)
{
	vRot += deltaVec;
	XMStoreFloat3(&rot, vRot);
	UpdateView();
}

void Camera::Rotate(float x, float y, float z)
{
	rot.x += x;
	rot.y += y;
	rot.z += z;
	vRot = XMLoadFloat3(&rot);
	UpdateView();
}

void Camera::Rotate(const XMFLOAT3& rot)
{
	Rotate(rot.x, rot.y, rot.z);
}
