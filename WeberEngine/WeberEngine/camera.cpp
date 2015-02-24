#include "camera.h"

Camera::Camera(D3DXVECTOR3 position, D3DXVECTOR3 viewDirection) 
{
	m_viewDirection = viewDirection;
	m_position = position;
	m_viewMatrix;
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	//movement speed
	m_forwardSpeed = 0.05f;
	m_rotateUpSpeed = 0.0174532925f;
	m_sidewaysSpeed = 0.05f;
	m_yaw = 0.0f;
	m_pitch = 0.0f;
	m_roll = 0.0f;

	updateCamera();
}
Camera::~Camera() {

}

void Camera::SetPosition(float x, float y, float z){
	m_position = D3DXVECTOR3(x, y, z);
}
void Camera::SetRotation(float roll, float pitch, float yaw){
	m_roll = roll;
	m_pitch = pitch;
	m_yaw = yaw;
}

void Camera::setForwardSpeed(float speed) {
	m_forwardSpeed = speed;
}
void Camera::setsidewaySpeed(float speed) {
	m_sidewaysSpeed = speed;
}
void Camera::setRotateUpSpeed(float speed){
	m_rotateUpSpeed = speed;
}

void Camera::moveForward(){
	m_position += m_forwardSpeed * m_viewDirection;
}
void Camera::moveBackward(){
	m_position -= m_forwardSpeed * m_viewDirection;
}
void Camera::moveUp(){
	m_position += m_forwardSpeed * m_up;
}
void Camera::moveDown(){
	m_position -= m_forwardSpeed * m_up;
}
void Camera::moveLeft(){
	m_position -= m_sidewaysSpeed * m_right;
}
void Camera::moveRight(){
	m_position += m_sidewaysSpeed * m_right;
}

void Camera::rotateLeftAroundUp(){
	m_yaw += m_rotateUpSpeed;
}

void Camera::rotateRightAroundUp(){
	m_yaw -= m_rotateUpSpeed;
}

D3DXVECTOR3* Camera::GetPosition(){
	return &m_position;
}
D3DXVECTOR3* Camera::GetViewDirection(){
	return &m_viewDirection;
}
D3DXMATRIX* Camera::GetViewMatrix(){
	return &m_viewMatrix;
}

void Camera::updateCamera(){

	D3DXVECTOR4 view;
	D3DXMATRIX rotationMatrix3, rotationMatrix4;
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix3, m_yaw, m_pitch, m_roll);
	rotationMatrix4 = D3DXMATRIX(rotationMatrix3._11, rotationMatrix3._12, rotationMatrix3._13, 0.0f, rotationMatrix3._21, rotationMatrix3._22, rotationMatrix3._23, 0.0f, rotationMatrix3._31, rotationMatrix3._32, rotationMatrix3._33, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	view = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.0f);
	D3DXVec4Transform(&view, &view, &rotationMatrix4);
	m_viewDirection.x = view.x;
	m_viewDirection.y = view.y;
	m_viewDirection.z = view.z;

	D3DXVECTOR4 right = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.0f);
	D3DXVec4Transform(&right, &right, &rotationMatrix4);
	m_right.x = right.x;
	m_right.y = right.y;
	m_right.z = right.z;

	D3DXVECTOR3 posPlusDir = m_position + m_viewDirection;

	D3DXMatrixLookAtLH(&m_viewMatrix, &m_position, &posPlusDir, &m_up);
}
