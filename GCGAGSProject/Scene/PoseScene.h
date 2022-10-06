#pragma once
#include "BaseScene.h"
#include "Vector2.h"

class PoseScene :
	public BaseScene
{
public:
	UNBS Update(UNBS own) override;
	PoseScene();
	PoseScene(UNBS own);
	~PoseScene();
	void Draw()override;
	void SetOwn(UNBS own);
private:
	int firstUpdate();
	void firstDraw();
	int poseUpdate();
	void poseDraw();
	void VolUpdate();
	void VolDraw();
	void BrightUpdate();
	void BrightDraw();
	int screenH_;
	Vector2 screenSize_;
	UNBS ownS_;
	int isTarget_;
	int setingNum_;
	int bright_;
	int tmpbright_;

	int soundVol_;
	int tmpSoundVol_;

	bool playsF_;
	int sterangle_;
	float time_;
	float vstime_;

	int circlePosx_;
};