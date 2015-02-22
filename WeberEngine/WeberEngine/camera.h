#pragma once
#include <d3dx10math.h>

class Camera
{
public:
	//set per Default as (0,0,-10) ,(0,0,1)
	Camera(D3DXVECTOR3 position, D3DXVECTOR3 viewDirection);
	~Camera();

	void SetPosition(float x, float y, float z);
	void SetRotation(float roll, float pitch, float yaw);
	void setForwardSpeed(float speed);
	void setsidewaySpeed(float speed);
	void setRotateUpSpeed(float speed);

	void moveForward();
	void moveBackward();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	void rotateLeftAroundUp();
	void rotateRightAroundUp();

	D3DXVECTOR3* GetPosition();
	D3DXVECTOR3* GetViewDirection();
	D3DXMATRIX* GetViewMatrix();

	void updateCamera();
private:
	D3DXMATRIX m_viewMatrix;
	D3DXVECTOR3 m_up;
	D3DXVECTOR3 m_right;
	D3DXVECTOR3 m_viewDirection;
	D3DXVECTOR3 m_position;

	//movement speed
	float m_forwardSpeed;
	float m_sidewaysSpeed;
	float m_rotateUpSpeed;
	float m_yaw, m_pitch, m_roll;
};

