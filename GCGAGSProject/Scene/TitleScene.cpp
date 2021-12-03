#include <DxLib.h>
#include "ImageMng.h"
#include "TitleScene.h"
#include "PoseScene.h"
#include "GameScene.h"
#include "PadMng.h"
#include "ImageMng.h"
#include "sceneMng.h"
#include "soundMng.h"
#include "MoneyMng.h"
#include "MouseMng.h"
#include "KeyMng.h"

UNBS TitleScene::Update(UNBS own)
{
	time_ += lpCronoMng.GetDeltaTime();
	//if (lpCronoMng.IsOneSecond())
	{
		maskPos1_.x += lpCronoMng.GetDeltaTime() * 60;
		maskPos1_.y += lpCronoMng.GetDeltaTime() * 60;
		maskPos2_.x += lpCronoMng.GetDeltaTime() * 60;
		maskPos2_.y += lpCronoMng.GetDeltaTime() * 60;
		if (maskPos1_.x >= screenSize_.x || maskPos1_.y >= screenSize_.y)
		{
			maskPos1_ = { -screenSize_.x,-screenSize_.y };
		}
		if (maskPos2_.x >= screenSize_.x || maskPos2_.y >= screenSize_.y)
		{
			maskPos2_ = { -screenSize_.x,-screenSize_.y };
		}
	}
	sterangle_ = static_cast<int>(time_*10) % 360;
	if (sterangle_ > 360)
	{
		sterangle_ = 0;
	}
	if (!lpSoundMng.CheckPlaySound("title.mp3"))
	{
		lpSoundMng.SoundPlay("title.mp3");
	}
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		lpSoundMng.StopSound("title.mp3");
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
			if (lpPadMng.GetControllerData(InputID::BtnA) || lpKeyMng.CheckKeyTrg(KeyBindID::No))
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
	lpImglMng.LoadGraph("wood.png");
	lpImglMng.LoadGraph("titlef.png");
	lpImglMng.LoadGraph("titleblack.png");
	SetWindowText("DungeonOwner");
	scnID_ = SCN_ID::SCN_TITLE;
	screenSize_.x = 0;
	screenSize_.y = 0;
	GetDrawScreenSize(&screenSize_.x, &screenSize_.y);
	screenH_ = MakeScreen(screenSize_.x, screenSize_.y, true);
	isTarget_ = 0;
	tmptitleNum_ = -1;
	titleNum_ = 0;
	sterangle_ = 0;
	time_ = 0;
	changeCount_ = 0;
	maskHandle_ = LoadMask("resource\\img/titlemask.png");
	SetMousePoint(screenSize_.x / 2, screenSize_.y / 2);
	maskPos1_ = { -screenSize_.x,-screenSize_.y };
	maskPos2_ = { 0,0 };
}

TitleScene::~TitleScene()
{
	DeleteMask(maskHandle_);
}

void TitleScene::Draw()
{
	SetDrawScreen(screenH_);
	ClsDrawScreen();

	//DrawFormatString(screenSize_.x / 2 - 50, screenSize_.y / 3, 0xffffff, "タイトル画面");


	lpImglMng.DrawImg("wood.png", { 0,0 });
	lpImglMng.DrawImg("title0.png", { 0,0 });
	lpImglMng.DrawImg("titleblack.png", { 0,0 });
	lpImglMng.DrawImg("title1.png", { 0,0 });
	lpImglMng.DrawImg("title2.png", { 0,0 });
	lpImglMng.DrawImg("title3.png", { 0,0 });
	CreateMaskScreen();
	DrawMask(0, 0, maskHandle_, DX_MASKTRANS_BLACK);
	lpImglMng.DrawImg("space3.png", { 0,0 });
	lpImglMng.DrawImg("space2.png", maskPos1_);
	lpImglMng.DrawImg("space2.png", { maskPos1_.x + screenSize_.x,maskPos1_.y });
	lpImglMng.DrawImg("space2.png", maskPos2_);
	lpImglMng.DrawImg("space2.png", { maskPos2_.x,maskPos2_.y - screenSize_.y });
	//lpImglMng.DrawImg("space2.png", maskPos1_);
	//lpImglMng.DrawImg("space2.png", { maskPos1_.x + 3820,maskPos1_.y });
	//lpImglMng.DrawImg("space2.png", maskPos2_);
	//lpImglMng.DrawImg("space2.bmp", { maskPos2_.x,maskPos2_.y - 2160 });
	DeleteMaskScreen();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	DrawBox(screenSize_.x / 2 - 480, screenSize_.y - screenSize_.y / 5 - 20, screenSize_.x / 2 + 450, screenSize_.y - screenSize_.y / 5 + 40, 0x00000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

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
	lpImglMng.ScreenAddDrawQue(screenH_, { 0,0 }, 30);
}

int TitleScene::title1Update()
{
	if (tmptitleNum_ != -1)
	{
		return 0;
	}
	if (lpPadMng.GetControllerData(InputID::Right)|| lpKeyMng.CheckKeyTrg(KeyBindID::Right))
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
	if (isTarget_ > 3)
	{
		isTarget_ = 3;
	}
	if (lpPadMng.GetControllerData(InputID::BtnB) || lpKeyMng.CheckKeyTrg(KeyBindID::Ok))
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
		pos.x = screenSize_.x / 2 - 450;
	}

	if (isTarget_ == 1)
	{
		pos.x = screenSize_.x / 2 - 200;
	}

	if (isTarget_ == 2)
	{
		pos.x = screenSize_.x / 2 + 100;
	}

	if (isTarget_ == 3)
	{
		pos.x = screenSize_.x / 2 + 350;
	}
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
	DrawFormatString(screenSize_.x / 2 - 450, screenSize_.y - screenSize_.y / 5, 0xffffff, "はじめる");
	if (isTarget_ != 1)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	DrawFormatString(screenSize_.x / 2 - 200, screenSize_.y - screenSize_.y / 5, 0xffffff, "マニュアルX");
	if (isTarget_ != 2)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	DrawFormatString(screenSize_.x / 2 + 100, screenSize_.y - screenSize_.y / 5, 0xffffff, "設定");
	if (isTarget_ != 3)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	DrawFormatString(screenSize_.x / 2 + 350, screenSize_.y - screenSize_.y / 5, 0xffffff, "おわる");

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

int TitleScene::title2Update()
{
	if (tmptitleNum_ != -1)
	{
		return 0;
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
	if (isTarget_ > 3)
	{
		isTarget_ = 3;
	}
	if (lpPadMng.GetControllerData(InputID::BtnB) || lpKeyMng.CheckKeyTrg(KeyBindID::Ok))
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

	if (lpPadMng.GetControllerData(InputID::BtnA) || lpKeyMng.CheckKeyTrg(KeyBindID::No))
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

	DrawRotaGraph(pos.x - 10, pos.y, 1.0, sterangle_, lpImglMng.GetGraphHandle("ster.png"), true);
	//DrawTriangle(pos.x - 20, pos.y - 15, pos.x - 20, pos.y + 15, pos.x, pos.y, 0xffffff, false);

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