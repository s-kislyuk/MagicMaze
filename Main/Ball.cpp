#include "pch.h"
#include "Ball.h"
#include <d2d1helper.h>

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

	double d_max_vel = 100;
	CBall res = *this;
	res.m_Velocity += acceleration*time *10;
	if (res.m_Velocity.m_x > d_max_vel)
		res.m_Velocity.m_x = d_max_vel;
	if (res.m_Velocity.m_y > d_max_vel)
		res.m_Velocity.m_y = d_max_vel;
	if (res.m_Velocity.m_x < -d_max_vel)
		res.m_Velocity.m_x = -d_max_vel;
	if (res.m_Velocity.m_y < -d_max_vel)
		res.m_Velocity.m_y = -d_max_vel;

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

void CBall::Render( Microsoft::WRL::ComPtr<ID2D1DeviceContext> & d2dContext ) const
{
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush;
	DX::ThrowIfFailed(d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &brush));
	D2D1_POINT_2F pt = {(float)m_Position.m_x, (float)m_Position.m_y};
	D2D1_ELLIPSE ellipse = {pt, (float)m_Radius, (float)m_Radius};
	d2dContext->FillEllipse(ellipse, brush.Get());
}

void CBall::InvertVelosity( EDir dir )
{
	if (dir == dir_horiz)
		m_Velocity.m_x *= -1;
	else
		m_Velocity.m_y *= -1;
}
