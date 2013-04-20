#pragma once
#include "Point2D.h"

class Obstacle
{
public:
	virtual ~Obstacle(void){};
};

class MazeWallObstacle : public Obstacle
{
public:
	MazeWallObstacle(CPoint2D const & pt1, CPoint2D const & pt2);

private:
	CPoint2D m_pt1, m_pt2;
};
