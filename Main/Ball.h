#pragma once
#include "Point2D.h"

class CBall
{
public:
	CBall(void);
	explicit CBall(CPoint2D const & pos, double r = 10.0);

	CBall UpdatePosition(CPoint2D const & acceleration, double time) const;
	void Render(Microsoft::WRL::ComPtr<ID2D1DeviceContext> & d2dContext) const;

	double GetR() const;
	CPoint2D GetPos() const;

	~CBall(void);
private:
	CPoint2D m_Position;
	CPoint2D m_Velocity;
	double m_Radius;
};

