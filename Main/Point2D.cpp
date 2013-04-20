#include "pch.h"
#include "Point2D.h"


CPoint2D::CPoint2D(void)
	:m_x(0),
	m_y(0)
{
}

CPoint2D::CPoint2D( double x, double y )
	:m_x(x),
	m_y(y)
{
	
}

void CPoint2D::operator*( double d )
{
	m_x *= d;
	m_y *= d;
}

void CPoint2D::operator+( CPoint2D const & point )
{
	m_x += point.m_x;
	m_y += point.m_y;
}


