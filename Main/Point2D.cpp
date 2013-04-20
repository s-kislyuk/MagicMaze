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

double CPoint2D::SquareDistTo( CPoint2D const & pt ) const
{
	CPoint2D const & p = *this - pt;
	return DotProduct(p, p);
}

double CPoint2D::DistTo( CPoint2D const & pt ) const
{
	double const squareDist = SquareDistTo(pt);
	return sqrt(squareDist);
}

double DotProduct( CPoint2D const & pt1, CPoint2D const & pt2 )
{
	return pt1.m_x * pt2.m_x + pt1.m_y * pt2.m_y;
}

double CrossProduct( CPoint2D const & pt1, CPoint2D const & pt2 )
{
	return pt1.m_x * pt2.m_y - pt1.m_y * pt2.m_x;
}
