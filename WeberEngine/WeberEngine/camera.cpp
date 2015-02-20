#include "camera.h"

Camera::Camera(D3DXVECTOR3 position, D3DXVECTOR3 viewDirection) 
{
	m_viewDirection = viewDirection;
	m_position = position;
	m_viewMatrix;
	m_up = D3DXVECTOR3(0.f, 1.f, 0.f);
	m_right = D3DXVECTOR3(1.f, 0.f, 0.f);

	//movement speed
	m_forwardSpeed = 0.5f;
	m_rotateUpSpeed = 0.5f;
	m_sidewaysSpeed = 0.5f;
	m_yaw = 0.f;
	m_pitch = 0.f;
	m_roll = 0.f;

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
	m_yaw -= m_rotateUpSpeed;
}

void Camera::rotateRightAroundUp(){
	m_yaw += m_rotateUpSpeed;
}

D3DXVECTOR3 Camera::GetPosition(){
	return m_position;
}
D3DXVECTOR3 Camera::GetViewDirection(){
	return m_viewDirection;
}
D3DXMATRIX Camera::GetViewMatrix(){
	return m_viewMatrix;
}

void Camera::updateCamera(){

	D3DXMATRIX *camToWorld = new D3DXMATRIX();
	D3DXMatrixTranslation(camToWorld, m_position[0], m_position[1], m_position[2]);
	D3DXMatrixRotationY(camToWorld, m_yaw);
	D3DXMatrixRotationX(camToWorld, m_pitch);
	
	m_viewDirection[0] = -camToWorld->_31;
	m_viewDirection[1] = -camToWorld->_32;
	m_viewDirection[2] = -camToWorld->_33;

	D3DXMatrixInverse(camToWorld, NULL, camToWorld);
	m_viewMatrix = *camToWorld;

	m_right[0] = m_viewMatrix._11;
	m_right[1] = m_viewMatrix._12;
	m_right[2] = m_viewMatrix._13;

	m_up[0] = m_viewMatrix._21;
	m_up[1] = m_viewMatrix._22;
	m_up[2] = m_viewMatrix._23;

	delete(camToWorld);
}
