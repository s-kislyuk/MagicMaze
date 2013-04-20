#pragma once
#include "Point2D.h"

class CBall
{
public:
	CBall(void);

	CBall UpdatePosition(CPoint2D const & acceleration, double time) const;

	~CBall(void);
private:
	CPoint2D m_Position;
	CPoint2D m_Velocity;
	double m_Radius;
};

