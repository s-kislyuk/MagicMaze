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

CPoint2D CPoint2D::operator*( double d ) const
{
	CPoint2D res(*this);
	res.m_x *= d;
	res.m_y *= d;
	return res;
}

CPoint2D CPoint2D::operator+( CPoint2D const & point ) const
{
	CPoint2D res(*this);
	res.m_x += point.m_x;
	res.m_y += point.m_y;
	return res;
}
CPoint2D CPoint2D::operator-( CPoint2D const & point ) const
{
	CPoint2D res(*this);
	res.m_x -= point.m_x;
	res.m_y -= point.m_y;
	return res;
}

CPoint2D CPoint2D::operator+=( CPoint2D const & point )
{
	(*this) = (*this)+point;
	return *this;
}

CPoint2D CPoint2D::operator-=( CPoint2D const & point )
{
	(*this) = (*this)-point;
	return *this;
}


