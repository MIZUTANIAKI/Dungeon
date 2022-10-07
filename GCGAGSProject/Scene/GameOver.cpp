#include <DxLib.h>
#include "GameOver.h"
#include "ImageMng.h"
#include "CronoMng.h"
#include "SoundMng.h"
#include "PadMng.h"
#include "KeyMng.h"
#include "MouseMng.h"
#include "TitleScene.h"
#include "sceneMng.h"
#include "MapMng.h"

UNBS GameOver::Update(UNBS own)
{
	count_ += lpCronoMng.GetDeltaTime();
	bool finDrop = true;

	for (int i = 0; i < dropPosAngle_.size(); i++)
	{
		auto& drop = dropPosAngle_[i];
		//if (dropF_)
		//{
		//	break;
		//}
		if (drop.first.first.y > drop.first.second + 50 &&
			drop.first.first.y < drop.first.second + 60)
		{
			if (!dropFVector_[i])
			{

				int tmpSoundHandle = DuplicateSoundMem(lpSoundMng.GetSoundHandle("maki2.mp3"));
				ChangeVolumeSoundMem(lpSoundMng.GetSoundVol(), tmpSoundHandle);
				lpSoundMng.DirectSoudPlay(tmpSoundHandle);
				dropFVector_[i] = true;
				dropSoundVector_.emplace_back(tmpSoundHandle);
				if (static_cast<int>(count_ * 10) % 10 == 0)
				{
					if (i >= 2 && !lpSoundMng.CheckPlaySound("maki1.mp3"))
					{
						lpSoundMng.SoundPlay("maki1.mp3");
					}
				}
			}
		}
		else
		{
			finDrop = false;
			drop.first.first.y += drop.second.second;
			drop.second.second += rand() % 2 == 0 ? 0.001f : 0.005f;
		}
	}

	//if (screenSize_.y >= backWPosY_-1000)
	//{
	//	if (screenSize_.y == backWPosY_-1000)
	//	{
	//		lpSoundMng.SoundPlay("don.mp3");
	//	}
	//	backWPosY_ += 10;
	//}
	//else
	if (!finDrop)
	{
		backWPosY_ = dropPosAngle_[0].first.first.y+50;
	}
	else
	{
		if (!dropF_)
		{
			int tmpSoundHandle = DuplicateSoundMem(lpSoundMng.GetSoundHandle("maki2.mp3"));
			ChangeVolumeSoundMem(lpSoundMng.GetSoundVol(), tmpSoundHandle);
			lpSoundMng.DirectSoudPlay(tmpSoundHandle);
			dropSoundVector_.emplace_back(tmpSoundHandle);
			lpSoundMng.SoundPlay("don.mp3");
		}
		//backWPosY_ = screenSize_.y;
		dropF_ = true;
		time_++;
		//backWPosY_ = screenSize_.y + 200;
		if (static_cast<int>(time_) > 2)
		{
			if (lpMouseMng.GetInputDat() && !lpMouseMng.GetOldInputDat())
			{
				time_ = 0;
				pressKeyF_ = true;
			}
		}
		sterangle_ = static_cast<int>(time_ * 10) % 360;
		if (sterangle_ > 360)
		{
			sterangle_ = 0;
		}
	}
	if (pressKeyF_)
	{
		return std::move(std::make_unique<TitleScene>());
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
		if (static_cast<int>(time_) > 2)
		{
			if (lpMouseMng.GetInputDat() && !lpMouseMng.GetOldInputDat())
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
	}
	auto itr = dropSoundVector_.begin();
	while (itr != dropSoundVector_.end())
	{
		if (CheckSoundMem((*itr)) != 1)
		{
			itr = dropSoundVector_.erase(itr);
		}
		else
		{
			itr++;
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
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBox(0, backWPosY_ - screenSize_.y - 1500 , screenSize_.x, backWPosY_, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (dropF_)
	{
		DrawGraph(0, backWPosY_ - screenSize_.y - 1500, lpImglMng.GetGraphHandle("GameOverWall.png"), true);
	}
	for (int i = dropPosAngle_.size() - 1; i >= 0; i--)
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
		DrawRotaGraph(dropPosAngle_[i].first.first.x,dropPosAngle_[i].first.first.y, 10.0, dropPosAngle_[i].second.first, id, true);
	}

	if (dropF_)
	{
		int id = 0;
		if (time_ / 5 % 30 == 29 || time_ / 5 % 30 == 20)
		{
			id = lpImglMng.GetGraphHandle("GameOver2.png");
		}
		else if (time_ / 5 % 30 == 10)
		{
			id = lpImglMng.GetGraphHandle("GameOver3.png");
		}
		else
		{
			id = lpImglMng.GetGraphHandle("GameOver1.png");
		}
		if (time_ / 2 % 100 == 50)
		{
			DrawRotaGraph(screenSize_.x / 2 - 25, screenSize_.y / 2 - 20, 1, 0, id, true);
		}
		else
		{
			DrawRotaGraph(screenSize_.x / 2, screenSize_.y / 2, 1, 0, id, true);
		}

		if (time_ / 20 % 6 != 0)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
			DrawBox(screenSize_.x / 2 - 150, screenSize_.y - 200 - 5, screenSize_.x / 2 - 150 + 300, screenSize_.y - 200 + 40, 0x000000, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			DrawFormatString(screenSize_.x / 2 - 130, screenSize_.y - 200, 0xffffff, "クリックをしてください");
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
	lpImglMng.ScreenAddDrawQue(screenH_, 69);
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
	lpSoundMng.LoadSound("maki1.mp3");
	lpSoundMng.LoadSound("maki2.mp3");
	lpSoundMng.SoundPlay("boon.mp3");
	isTarget_ = 0;
	sterangle_ = 0;
	pressKeyF_ = false;
	dropF_ = false;
	backWPosY_ = 0;
	GetDrawScreenSize(&screenSize_.x, &screenSize_.y);
	screenH_ = MakeScreen(screenSize_.x, screenSize_.y, true);
	lpImglMng.LoadGraph("GameOverWall.png");
	lpImglMng.LoadGraph("GameOver1.png");
	lpImglMng.LoadGraph("GameOver2.png");
	lpImglMng.LoadGraph("GameOver3.png");
	Vector2flt pos = { 200 ,10 };
	dropPosAngle_.emplace_back(std::pair<Vector2flt, int>(pos, screenSize_.y), std::pair<int, float>(0, 5.001f));
	dropFVector_.emplace_back(false);
	pos = { 800 ,150 };
	dropPosAngle_.emplace_back(std::pair<Vector2flt, int>(pos, screenSize_.y), std::pair<int, float>(60, 7.001f));
	dropFVector_.emplace_back(false);
	for (int i = 0; i < 100; i++)
	{
		//if (i == 30)
		//{

		//}
		//if (i == 70)
		//{

		//}
		Vector2flt pos = { static_cast<float>(rand() % (screenSize_.x - 100) + 50),static_cast<float>(-rand() % 1000 )};
		int tmpY = -static_cast<int>(pos.y) % 200;
		pos.y -= 1000;
		if (i > 30)
		{
			pos.y -= 500;
			pos.x = rand() % (screenSize_.x - 600) + 300;
			tmpY += 100;
		}
		dropPosAngle_.emplace_back(std::pair<Vector2flt, int>(pos, screenSize_.y - tmpY), std::pair<int, float>(rand() % 360, rand() % 3 + 3));
		dropFVector_.emplace_back(false);
	}

	lpMapMng.GetDropEndF(MapDropDateID::Desmodus);
	lpMapMng.GetDropEndF(MapDropDateID::Gate);
	lpMapMng.GetDropEndF(MapDropDateID::Rook);
	lpMapMng.GetDropEndF(MapDropDateID::Slime);
	lpMapMng.GetDropEndF(MapDropDateID::Spike);
	count_ = 0;
}
