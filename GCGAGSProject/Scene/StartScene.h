#pragma once
#include <array>
#include <utility>
#include "BaseScene.h"

class StartScene :
    public BaseScene
{
public:
	UNBS Update(UNBS own) override;
	StartScene();
	StartScene(UNBS own);
	void Init();
	~StartScene();
	void Draw()override;
private:
	float time_;
	int atenNum_;
	std::array<float, 5> graphPos_;
	std::array<int, 5> graphAlpha_;
	int screenH_;
	Vector2 screenSize_;
	int maskHandle_;
	int maskHandle1_;
	int maskHandle2_;
	Vector2 maskPos1_;
	Vector2 maskPos2_;
};

