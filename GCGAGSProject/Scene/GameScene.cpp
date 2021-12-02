#include <time.h>
#include <DxLib.h>
#include <vector>
#include <memory>
#include "GameScene.h"
#include "SceneMng.h"
#include "ImageMng.h"
#include "UIMng.h"
#include "MoneyMng.h"
#include "PadMng.h"
#include "PoseScene.h"
#include "CronoMng.h"
#include "UIStartPlay.h"
#include "UIBackPlay.h"

GameScene::GameScene()
{
	srand((unsigned)time(NULL));
	scnID_ = SCN_ID::SCN_GAME;
	lpImglMng.LoadGraph("MapBack.png");
	lpImglMng.LoadGraph("wood.png");
	lpImglMng.LoadGraph("Monster.png");
	lpImglMng.LoadGraph("testC2.png");
	lpImglMng.LoadGraph("testC3.png");
	lpImglMng.LoadGraph("testC4.png");
	lpImglMng.LoadGraph("fire.png");
	lpImglMng.LoadGraph("dfire.png");
	lpImglMng.LoadGraph("gate.png");
	lpImglMng.LoadGraph("ring1.png");
	lpImglMng.LoadGraph("ring2.png");
	lpImglMng.LoadGraph("mouse.png");
	lpImglMng.LoadGraph("frame.png");
	lpImglMng.LoadGraph("player.png");

	roadTime_ = std::make_unique<RoadTime>(0);
	mapSelect_ = std::make_unique<MapSelect>();
	gamePlay_ = std::make_unique<PlayMode>();
	mapSelect_->SetStageID(0);
	roadCount_ = 0;
	time_ = 0;
	roadFinishF_ = false;
	isGameNow_ = false;
	startGame_ = false;
}

UNBS GameScene::Update(UNBS own)
{
	if (lpPadMng.GetControllerData(InputID::Menu))
	{
		return std::move(std::make_unique<PoseScene>(std::move(own)));
	}
	if (!roadFinishF_)
	{
		RoadNow(lpCronoMng.GetDeltaTime());
	}
	else
	{
		lpMoneyMng.Update();
		GameNow(lpCronoMng.GetDeltaTime());
	}
	time_ += lpCronoMng.GetDeltaTime();
	return std::move(own);
}

GameScene::~GameScene()
{
	lpImglMng.DeleteGraph("MapBack.png");
	lpImglMng.DeleteGraph("Monster.png");
	lpImglMng.DeleteGraph("testC2.png");
	lpImglMng.DeleteGraph("testC3.png");
	lpImglMng.DeleteGraph("testC4.png");
	lpImglMng.DeleteGraph("fire.png");
	lpImglMng.DeleteGraph("dfire.png");
	lpImglMng.DeleteGraph("testP.png");
	lpImglMng.DeleteGraph("gate.png");
	lpImglMng.DeleteGraph("ring1.png");
	lpImglMng.DeleteGraph("ring2.png");
	lpImglMng.DeleteGraph("frame.png");
	lpImglMng.DeleteGraph("player.png");
}

void GameScene::Draw()
{
	if (!roadFinishF_)
	{
		roadTime_->Draw(lpCronoMng.GetDeltaTime());
		return;
	}
	if (!isGameNow_)
	{
		lpMoneyMng.Draw();
		mapSelect_->Draw(lpCronoMng.GetDeltaTime());
		return;
	}
	gamePlay_->Draw();
}

void GameScene::RoadNow(float deltaTime)
{
	if (roadCount_ / 2 % 2 != 0)
	{
		Vector2 tpos = { 15,25 + 600 };
		Vector2 tsize = { 100,50 };
		lpUIMng.CreateUI(std::move<>(std::make_unique<UIStartPlay>(tpos, tsize)));
		roadCount_ = -1;
		roadFinishF_ = true;
		return;
	}
	roadTime_->Update(deltaTime);
	roadCount_ = static_cast<int>(time_);
}

void GameScene::GameNow(float deltaTime)
{
	if (lpMoneyMng.GetStartFlag())
	{
		if (!isGameNow_)
		{
			gamePlay_->SetMapDate(mapSelect_->GetMapdate()); 
			gamePlay_->CheckGoal();
			if (gamePlay_->IsCheckClear())
			{
				srand(static_cast<unsigned int>(time(NULL)));
				lpUIMng.DeleteAllUI();
				roadFinishF_ = false;
				roadCount_ = 0;
				startGame_ = false; isGameNow_;
				isGameNow_ = true;
				roadTime_->Init(0);
				return;
			}
			else
			{
				SetMouseDispFlag(true);
				MessageBox(NULL, "ドアとゴールがつながっていますか？ \nOKをクリックしてください", "ゴールにたどり着けません！", MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
				SetMouseDispFlag(false);
				lpMoneyMng.SetStartFlag(false);
			}
		}
	}
	if (!isGameNow_)
	{
		mapSelect_->Update(deltaTime);
		return;
	}
	else
	{
		if (!startGame_)
		{
			lpUIMng.DeleteAllUI();
			startGame_ = true;
			gamePlay_->Init();
			Vector2 tpos = { 15,25 + 600 };
			Vector2 tsize = { 100,50 };
			lpUIMng.CreateUI(std::move<>(std::make_unique<UIBackPlay>(tpos, tsize)));
			srand((unsigned)time(NULL));
			roadCount_ = 0;
		}

		gamePlay_->Update();
		if (!lpMoneyMng.GetStartFlag())
		{
			lpUIMng.DeleteAllUI();
			mapSelect_->Init();
			Vector2 tpos = { 15,25 + 600 };
			Vector2 tsize = { 100,50 };
			lpUIMng.CreateUI(std::move<>(std::make_unique<UIStartPlay>(tpos, tsize)));
			lpMoneyMng.SetStartFlag(false);
			isGameNow_ = false;
			roadCount_ = 0;
			roadTime_->Init(0);
		}
	}
}