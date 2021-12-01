#pragma once
#include "Vector2.h"

class RoadTime
{
public:
	RoadTime(int num);
	~RoadTime();

	void Update(float deltaTime);

	void Draw(float deltaTime);
	void Init(int num);

private:
	int screenH_;
	Vector2 screenSize_;

	float rsita_;
	float time_;
};
