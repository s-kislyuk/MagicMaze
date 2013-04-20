#pragma once
#include "Obstacles.h"
#include "Ball.h"

class MazeModel
{
public:
	enum EUpdateResult
	{
		res_Victory,
		res_NothigInteresting,
		res_Lose
	};

	MazeModel() {}
	explicit MazeModel(Windows::Foundation::Rect const & bounds);
	~MazeModel(void);
	
	void Render(Microsoft::WRL::ComPtr<ID2D1DeviceContext> & d2dContext);
	EUpdateResult Update(CPoint2D const & accel, float timeDelta);

private:
	std::vector<std::shared_ptr<Obstacle> > m_obstacles;
	CBall m_ball;

	CBall m_exit;
};

