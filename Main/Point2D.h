#pragma once
struct CPoint2D
{
	CPoint2D();
	CPoint2D(double x, double y);

	void operator*(double d);
	void operator+ (CPoint2D const & point);


	double m_x;
	double m_y;
};

