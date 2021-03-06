#include "pch.h"
#include "Obstacles.h"
#include "Ball.h"


MazeWallObstacle::MazeWallObstacle( CPoint2D const & pt1, CPoint2D const & pt2 )
	:m_pt1(pt1), m_pt2(pt2), m_dir(dir_error) 
{
	m_length = m_pt1.DistTo(m_pt2);
	if (m_length == 0)
		throw new std::exception("Bad maze wall!");
}

MazeWallObstacle::MazeWallObstacle( CPoint2D const & pt1, EDir dir, double dLength )
	:m_pt1(pt1),
	m_dir(dir)
{
	CPoint2D pt(pt1);
	if (dir == dir_horiz)
		pt.m_x += dLength;
	else 
		pt.m_y += dLength;
	m_pt2 = pt;
	m_length = m_pt1.DistTo(m_pt2);
}

bool MazeWallObstacle::IsIntersect( CBall const & ball ) const
{
	CPoint2D const & pt = ball.GetPos();
	double const r = ball.GetR();

	double const sqrR = r * r;
	if (m_pt1.SquareDistTo(pt) < sqrR || m_pt2.SquareDistTo(pt) < sqrR)
		return true;

	double const h = 0.5 * fabs(CrossProduct(m_pt1 - pt, m_pt2 - pt)) / m_length;
	if (h >= r)
		return false;

	double const projection = DotProduct(pt - m_pt1, m_pt2 - m_pt1) / m_length;
	if (projection < 0 || projection > m_length)
		return false;

	return true;
}

void MazeWallObstacle::Render( Microsoft::WRL::ComPtr<ID2D1DeviceContext> & d2dContext ) const
{
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush;
	DX::ThrowIfFailed(d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &brush));
	D2D1_POINT_2F const pt1 = {(float)m_pt1.m_x, (float)m_pt1.m_y};
	D2D1_POINT_2F const pt2 = {(float)m_pt2.m_x, (float)m_pt2.m_y};

	d2dContext->DrawLine(pt1, pt2, brush.Get());
}