#include "pch.h"
#include "MazeModel.h"
#include "Point2D.h"


MazeModel::MazeModel(Windows::Foundation::Rect const & bounds)
{
	CPoint2D const pt1(0, 0), pt2(0, bounds.Width), pt3(bounds.Height, bounds.Width), pt4(bounds.Height, 0);
	m_obstacles.push_back(std::make_shared<MazeWallObstacle>(pt1, pt2));
	m_obstacles.push_back(std::make_shared<MazeWallObstacle>(pt2, pt3));
	m_obstacles.push_back(std::make_shared<MazeWallObstacle>(pt3, pt4));
	m_obstacles.push_back(std::make_shared<MazeWallObstacle>(pt4, pt1));

	m_ball = CBall((pt1+pt3)*0.5);
}


MazeModel::~MazeModel(void)
{
}

void MazeModel::Render( Microsoft::WRL::ComPtr<ID2D1DeviceContext> & d2dContext )
{
	m_ball.Render(d2dContext);
	for(auto obstacle : m_obstacles)
		obstacle->Render(d2dContext);
}

void MazeModel::Update(CPoint2D const & accel, float timeDelta )
{
	CBall newBall = m_ball.UpdatePosition(accel, timeDelta);
	for (size_t i = 0; i<m_obstacles.size(); ++i)
	{
		if (m_obstacles[i]->IsIntersect(newBall))
		{
			if (m_obstacles[i]->GetDir() == Obstacle::dir_horiz);
		}
	}
}
