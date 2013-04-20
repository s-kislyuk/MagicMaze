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

	double SquareDistTo(CPoint2D const & pt) const;
	double DistTo(CPoint2D const & pt) const;

	double m_x;
	double m_y;
};

double DotProduct(CPoint2D const & pt1, CPoint2D const & pt2);
double CrossProduct(CPoint2D const & pt1, CPoint2D const & pt2);
