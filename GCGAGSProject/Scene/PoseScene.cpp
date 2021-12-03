#include <DxLib.h>
#include "PoseScene.h"
#include "TitleScene.h"
#include "ImageMng.h"
#include "PadMng.h"
#include "soundMng.h"
#include "ReadMng.h"
#include "CronoMng.h"
#include "KeyMng.h"

UNBS PoseScene::Update(UNBS own)
{
	time_ += lpCronoMng.GetDeltaTime();
	sterangle_ = static_cast<int>(time_ * 10) % 360;
	if (sterangle_ > 360)
	{
		sterangle_ = 0;
	}

	if (setingNum_ == 0)
	{
		int num = poseUpdate();
		if (num == 1)
		{
			setingNum_ = 1;
		}
		if (num == 2)
		{
			lpImglMng.SetBright(255);
			setingNum_ = 2;
		}
		if (num == 4)
		{
			if (ownS_->GetSCNID() == SCN_ID::SCN_GAME)
			{
				setingNum_ = -1;
			}
			else
			{
				return std::move(ownS_);
			}
		}
	}
	else if (setingNum_ == 1)
	{
		VolUpdate();
	}
	else if (setingNum_ == 2)
	{
		BrightUpdate();
	}
	else if (setingNum_ == -1)
	{
		int num = firstUpdate();
		if (num == 1)
		{
			setingNum_ = 0;
		}
		if (num == 2)
		{
			setingNum_ = -2;
		}
		if (num == 3)
		{
			lpReadMng.SetDate(setinglist::Bright, tmpbright_);
			lpImglMng.SetBright(tmpbright_);
			return std::move(ownS_);
		}
	}
	else
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
				lpReadMng.SetDate(setinglist::Bright, tmpbright_);
				lpImglMng.SetBright(tmpbright_);
				return std::move(std::make_unique<TitleScene>());
			}
			else
			{
				isTarget_ = 0;
				setingNum_ = -1;
			}
		}
		if (lpPadMng.GetControllerData(InputID::BtnA) || lpKeyMng.CheckKeyTrg(KeyBindID::No))
		{
			lpSoundMng.SoundPlay("pusbotan.mp3");
			isTarget_ = 0;
			setingNum_ = -1;
		}
	}

	return std::move(own);
}

PoseScene::PoseScene()
{
	SetWindowText("::設定");
	screenSize_.x = 0;
	screenSize_.y = 0;
	GetDrawScreenSize(&screenSize_.x, &screenSize_.y);
	screenH_ = MakeScreen(screenSize_.x, screenSize_.y, true);
	setingNum_ = 0;
	isTarget_ = 0;
	tmpbright_ = bright_ = lpImglMng.GetBright();
	tmpSoundVol_ = soundVol_ = lpSoundMng.GetSoundVol();
	lpImglMng.SetBright(255);
	playsF_ = false;
	SetMousePoint(screenSize_.x / 2, screenSize_.y / 2);
}

PoseScene::PoseScene(UNBS own)
{
	setingNum_ = 0;
	if (own->GetSCNID() == SCN_ID::SCN_TITLE)
	{
	}
	else if (own->GetSCNID() == SCN_ID::SCN_GAME)
	{
		setingNum_ = -1;
	}
	screenSize_.x = 0;
	screenSize_.y = 0;
	GetDrawScreenSize(&screenSize_.x, &screenSize_.y);
	screenH_ = MakeScreen(screenSize_.x, screenSize_.y, true);
	ownS_ = std::move(own);
	isTarget_ = 0;
	tmpbright_ = bright_ = lpImglMng.GetBright();
	tmpSoundVol_ = soundVol_ = lpSoundMng.GetSoundVol();
	playsF_ = false;
}

PoseScene::~PoseScene()
{
}

void PoseScene::Draw()
{
	SetDrawScreen(screenH_);
	ClsDrawScreen();
	ownS_->Draw();
	SetDrawScreen(screenH_);

	if (setingNum_ == 0)
	{
		poseDraw();
	}
	else if (setingNum_ == 1)
	{
		VolDraw();
	}
	else if (setingNum_ == 2)
	{
		BrightDraw();
	}
	else if (setingNum_ == -1)
	{
		firstDraw();
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
		DrawBox(0, 0, screenSize_.x, screenSize_.y, 0x000000, true);

		DrawBox(screenSize_.x / 2 - 125, screenSize_.y / 2 - 100, screenSize_.x / 2 + 150, screenSize_.y / 2 + 125, 0x121212, true);
		DrawBox(screenSize_.x / 2 - 125, screenSize_.y / 2 - 100, screenSize_.x / 2 + 150, screenSize_.y / 2 + 125, 0xffffff, false);
		Vector2 pos;
		pos.x = screenSize_.x / 2 - 100;
		pos.y = screenSize_.y / 2 - 20;

		pos.y += 13;
		DrawRotaGraph(pos.x - 10, pos.y, 1.0, sterangle_, lpImglMng.GetGraphHandle("ster.png"), true);
		//DrawTriangle(pos.x - 20, pos.y - 15, pos.x - 20, pos.y + 15, pos.x, pos.y, 0xffffff, false);

		DrawFormatString(screenSize_.x / 2 - 50, screenSize_.y / 2 - 130, 0xffffff, "ポーズ中");

		DrawFormatString(screenSize_.x / 2 - 100, screenSize_.y / 2 - 80, 0xffffff, "システム設定");

		DrawFormatString(screenSize_.x / 2 - 100, screenSize_.y / 2 - 20, 0xffffff, "タイトルへ");

		DrawFormatString(screenSize_.x / 2 - 100, screenSize_.y / 2 + 90, 0xffffff, "もどる");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		DrawBox(screenSize_.x / 2 - 150, screenSize_.y / 2 - 50, screenSize_.x / 2 + 160, screenSize_.y / 2 + 100, 0x121212, true);
		DrawFormatString(screenSize_.x / 2 - 70, screenSize_.y / 2 - 35, 0xffffff, "ほんとうに？");
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

		DrawFormatString(screenSize_.x / 2 - 100, screenSize_.y / 2 + 50, 0xffffff, "いいえ");
		DrawFormatString(screenSize_.x / 2 + 60, screenSize_.y / 2 + 50, 0xffffff, "はい");
	}
	SetDrawScreen(DX_SCREEN_BACK);
	lpImglMng.ScreenAddDrawQue(screenH_, { 0,0 }, 75);
}

void PoseScene::SetOwn(UNBS own)
{
	ownS_ = std::move(own);
}

int PoseScene::firstUpdate()
{
	if (lpPadMng.GetControllerData(InputID::Up) || lpKeyMng.CheckKeyTrg(KeyBindID::Up))
	{
		lpSoundMng.SoundPlay("botan.mp3");
		isTarget_--;
	}
	if (lpPadMng.GetControllerData(InputID::Down) || lpKeyMng.CheckKeyTrg(KeyBindID::Down))
	{
		lpSoundMng.SoundPlay("botan.mp3");
		isTarget_++;
	}
	if (isTarget_ < 0)
	{
		isTarget_ = 0;
	}
	if (isTarget_ > 2)
	{
		isTarget_ = 2;
	}

	if (lpPadMng.GetControllerData(InputID::BtnB) || lpKeyMng.CheckKeyTrg(KeyBindID::Ok))
	{
		lpSoundMng.SoundPlay("pusbotan.mp3");
		if (isTarget_ == 0)
		{
			isTarget_ = 0;
			return 1;
		}
		if (isTarget_ == 1)
		{
			isTarget_ = 0;
			return 2;
		}
		if (isTarget_ == 2)
		{
			isTarget_ = 0;
			return 3;
		}
	}

	if (lpPadMng.GetControllerData(InputID::BtnA) || lpKeyMng.CheckKeyTrg(KeyBindID::No))
	{
		lpSoundMng.SoundPlay("pusbotan.mp3");
		isTarget_ = 0;
		return 3;
	}
	return 0;
}

void PoseScene::firstDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
	DrawBox(0, 0, screenSize_.x, screenSize_.y, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	DrawBox(screenSize_.x / 2 - 125, screenSize_.y / 2 - 100, screenSize_.x / 2 + 150, screenSize_.y / 2 + 125, 0x121212, true);
	DrawBox(screenSize_.x / 2 - 125, screenSize_.y / 2 - 100, screenSize_.x / 2 + 150, screenSize_.y / 2 + 125, 0xffffff, false);
	Vector2 pos;
	pos.x = screenSize_.x / 2 - 100;

	if (isTarget_ == 0)
	{
		pos.y = screenSize_.y / 2 - 80;
	}

	if (isTarget_ == 1)
	{
		pos.y = screenSize_.y / 2 - 20;
	}

	if (isTarget_ == 2)
	{
		pos.y = screenSize_.y / 2 + 90;
	}

	pos.y += 13;
	DrawRotaGraph(pos.x - 10, pos.y, 1.0, sterangle_, lpImglMng.GetGraphHandle("ster.png"), true);
	//DrawTriangle(pos.x - 20, pos.y - 15, pos.x - 20, pos.y + 15, pos.x, pos.y, 0xffffff, false);

	DrawFormatString(screenSize_.x / 2 - 50, screenSize_.y / 2 - 130, 0xffffff, "ポーズ中");

	DrawFormatString(screenSize_.x / 2 - 100, screenSize_.y / 2 - 80, 0xffffff, "システム設定");

	DrawFormatString(screenSize_.x / 2 - 100, screenSize_.y / 2 - 20, 0xffffff, "タイトルへ");

	DrawFormatString(screenSize_.x / 2 - 100, screenSize_.y / 2 + 90, 0xffffff, "もどる");
}

int PoseScene::poseUpdate()
{
	if (lpPadMng.GetControllerData(InputID::Up) || lpKeyMng.CheckKeyTrg(KeyBindID::Up))
	{
		lpSoundMng.SoundPlay("botan.mp3");
		isTarget_--;
	}
	if (lpPadMng.GetControllerData(InputID::Down) || lpKeyMng.CheckKeyTrg(KeyBindID::Down))
	{
		lpSoundMng.SoundPlay("botan.mp3");
		isTarget_++;
	}
	if (isTarget_ < 0)
	{
		isTarget_ = 0;
	}
	if (isTarget_ > 2)
	{
		isTarget_ = 2;
	}

	if (lpPadMng.GetControllerData(InputID::BtnB) || lpKeyMng.CheckKeyTrg(KeyBindID::Ok))
	{
		lpSoundMng.SoundPlay("pusbotan.mp3");
		if (isTarget_ == 0)
		{
			isTarget_ = 0;
			return 1;
		}
		if (isTarget_ == 1)
		{
			isTarget_ = 0;
			return 2;
		}
		if (isTarget_ == 2)
		{
			isTarget_ = 0;
			return 4;
		}
	}
	if (lpPadMng.GetControllerData(InputID::BtnA) || lpKeyMng.CheckKeyTrg(KeyBindID::No))
	{
		lpSoundMng.SoundPlay("pusbotan.mp3");
		isTarget_ = 0;
		return 4;
	}
	return 0;
}

void PoseScene::poseDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(0, 0, screenSize_.x, screenSize_.y, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	DrawBox(screenSize_.x / 2 - 125, screenSize_.y / 2 - 100, screenSize_.x / 2 + 150, screenSize_.y / 2 + 125, 0x121212, true);

	Vector2 pos;
	pos.x = screenSize_.x / 2 - 100;

	if (isTarget_ == 0)
	{
		pos.y = screenSize_.y / 2 - 80;
	}

	if (isTarget_ == 1)
	{
		pos.y = screenSize_.y / 2 - 20;
	}

	if (isTarget_ == 2)
	{
		pos.y = screenSize_.y / 2 + 90;
	}
	pos.y += 13;
	DrawRotaGraph(pos.x - 10, pos.y, 1.0, sterangle_, lpImglMng.GetGraphHandle("ster.png"), true);
	//DrawTriangle(pos.x - 20, pos.y - 15, pos.x - 20, pos.y + 15, pos.x, pos.y, 0xffffff, false);

	DrawFormatString(screenSize_.x / 2 - 60, screenSize_.y / 2 - 130, 0xffffff, "システム設定");

	DrawFormatString(screenSize_.x / 2 - 100, screenSize_.y / 2 - 80, 0xffffff, "音量");

	DrawFormatString(screenSize_.x / 2 - 100, screenSize_.y / 2 - 20, 0xffffff, "明るさ");

	DrawFormatString(screenSize_.x / 2 - 100, screenSize_.y / 2 + 90, 0xffffff, "もどる");
}

void PoseScene::VolUpdate()
{
	if (lpPadMng.GetControllerData(InputID::Up) || lpKeyMng.CheckKeyTrg(KeyBindID::Up))
	{
		lpSoundMng.SoundPlay("botan.mp3");
		isTarget_--;
	}
	if (lpPadMng.GetControllerData(InputID::Down) || lpKeyMng.CheckKeyTrg(KeyBindID::Down))
	{
		lpSoundMng.SoundPlay("botan.mp3");
		isTarget_++;
	}
	if (isTarget_ < 0)
	{
		isTarget_ = 0;
	}
	if (isTarget_ > 1)
	{
		isTarget_ = 1;
	}
	if (isTarget_ == 0)
	{
		if (lpPadMng.GetNowControllerData(InputID::Right) || lpKeyMng.CheckKeyNow(KeyBindID::Right))
		{
			ChangeVolumeSoundMem(tmpSoundVol_, lpSoundMng.GetSoundHandle("pusbotan.mp3"));
			tmpSoundVol_++;
			playsF_ = true;
		}
		else
			if (lpPadMng.GetNowControllerData(InputID::Left) || lpKeyMng.CheckKeyNow(KeyBindID::Left))
			{
				ChangeVolumeSoundMem(tmpSoundVol_, lpSoundMng.GetSoundHandle("pusbotan.mp3"));
				tmpSoundVol_--;
				playsF_ = true;
			}
			else if (playsF_)
			{
				playsF_ = false;
				lpSoundMng.StopSound("pusbotan.mp3");
				lpSoundMng.SoundPlay("pusbotan.mp3");
			}
		if (tmpSoundVol_ < 0)
		{
			tmpSoundVol_ = 0;
		}
		if (tmpSoundVol_ > 120)
		{
			tmpSoundVol_ = 120;
		}
	}
	if (lpPadMng.GetControllerData(InputID::BtnB) || lpKeyMng.CheckKeyTrg(KeyBindID::Ok))
	{
		lpSoundMng.SoundPlay("pusbotan.mp3");
		if (isTarget_ == 1)
		{
			lpReadMng.SetDate(setinglist::SoundVol, tmpSoundVol_);
			lpSoundMng.SetSoundVol(tmpSoundVol_);
			setingNum_ = 0;
			isTarget_ = 0;
		}
	}
	if (lpPadMng.GetControllerData(InputID::BtnA) || lpKeyMng.CheckKeyTrg(KeyBindID::No))
	{
		ChangeVolumeSoundMem(soundVol_, lpSoundMng.GetSoundHandle("pusbotan.mp3"));
		tmpSoundVol_ = soundVol_;
		lpSoundMng.SoundPlay("pusbotan.mp3");
		tmpbright_ = bright_;
		isTarget_ = 0;
		setingNum_ = 0;
		isTarget_ = 0;
	}
}

void PoseScene::VolDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(0, 0, screenSize_.x, screenSize_.y, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	DrawBox(screenSize_.x / 2 - 125, screenSize_.y / 2 - 100, screenSize_.x / 2 + 150, screenSize_.y / 2 + 125, 0x121212, true);

	Vector2 pos;
	pos.x = screenSize_.x / 2 - 100;

	if (isTarget_ == 0)
	{
		pos.y = screenSize_.y / 2 - 15;
	}

	if (isTarget_ == 1)
	{
		pos.y = screenSize_.y / 2 + 90;
	}
	pos.y += 13;
	DrawRotaGraph(pos.x - 10, pos.y, 1.0, sterangle_, lpImglMng.GetGraphHandle("ster.png"), true);
	//DrawTriangle(pos.x - 20, pos.y - 15, pos.x - 20, pos.y + 15, pos.x, pos.y, 0xffffff, false);

	Vector2 boxPos = screenSize_ / 2;
	boxPos.y = screenSize_.y / 2 - 60;
	boxPos.x -= 100;

	pos.y = screenSize_.y / 2 - 15;
	pos.x += 25;

	DrawFormatString(screenSize_.x / 2 - 55, screenSize_.y / 2 - 130, 0xffffff, "音量設定");

	DrawGraph(pos.x, pos.y, lpImglMng.GetGraphHandle("bars.png"), true);
	DrawBox(pos.x, pos.y, pos.x + 165, pos.y + 25, 0xffffff, false);
	int circlePosx;
	circlePosx = static_cast<int>((tmpSoundVol_) / 150.0f * 205.0f);
	circlePosx += pos.x;
	DrawCircle(circlePosx, pos.y + 13, 16, 0xffffff, true);

	DrawFormatString(screenSize_.x / 2 - 100, screenSize_.y / 2 + 90, 0xffffff, "もどる");
}

void PoseScene::BrightUpdate()
{
	if (lpPadMng.GetControllerData(InputID::Up) || lpKeyMng.CheckKeyTrg(KeyBindID::Up))
	{
		lpSoundMng.SoundPlay("botan.mp3");
		isTarget_--;
	}
	if (lpPadMng.GetControllerData(InputID::Down) || lpKeyMng.CheckKeyTrg(KeyBindID::Down))
	{
		lpSoundMng.SoundPlay("botan.mp3");
		isTarget_++;
	}
	if (isTarget_ < 0)
	{
		isTarget_ = 0;
	}
	if (isTarget_ > 1)
	{
		isTarget_ = 1;
	}
	if (isTarget_ == 0)
	{
		if (lpPadMng.GetNowControllerData(InputID::Right) || lpKeyMng.CheckKeyNow(KeyBindID::Right))
		{
			tmpbright_++;
		}
		if (lpPadMng.GetNowControllerData(InputID::Left) || lpKeyMng.CheckKeyNow(KeyBindID::Left))
		{
			tmpbright_--;
		}
		if (tmpbright_ < 50)
		{
			tmpbright_ = 50;
		}
		if (tmpbright_ > 255)
		{
			tmpbright_ = 255;
		}
	}
	if (lpPadMng.GetControllerData(InputID::BtnB) || lpKeyMng.CheckKeyTrg(KeyBindID::Ok))
	{
		lpSoundMng.SoundPlay("pusbotan.mp3");
		if (isTarget_ == 1)
		{
			lpReadMng.SetDate(setinglist::Bright, tmpbright_);
			lpImglMng.SetBright(tmpbright_);
			setingNum_ = 0;
			isTarget_ = 0;
		}
	}
	if (lpPadMng.GetControllerData(InputID::BtnA) || lpKeyMng.CheckKeyTrg(KeyBindID::No))
	{
		lpSoundMng.SoundPlay("pusbotan.mp3");
		tmpbright_ = bright_;
		isTarget_ = 0;
		setingNum_ = 0;
		isTarget_ = 0;
	}
}

void PoseScene::BrightDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(0, 0, screenSize_.x, screenSize_.y, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	DrawBox(screenSize_.x / 2 - 125, screenSize_.y / 2 - 100, screenSize_.x / 2 + 150, screenSize_.y / 2 + 125, 0x121212, true);

	Vector2 pos;
	pos.x = screenSize_.x / 2 - 100;

	if (isTarget_ == 0)
	{
		pos.y = screenSize_.y / 2 - 15;
	}

	if (isTarget_ == 1)
	{
		pos.y = screenSize_.y / 2 + 90;
	}
	pos.y += 13;
	DrawRotaGraph(pos.x - 10, pos.y, 1.0, sterangle_, lpImglMng.GetGraphHandle("ster.png"), true);
	//DrawTriangle(pos.x - 20, pos.y - 15, pos.x - 20, pos.y + 15, pos.x, pos.y, 0xffffff, false);

	Vector2 boxPos = screenSize_ / 2;
	boxPos.y = screenSize_.y / 2 - 60;
	boxPos.x -= 100;
	DrawBox(boxPos.x, boxPos.y - 25, boxPos.x + 220, boxPos.y + 100, 0x000000, true);
	SetDrawArea(boxPos.x, boxPos.y, boxPos.x + 220, boxPos.y + 25);

	boxPos.x += 20;

	SetDrawBright(tmpbright_, tmpbright_, tmpbright_);
	DrawBox(boxPos.x, boxPos.y, boxPos.x + 25, boxPos.y + 25, 0xff0000, true);
	boxPos.x += 50;
	DrawBox(boxPos.x, boxPos.y, boxPos.x + 25, boxPos.y + 25, 0x00ff00, true);
	boxPos.x += 50;
	DrawBox(boxPos.x, boxPos.y, boxPos.x + 25, boxPos.y + 25, 0x0000ff, true);
	boxPos.x += 50;
	DrawBox(boxPos.x, boxPos.y, boxPos.x + 25, boxPos.y + 25, 0xffffff, true);

	SetDrawArea(0, 0, screenSize_.x, screenSize_.y);

	SetDrawBright(255, 255, 255);

	pos.y = screenSize_.y / 2 - 15;
	pos.x += 25;

	DrawFormatString(screenSize_.x / 2 - 55, screenSize_.y / 2 - 130, 0xffffff, "明るさ設定");

	DrawGraph(pos.x, pos.y, lpImglMng.GetGraphHandle("barg.png"), true);
	DrawBox(pos.x, pos.y, pos.x + 165, pos.y + 25, 0xffffff, false);
	int circlePosx;
	circlePosx = static_cast<int>((tmpbright_ - 50) / 255.0f * 205.0f);
	circlePosx += pos.x;
	DrawCircle(circlePosx, pos.y + 13, 16, 0xffffff, true);

	DrawFormatString(screenSize_.x / 2 - 100, screenSize_.y / 2 + 90, 0xffffff, "もどる");
}