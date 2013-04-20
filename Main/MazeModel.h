#pragma once
#include "Obstacles.h"
class MazeModel
{
public:
	MazeModel(void);
	~MazeModel(void);
	
	void Render(Microsoft::WRL::ComPtr<ID2D1DeviceContext> & d2dContext);
	void Update(float timeTotal, float timeDelta);

private:
	std::vector<std::shared_ptr<Obstacle> > m_obstacles;
};

