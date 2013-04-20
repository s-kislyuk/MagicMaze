#pragma once

class CBall
{
public:
	CBall(void);

	CBall UpdatePosition(Windows::Foundation::Point const & acceleration, double time) const;

	~CBall(void);
private:
	Windows::Foundation::Point m_Position;
	Windows::Foundation::Point m_velocity;
};

