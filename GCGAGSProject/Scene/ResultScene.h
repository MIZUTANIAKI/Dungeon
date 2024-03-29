#pragma once
#include "BaseScene.h"
#include "Vector2.h"
class ResultScene :
    public BaseScene
{
public:
	UNBS Update(UNBS own) override;
	ResultScene();
	ResultScene(UNBS own);
	~ResultScene();
	void Draw()override;
	void DrawName();
	void SetOwn(UNBS own);
private:
	void Init(void);
	int screenH_;
	Vector2 screenSize_;
	UNBS ownS_;
	int isTarget_;
	float time_;
	int sterangle_;
	int resultNum_;

	int resultMoney_;

	float graphY_;
	float graphSpeedY_;

	int paVal_;
};

