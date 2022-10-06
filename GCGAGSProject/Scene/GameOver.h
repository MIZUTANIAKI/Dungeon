#pragma once
#include <vector>
#include "BaseScene.h"
#include "Vector2.h"
class GameOver :
    public BaseScene
{
public:
	UNBS Update(UNBS own) override;
	GameOver();
	GameOver(UNBS own);
	~GameOver();
	void Draw()override;
	void SetOwn(UNBS own);
private:
	void Init(void);
	int screenH_;
	Vector2 screenSize_;
	UNBS ownS_;
	int isTarget_;
	int backWPosY_;
	int time_;
	float sterangle_;
	bool pressKeyF_;

	bool dropF_;

	float count_;

	std::vector<std::pair<std::pair<Vector2flt,int>, std::pair<int,float>>> dropPosAngle_;		//座標、「角度、速度」
	std::vector<bool> dropFVector_;
	std::vector<int> dropSoundVector_;

};

