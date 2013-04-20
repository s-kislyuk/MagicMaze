#pragma once
#include "Point2D.h"
#include "Direction.h"

class CBall;

class Obstacle
{
public:


	virtual ~Obstacle(void){};

	virtual bool IsIntersect(CBall const & ball) const = 0;
	virtual void Render(Microsoft::WRL::ComPtr<ID2D1DeviceContext> & d2dContext) const = 0;
	virtual EDir GetDir() const  = 0;
};



class MazeWallObstacle : public Obstacle
{
public:
	

	MazeWallObstacle(CPoint2D const & pt1, CPoint2D const & pt2);

	MazeWallObstacle(CPoint2D const & pt1, EDir dir, double dLength);

	virtual bool IsIntersect( CBall const & ball ) const;
	void Render( Microsoft::WRL::ComPtr<ID2D1DeviceContext> & d2dContext ) const;

	EDir GetDir() const {return m_dir;}
private:
	CPoint2D m_pt1, m_pt2;
	EDir m_dir;
	double m_length;
};
