#include "pch.h"
#include "Ball.h"

using namespace Windows::Foundation;

CBall::CBall(void)
{
}

CBall::CBall( CPoint2D const & pos, double r /*= 10.0*/ ) : m_Position(pos), m_Radius(r)
{

}


CBall::~CBall(void)
{
}

CBall CBall::UpdatePosition( CPoint2D const & acceleration , double time) const
{
	CBall res = *this;
	res.m_Velocity += acceleration*time;

	res.m_Position += res.m_Velocity*time;
	return res;

}

double CBall::GetR() const
{
	return m_Radius;
}

CPoint2D CBall::GetPos() const
{
	return m_Position;
}
