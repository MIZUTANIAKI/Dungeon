#pragma once
#include "BaseScene.h"
#include "Vector2.h"
#include "RoadTime.h"
#include "MapSelect.h"
#include "PlayMode.h"

class ExampleMap;

class GameScene :
	public BaseScene
{
public:
	UNBS Update(UNBS own) override;
	GameScene();
	~GameScene();
	void Draw()override;
private:
	void RoadNow(float deltaTime);
	void GameNow(float deltaTime);

	std::unique_ptr<RoadTime> roadTime_;
	std::unique_ptr<MapSelect> mapSelect_;
	std::unique_ptr<PlayMode> gamePlay_;
	int roadCount_;
	float time_;

	bool roadFinishF_;
	bool isGameNow_;
};
