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

}

void MazeModel::Update( float timeTotal, float timeDelta )
{

}
