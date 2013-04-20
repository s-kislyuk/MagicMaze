#pragma once
class MazeModel
{
public:
	MazeModel(void);
	~MazeModel(void);
	
	void Render(Microsoft::WRL::ComPtr<ID2D1DeviceContext> & d2dContext);
	void Update(float timeTotal, float timeDelta);

private:

};

