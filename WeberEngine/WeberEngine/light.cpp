#include "light.h"


Light::Light(D3DXVECTOR3 position, D3DXVECTOR3 direction, D3DXVECTOR4 color)
{
	m_position = position;
	m_direction = direction;
	m_color = color;
}

Light::~Light()
{
}

D3DXVECTOR3 Light::getDirection() {
	return m_direction;
}
D3DXVECTOR3 Light::getPosition() {
	return m_position;
}
D3DXVECTOR4 Light::getColor() {
	return m_color;
}
void Light::setDirection(D3DXVECTOR3 direction) {
	m_direction = direction;
}
void Light::setPosition(D3DXVECTOR3 position) {
	m_position = position;
}
void Light::setColor(D3DXVECTOR4 color) {
	m_color = color;
}
