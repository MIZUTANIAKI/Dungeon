#pragma once
#include "BaseScene.h"
#include "Vector2.h"

class TitleScene :
	public BaseScene
{
public:
	UNBS Update(UNBS own) override;
	TitleScene();
	~TitleScene();
	void Draw()override;
private:
	int title1Update();
	void title1Draw();
	int title2Update();
	void title2Draw();

	int titleNum_;
	int tmptitleNum_;

	int screenH_;
	Vector2 screenSize_;

	int isTarget_;

	int changeCount_;
	int sterangle_;
	float time_;

	int maskHandle_;

	Vector2 maskPos1_;
	Vector2 maskPos2_;
};
