#pragma once

#include <d3dx10math.h>

class Light
{
public:
	Light(D3DXVECTOR3 position, D3DXVECTOR3 direction, D3DXVECTOR4 color);
	~Light();
	D3DXVECTOR3 getDirection();
	D3DXVECTOR3 getPosition();
	D3DXVECTOR4 getColor();
	void setDirection(D3DXVECTOR3 direction);
	void setPosition(D3DXVECTOR3 position);
	void setColor(D3DXVECTOR4 color);
private:
	D3DXVECTOR4 m_color;
	D3DXVECTOR3 m_direction;
	D3DXVECTOR3 m_position;
};

