#pragma once
struct CPoint2D
{
	CPoint2D();
	CPoint2D(double x, double y);

	CPoint2D operator*(double d) const;
	CPoint2D operator+ (CPoint2D const & point) const;
	CPoint2D operator- (CPoint2D const & point) const;

	CPoint2D operator+= (CPoint2D const & point);
	CPoint2D operator-= (CPoint2D const & point);


	double m_x;
	double m_y;
};

