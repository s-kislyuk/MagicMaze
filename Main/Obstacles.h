#pragma once
#include "Point2D.h"

class CBall;

class Obstacle
{
public:
	virtual ~Obstacle(void){};

	virtual bool IsIntersect(CBall const & ball) const = 0;
	virtual void Render(Microsoft::WRL::ComPtr<ID2D1DeviceContext> & d2dContext) const = 0;
};

class MazeWallObstacle : public Obstacle
{
public:
	MazeWallObstacle(CPoint2D const & pt1, CPoint2D const & pt2);

	virtual bool IsIntersect( CBall const & ball ) const;
	virtual void Render( Microsoft::WRL::ComPtr<ID2D1DeviceContext> & d2dContext ) const;

private:
	CPoint2D m_pt1, m_pt2;
	double m_length;
};
