#include <DxLib.h>
#include "ImageMng.h"
#include "TitleScene.h"
#include "PoseScene.h"
#include "GameScene.h"
#include "PadMng.h"
#include "sceneMng.h"
#include "soundMng.h"
#include "MoneyMng.h"
#include "MouseMng.h"

UNBS TitleScene::Update(UNBS own)
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		return std::move(std::make_unique<GameScene>());
	}
	if (titleNum_ == 0)
	{
		int num = title1Update();
		if (num == 1)
		{
			return std::move(std::make_unique<PoseScene>(std::move(own)));
		}
	}
	else if (titleNum_ == 1)
	{
		int num = title2Update();
		if (num == 1)
		{
			tmptitleNum_ = 2;
		}
	}
	else if (titleNum_ == 2)
	{
		if (tmptitleNum_ == -1)
		{
			if (lpPadMng.GetControllerData(InputID::Right) || CheckHitKey(KEY_INPUT_RIGHT))
			{
				lpSoundMng.SoundPlay("botan.mp3");
				isTarget_++;
			}
			if (lpPadMng.GetControllerData(InputID::Left) || CheckHitKey(KEY_INPUT_LEFT))
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
			if (lpPadMng.GetControllerData(InputID::BtnB) || CheckHitKey(KEY_INPUT_Z))
			{
				lpSoundMng.SoundPlay("pusbotan.mp3");
				if (isTarget_ == 1)
				{
					lpMoneyMng.SetMoney(150);
					tmptitleNum_ = 0;
					return std::move(std::make_unique<GameScene>());
				}
				else
				{
					tmptitleNum_ = 0;
					return std::move(std::make_unique<GameScene>());
				}
			}
			if (lpPadMng.GetControllerData(InputID::BtnA) || CheckHitKey(KEY_INPUT_X))
			{
				lpSoundMng.SoundPlay("pusbotan.mp3");
				isTarget_ = 1;
				tmptitleNum_ = 1;
			}
		}
	}
	if (tmptitleNum_ != -1)
	{
		if (changeCount_ / 30 % 2 != 0)
		{
			isTarget_ = 0;
			changeCount_ = -1;
			titleNum_ = tmptitleNum_;
			tmptitleNum_ = -1;
		}
		changeCount_++;
	}
	return std::move(own);
}

TitleScene::TitleScene()
{
	SetWindowText("::タイトル");
	scnID_ = SCN_ID::SCN_TITLE;
	screenSize_.x = 0;
	screenSize_.y = 0;
	GetDrawScreenSize(&screenSize_.x, &screenSize_.y);
	screenH_ = MakeScreen(screenSize_.x, screenSize_.y, true);
	isTarget_ = 0;
	tmptitleNum_ = -1;
	titleNum_ = 0;
	changeCount_ = 0;
	SetMousePoint(screenSize_.x / 2, screenSize_.y / 2);
}

TitleScene::~TitleScene()
{
}

void TitleScene::Draw()
{
	SetDrawScreen(screenH_);
	ClsDrawScreen();

	DrawFormatString(screenSize_.x / 2 - 50, screenSize_.y / 3, 0xffffff, "タイトル画面");

	if (titleNum_ == 0)
	{
		title1Draw();
	}
	else if (titleNum_ == 1)
	{
		title2Draw();
	}
	else if (titleNum_ == 2)
	{
		Vector2 pos;
		DrawBox(screenSize_.x / 2 - 150, screenSize_.y / 2 - 50, screenSize_.x / 2 + 160, screenSize_.y / 2 + 100, 0x121212, true);
		DrawFormatString(screenSize_.x / 2 - 70, screenSize_.y / 2 - 35, 0xffffff, "つづきから？\n(未実装)");
		pos.x = screenSize_.x / 2 - 100;
		pos.y = screenSize_.y / 2 + 50;

		if (isTarget_ == 0)
		{
			pos.x = screenSize_.x / 2 - 110;
		}

		if (isTarget_ == 1)
		{
			pos.x = screenSize_.x / 2 + 50;
		}
		pos.y += 13;
		DrawTriangle(pos.x - 20, pos.y - 15, pos.x - 20, pos.y + 15, pos.x, pos.y, 0xffffff, false);

		if (isTarget_ != 0)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
		}
		else
		{
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
		DrawFormatString(screenSize_.x / 2 - 100, screenSize_.y / 2 + 50, 0xffffff, "はい");
		if (isTarget_ != 1)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
		}
		else
		{
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
		DrawFormatString(screenSize_.x / 2 + 60, screenSize_.y / 2 + 50, 0xffffff, "いいえ");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	SetDrawScreen(DX_SCREEN_BACK);
	lpImglMng.ScreenAddDrawQue(screenH_, { 0,0 }, 0);
}

int TitleScene::title1Update()
{
	if (tmptitleNum_ != -1)
	{
		return 0;
	}
	if (lpPadMng.GetControllerData(InputID::Right)||CheckHitKey(KEY_INPUT_RIGHT))
	{
		lpSoundMng.SoundPlay("botan.mp3");
		isTarget_++;
	}
	if (lpPadMng.GetControllerData(InputID::Left) || CheckHitKey(KEY_INPUT_LEFT))
	{
		lpSoundMng.SoundPlay("botan.mp3");
		isTarget_--;
	}
	if (isTarget_ < 0)
	{
		isTarget_ = 0;
	}
	if (isTarget_ > 3)
	{
		isTarget_ = 3;
	}
	if (lpPadMng.GetControllerData(InputID::BtnB) || CheckHitKey(KEY_INPUT_Z))
	{
		lpSoundMng.SoundPlay("pusbotan.mp3");
		if (isTarget_ == 0)
		{
			tmptitleNum_ = 1;
			return 0;
		}
		if (isTarget_ == 2)
		{
			return 1;
		}
		if (isTarget_ == 3)
		{
			tmptitleNum_ = 0;
			Sleep(300);
			lpSceneMng.SetShutdown();
			return 0;
		}
	}
	return 0;
}

void TitleScene::title1Draw()
{
	Vector2 pos;
	pos.y = screenSize_.y - screenSize_.y / 5 + 13;

	if (isTarget_ == 0)
	{
		pos.x = screenSize_.x / 2 - 400;
	}

	if (isTarget_ == 1)
	{
		pos.x = screenSize_.x / 2 - 150;
	}

	if (isTarget_ == 2)
	{
		pos.x = screenSize_.x / 2 + 150;
	}

	if (isTarget_ == 3)
	{
		pos.x = screenSize_.x / 2 + 400;
	}
	DrawTriangle(pos.x - 20, pos.y - 15, pos.x - 20, pos.y + 15, pos.x, pos.y, 0xffffff, false);
	if (isTarget_ != 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	DrawFormatString(screenSize_.x / 2 - 400, screenSize_.y - screenSize_.y / 5, 0xffffff, "はじめる");
	if (isTarget_ != 1)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	DrawFormatString(screenSize_.x / 2 - 150, screenSize_.y - screenSize_.y / 5, 0xffffff, "マニュアルX");
	if (isTarget_ != 2)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	DrawFormatString(screenSize_.x / 2 + 150, screenSize_.y - screenSize_.y / 5, 0xffffff, "設定");
	if (isTarget_ != 3)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	DrawFormatString(screenSize_.x / 2 + 400, screenSize_.y - screenSize_.y / 5, 0xffffff, "おわる");

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

int TitleScene::title2Update()
{
	if (tmptitleNum_ != -1)
	{
		return 0;
	}
	if (lpPadMng.GetControllerData(InputID::Right) || CheckHitKey(KEY_INPUT_RIGHT))
	{
		lpSoundMng.SoundPlay("botan.mp3");
		isTarget_++;
	}
	if (lpPadMng.GetControllerData(InputID::Left) || CheckHitKey(KEY_INPUT_LEFT))
	{
		lpSoundMng.SoundPlay("botan.mp3");
		isTarget_--;
	}
	if (isTarget_ < 0)
	{
		isTarget_ = 0;
	}
	if (isTarget_ > 3)
	{
		isTarget_ = 3;
	}
	if (lpPadMng.GetControllerData(InputID::BtnB) || CheckHitKey(KEY_INPUT_Z))
	{
		lpSoundMng.SoundPlay("pusbotan.mp3");
		if (isTarget_ == 1)
		{
			return 1;
		}
		if (isTarget_ == 3)
		{
			tmptitleNum_ = 0;
			return 0;
		}
	}

	if (lpPadMng.GetControllerData(InputID::BtnA) || CheckHitKey(KEY_INPUT_X))
	{
		lpSoundMng.SoundPlay("pusbotan.mp3");
		tmptitleNum_ = 0;
	}
	return 0;
}

void TitleScene::title2Draw()
{
	Vector2 pos;
	pos.y = screenSize_.y - screenSize_.y / 5 + 13;

	if (isTarget_ == 0)
	{
		pos.x = screenSize_.x / 2 - 400;
	}

	if (isTarget_ == 1)
	{
		pos.x = screenSize_.x / 2 - 150;
	}

	if (isTarget_ == 2)
	{
		pos.x = screenSize_.x / 2 + 150;
	}

	if (isTarget_ == 3)
	{
		pos.x = screenSize_.x / 2 + 400;
	}
	DrawTriangle(pos.x - 20, pos.y - 15, pos.x - 20, pos.y + 15, pos.x, pos.y, 0xffffff, false);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	if (isTarget_ != 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	DrawFormatString(screenSize_.x / 2 - 400, screenSize_.y - screenSize_.y / 5, 0xffffff, "れんしゅうX");
	if (isTarget_ != 1)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	DrawFormatString(screenSize_.x / 2 - 150, screenSize_.y - screenSize_.y / 5, 0xffffff, "ストーリー");
	if (isTarget_ != 2)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	DrawFormatString(screenSize_.x / 2 + 150, screenSize_.y - screenSize_.y / 5, 0xffffff, "エンドレスX");
	if (isTarget_ != 3)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	DrawFormatString(screenSize_.x / 2 + 400, screenSize_.y - screenSize_.y / 5, 0xffffff, "もどる");
	if (isTarget_ != 4)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}