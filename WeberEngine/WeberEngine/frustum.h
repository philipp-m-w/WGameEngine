#pragma once

#include <d3dx10math.h>

class Frustum
{
public:
	Frustum();
	~Frustum();

	void ConstructFrustum(float screenDepth, D3DXMATRIX projectionMatrix, D3DXMATRIX viewMatrix);
	
	bool CheckBB(D3DXVECTOR3 minPoint, D3DXVECTOR3 maxPoint);
	bool CheckPoint(D3DXVECTOR3 point);
private:
	D3DXPLANE m_planes[6];
};

