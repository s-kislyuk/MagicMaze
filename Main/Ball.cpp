#include "pch.h"
#include "Ball.h"

using namespace Windows::Foundation;

CBall::CBall(void)
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
