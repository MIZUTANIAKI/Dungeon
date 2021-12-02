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
	~StartScene();
	void Draw()override;
private:
	float time_;
	int atenNum_;
	std::array<float, 5> graphPos_;
};

