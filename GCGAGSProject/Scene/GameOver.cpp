#include <DxLib.h>
#include "GameOver.h"
#include "ImageMng.h"
#include "CronoMng.h"
#include "SoundMng.h"
#include "PadMng.h"
#include "KeyMng.h"
#include "TitleScene.h"
#include "sceneMng.h"

UNBS GameOver::Update(UNBS own)
{
	time_++;
	if (screenSize_.y >= backWPosY_)
	{
		if (screenSize_.y == backWPosY_)
		{
			lpSoundMng.SoundPlay("don.mp3");
		}
		backWPosY_++;
	}
	if (CheckHitKeyAll())
	{
		pressKeyF_ = true;
	}
	if (pressKeyF_)
	{
		sterangle_ = static_cast<int>(time_ * 10) % 360;
		if (sterangle_ > 360)
		{
			sterangle_ = 0;
		}
		if (lpPadMng.GetControllerData(InputID::Right) || lpKeyMng.CheckKeyTrg(KeyBindID::Right))
		{
			lpSoundMng.SoundPlay("botan.mp3");
			isTarget_++;
		}
		if (lpPadMng.GetControllerData(InputID::Left) || lpKeyMng.CheckKeyTrg(KeyBindID::Left))
		{
			lpSoundMng.SoundPlay("botan.mp3");
			isTarget_--;
		}
		if (isTarget_ < 0)
		{
			isTarget_ = 0;
		}
		if (isTarget_ > 1)
		{
			isTarget_ = 1;
		}
		if (lpPadMng.GetControllerData(InputID::BtnB) || lpKeyMng.CheckKeyTrg(KeyBindID::Ok))
		{
			lpSoundMng.SoundPlay("pusbotan.mp3");
			if (isTarget_ == 1)
			{
				Sleep(300);
				lpSceneMng.SetShutdown();
				return own;
			}
			else
			{
				return std::move(std::make_unique<TitleScene>());
			}
		}
	}
	return own;
}

GameOver::GameOver()
{
	Init();
}

GameOver::GameOver(UNBS own)
{
	Init();
	ownS_ = std::move(own);
}

GameOver::~GameOver()
{
	lpImglMng.DeleteGraph("GameOverWall.png");
	lpImglMng.DeleteGraph("GameOver1.png");
	lpImglMng.DeleteGraph("GameOver2.png");
	lpImglMng.DeleteGraph("GameOver3.png");
}

void GameOver::Draw()
{
	ownS_->Draw();
	SetDrawScreen(screenH_);
	ClsDrawScreen();
	//lpImglMng.DrawImg("GameOverWall.png", { -10 + (rand() % 20 - 10),backWPosY_ });
	for (int i = 0; i < 50; i++)
	{
		int id = 0;
		if (i % 3 == 0)
		{
			id = lpImglMng.GetGraphHandle("testC2.png");
		}
		else if (i % 3 == 1)
		{
			id = lpImglMng.GetGraphHandle("testC4.png");
		}
		else
		{
			id = lpImglMng.GetGraphHandle("testC3.png");
		}
		DrawRotaGraph(dropPosAngle_[i].first.x, backWPosY_+ dropPosAngle_[i].first.y, 10.0, dropPosAngle_[i].second, id, true);
	}


	if (screenSize_.y <= backWPosY_)
	{
		if (time_ / 5 % 30 == 29 || time_ / 5 % 30 == 20)
		{
			lpImglMng.DrawImg("GameOver2.png", { rand() % 5 == 0 ? rand() % 10 - 5 : 0,0 });
		}
		else if (time_ / 5 % 30 == 10)
		{
			lpImglMng.DrawImg("GameOver3.png", { rand() % 5 == 0 ? rand() % 10 - 5 : 0,0 });
		}
		else
		{
			lpImglMng.DrawImg("GameOver1.png", { rand() % 10 == 0 ? rand() % 10 - 5 : 0,0 });
		}
		if (time_ / 20 % 3 != 0)
		{
			DrawFormatString(screenSize_.x / 2 - 150, screenSize_.y - 200, 0xffffff, "なにかキーを押してください");
		}
	}
	if(pressKeyF_)
	{
		Vector2 pos;
		DrawBox(screenSize_.x / 2 - 150, screenSize_.y / 2 - 50, screenSize_.x / 2 + 160, screenSize_.y / 2 + 100, 0x121212, true);
		DrawFormatString(screenSize_.x / 2 - 70, screenSize_.y / 2 - 35, 0xffffff, "どうする？");
		pos.x = screenSize_.x / 2 - 100;
		pos.y = screenSize_.y / 2 + 50;

		if (isTarget_ == 0)
		{
			pos.x = screenSize_.x / 2 - 130;
		}

		if (isTarget_ == 1)
		{
			pos.x = screenSize_.x / 2 + 70;
		}
		pos.y += 13;

		DrawRotaGraph(pos.x - 10, pos.y, 1.0, sterangle_, lpImglMng.GetGraphHandle("ster.png"), true);
		//DrawTriangle(pos.x - 20, pos.y - 15, pos.x - 20, pos.y + 15, pos.x, pos.y, 0xffffff, false);

		if (isTarget_ != 0)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
		}
		else
		{
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
		DrawFormatString(screenSize_.x / 2 - 120, screenSize_.y / 2 + 50, 0xffffff, "タイトルへ");
		if (isTarget_ != 1)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
		}
		else
		{
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
		DrawFormatString(screenSize_.x / 2 + 50, screenSize_.y / 2 + 50, 0xffffff, "やめる");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	lpImglMng.ScreenAddDrawQue(screenH_, 79);
}

void GameOver::SetOwn(UNBS own)
{
	ownS_ = std::move(own);
}

void GameOver::Init(void)
{
	lpSoundMng.StopSound("game.mp3");
	lpSoundMng.LoadSound("boon.mp3");
	lpSoundMng.LoadSound("don.mp3");
	lpSoundMng.SoundPlay("boon.mp3");
	isTarget_ = 0;
	sterangle_ = 0;
	pressKeyF_ = false;
	backWPosY_ = 0;
	GetDrawScreenSize(&screenSize_.x, &screenSize_.y);
	screenH_ = MakeScreen(screenSize_.x, screenSize_.y, true);
	lpImglMng.LoadGraph("GameOverWall.png");
	lpImglMng.LoadGraph("GameOver1.png");
	lpImglMng.LoadGraph("GameOver2.png");
	lpImglMng.LoadGraph("GameOver3.png");
	for (int i = 0; i < 50; i++)
	{
		dropPosAngle_.emplace_back(Vector2{ rand() % screenSize_.x ,rand() % 500 - 200 }, rand() % 360);
	}
}
