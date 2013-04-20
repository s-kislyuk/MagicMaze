#include "pch.h"
#include "Ball.h"

using namespace Windows::Foundation;

CBall::CBall(void)
{
}


CBall::~CBall(void)
{
}

CBall CBall::UpdatePosition( Windows::Foundation::Point const & acceleration , double time) const
{
	CBall res = *this;
	res.m_velocity.X += acceleration.X*time;
	res.m_velocity.Y += acceleration.Y*time;

	res.m_Position.X += res.m_velocity.X * time;
	res.m_Position.Y += res.m_velocity.X * time;
	return res;

}
