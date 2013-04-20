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
	enum EDir
	{
		dir_vert,
		dir_horiz,
		dir_error
	};

	MazeWallObstacle(CPoint2D const & pt1, CPoint2D const & pt2);

	MazeWallObstacle(CPoint2D const & pt1, EDir dir, double dLength);

	virtual bool IsIntersect( CBall const & ball ) const;

private:
	CPoint2D m_pt1, m_pt2;
	EDir m_dir;
	double m_length;
};
