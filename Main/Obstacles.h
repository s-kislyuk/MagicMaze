#pragma once
#include "Point2D.h"

class CBall;

class Obstacle
{
public:
	virtual ~Obstacle(void){};

	virtual bool IsIntersect(CBall const & ball) const = 0;
};

class MazeWallObstacle : public Obstacle
{
public:
	MazeWallObstacle(CPoint2D const & pt1, CPoint2D const & pt2);

	virtual bool IsIntersect( CBall const & ball ) const;

private:
	CPoint2D m_pt1, m_pt2;
	double m_length;
};
