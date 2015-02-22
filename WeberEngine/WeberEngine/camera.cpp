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

	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, m_yaw, m_pitch, m_roll);
	
	m_viewDirection = D3DXVECTOR3(0.f, 0.f, 1.f);
	m_up = D3DXVECTOR3(0.f, 1.f, 0.f);

	D3DXVec3TransformCoord(&m_viewDirection, &m_viewDirection, &rotationMatrix);
	D3DXVec3TransformCoord(&m_up, &m_up, &rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	m_viewDirection = m_position + m_viewDirection;

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&m_viewMatrix, &m_position, &m_viewDirection, &m_up);
}
