#include <DxLib.h>
#include "ResultScene.h"
#include "ImageMng.h"
#include "CronoMng.h"
#include "PadMng.h"
#include "KeyMng.h"
#include "moneyMng.h"
#include "mouseMng.h"
#include "soundMng.h"
#include "StatusCtr.h"
#include "ReadMng.h"
#include "gameUI/ScrollUIBase.h"

UNBS ResultScene::Update(UNBS own)
{
	time_ += lpCronoMng.GetDeltaTime();
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
	if (isTarget_ > 3)
	{
		isTarget_ = 3;
	}
	if (lpPadMng.GetControllerData(InputID::BtnB) || lpKeyMng.CheckKeyTrg(KeyBindID::Ok))
	{
		if (resultNum_ == 0)
		{
			StatusID id;
			if (isTarget_ == 0)
			{
				if (lpMoneyMng.SubMoney(100))
				{
					lpSoundMng.SoundPlay("pusbotan.mp3");
					id = StatusID::MapSize;
					StatusCtr::SetStates(id, StatusCtr::GetStates(id) + 1);
				}
				else
				{
					lpSoundMng.SoundPlay("not.mp3");
				}
			}
			if (isTarget_ == 1)
			{
				if (lpMoneyMng.SubMoney(100))
				{
					lpSoundMng.SoundPlay("pusbotan.mp3");
					id = StatusID::Monster1;
					StatusCtr::SetStates(id, StatusCtr::GetStates(id) + 1);
				}
				else
				{
					lpSoundMng.SoundPlay("not.mp3");
				}
			}
			if (isTarget_ == 2)
			{
				if (lpMoneyMng.SubMoney(100))
				{
					lpSoundMng.SoundPlay("pusbotan.mp3");
					id = StatusID::Monster2;
					StatusCtr::SetStates(id, StatusCtr::GetStates(id) + 1);
				}
				else
				{
					lpSoundMng.SoundPlay("not.mp3");
				}
			}
			if (isTarget_ == 3)
			{
				isTarget_ = 0;
				resultNum_ = 1;
			}
		}
		else
		{
			StatusID id;
			if (isTarget_ == 0)
			{
				if (lpMoneyMng.SubMoney(100))
				{
					lpSoundMng.SoundPlay("pusbotan.mp3");
					id = StatusID::Monster3;
					StatusCtr::SetStates(id, StatusCtr::GetStates(id) + 1);
				}
				else
				{
					lpSoundMng.SoundPlay("not.mp3");
				}
			}
			if (isTarget_ == 1)
			{
				if (lpMoneyMng.SubMoney(100))
				{
					lpSoundMng.SoundPlay("pusbotan.mp3");
					id = StatusID::GImmick1;
					StatusCtr::SetStates(id, StatusCtr::GetStates(id) + 1);
				}
				else
				{
					lpSoundMng.SoundPlay("not.mp3");
				}
			}
			if (isTarget_ == 2)
			{
				if (lpMoneyMng.SubMoney(100))
				{
					lpSoundMng.SoundPlay("pusbotan.mp3");
					id = StatusID::GImmick2;
					StatusCtr::SetStates(id, StatusCtr::GetStates(id) + 1);
				}
				else
				{
					lpSoundMng.SoundPlay("not.mp3");
				}
			}
			if (isTarget_ == 3)
			{
				if (lpMoneyMng.SubMoney(100))
				{
					lpSoundMng.SoundPlay("pusbotan.mp3");
					id = StatusID::PlayerHP;
					StatusCtr::SetStates(id, StatusCtr::GetStates(id) + 1);
				}
				else
				{
					lpSoundMng.SoundPlay("not.mp3");
				}
			}
		}
	}
	if (lpPadMng.GetControllerData(InputID::BtnA) || lpKeyMng.CheckKeyTrg(KeyBindID::No))
	{
		lpSoundMng.SoundPlay("pusbotan.mp3");
		isTarget_ = 1;
		if (resultNum_ == 0)
		{
			lpReadMng.SetDate(setinglist::Money, lpMoneyMng.GetMoney());
			return std::move(ownS_);
		}
		else
		{
			resultNum_ = 0;
		}
	}
	graphY_++;
	return own;
}

ResultScene::ResultScene()
{
	Init();
}

ResultScene::ResultScene(UNBS own)
{
	Init();
	SetOwn(std::move(own));
}

ResultScene::~ResultScene()
{
	lpSoundMng.DeleteSound("not.mp3");
}

void ResultScene::Draw()
{
	ownS_->Draw();
	SetDrawScreen(screenH_);
	ClsDrawScreen();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	DrawBox(0, 0, screenSize_.x, screenSize_.y, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	lpImglMng.DrawImg("gameWin.png", { 0,graphY_ % 20 - 30 });

	DrawFormatString(screenSize_.x / 3, screenSize_.y / 2 - 140, 0xffffff, "ゲットしたゴールド　%4d", resultMoney_);
	DrawFormatString(screenSize_.x / 3, screenSize_.y / 2 - 100, 0xffffff, "もっているゴールド　%4d", lpMoneyMng.GetMoney());
	DrawFormatString(screenSize_.x / 4, screenSize_.y / 2 - 50, 0xffffff, "きょうかしたいものを選んでください　価格100ゴールド");

	DrawLine(0, screenSize_.y - screenSize_.y / 5 - 60, screenSize_.x, screenSize_.y - screenSize_.y / 5 - 60, 0xffffff, 5);

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
	if (resultNum_ == 0)
	{
		DrawFormatString(screenSize_.x / 2 - 450, screenSize_.y - screenSize_.y / 5, 0xffffff, "マップ");
	}
	else
	{
		DrawFormatString(screenSize_.x / 2 - 450, screenSize_.y - screenSize_.y / 5, 0xffffff, "ビショップ");
	}
	if (isTarget_ != 1)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	if (resultNum_ == 0)
	{
		DrawFormatString(screenSize_.x / 2 - 200, screenSize_.y - screenSize_.y / 5, 0xffffff, "ポーン");
	}
	else
	{
		DrawFormatString(screenSize_.x / 2 - 200, screenSize_.y - screenSize_.y / 5, 0xffffff, "スパイク");
	}
	if (isTarget_ != 2)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	if (resultNum_ == 0)
	{
		DrawFormatString(screenSize_.x / 2 + 100, screenSize_.y - screenSize_.y / 5, 0xffffff, "ルーク");
	}
	else
	{
		DrawFormatString(screenSize_.x / 2 + 100, screenSize_.y - screenSize_.y / 5, 0xffffff, "ゲート");
	}
	if (isTarget_ != 3)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	if (resultNum_ == 0)
	{
		DrawFormatString(screenSize_.x / 2 + 350, screenSize_.y - screenSize_.y / 5, 0xffffff, "ほか");
	}
	else
	{
		DrawFormatString(screenSize_.x / 2 + 350, screenSize_.y - screenSize_.y / 5, 0xffffff, "じぶん");
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	if (resultNum_ == 0)
	{
		DrawFormatString(screenSize_.x - screenSize_.x/5, screenSize_.y - 100, 0xffffff, "Xでキャンセルする");
	}
	else
	{
		DrawFormatString(screenSize_.x - screenSize_.x / 5, screenSize_.y - 100, 0xffffff, "Xでもどる");
	}

	lpImglMng.ScreenAddDrawQue(screenH_, 79);
}

void ResultScene::SetOwn(UNBS own)
{
	ownS_ = std::move(own);
}

void ResultScene::Init(void)
{
	resultMoney_ = lpMoneyMng.GettmpMoney();
	lpMoneyMng.AddMoney(resultMoney_);

	lpReadMng.SetDate(setinglist::Money, lpMoneyMng.GetMoney());
	isTarget_ = 0;
	time_ = 0;
	graphY_ = 0;
	resultNum_ = 0;
	GetDrawScreenSize(&screenSize_.x, &screenSize_.y);
	screenH_ = MakeScreen(screenSize_.x, screenSize_.y, true);
	lpImglMng.LoadGraph("gameWin.png");
	lpSoundMng.LoadSound("not.mp3");
	ScrollUIBase::SetLockOff();
}
