#pragma once
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
};

