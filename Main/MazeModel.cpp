#include "pch.h"
#include "MazeModel.h"
#include "Point2D.h"


MazeModel::MazeModel(Windows::Foundation::Rect const & bounds)
{
	CPoint2D const pt1(0, 0);
	CPoint2D const pt2(0, bounds.Width);
	CPoint2D const pt3(bounds.Height, bounds.Width);
	CPoint2D const pt4(bounds.Height, 0);
	m_obstacles.push_back(std::make_shared<MazeWallObstacle>(pt1, dir_horiz, bounds.Width));
	m_obstacles.push_back(std::make_shared<MazeWallObstacle>(pt1, dir_vert, bounds.Height));
	m_obstacles.push_back(std::make_shared<MazeWallObstacle>(pt2, dir_vert, bounds.Height));
	m_obstacles.push_back(std::make_shared<MazeWallObstacle>(pt4, dir_horiz, bounds.Width));

	srand(56);
	

	
	for (int i =0; i < 30; ++i)
	{
		CPoint2D pt(rand()%(int)(bounds.Width), rand()%(int)(bounds.Height));

		m_obstacles.push_back(std::make_shared<MazeWallObstacle>(pt, rand()%2 == 1 ? dir_vert: dir_horiz, rand()%30 *20));
	}

	m_ball = CBall((pt1+pt3)*0.5);

	m_exit = CBall(CPoint2D(20,20));
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

MazeModel::EUpdateResult MazeModel::Update(CPoint2D const & accel, float timeDelta )
{
	CBall newBall = m_ball.UpdatePosition(accel, timeDelta);
	if (newBall.GetPos().DistTo(m_exit.GetPos()))
		return res_Victory;
	for (size_t i = 0; i<m_obstacles.size(); ++i)
	{
		if (m_obstacles[i]->IsIntersect(newBall))
		{
			newBall.InvertVelosity(m_obstacles[i]->GetDir() == dir_horiz ? dir_vert: dir_horiz);
		}
	}
	m_ball = newBall;
	return res_NothigInteresting;
}
