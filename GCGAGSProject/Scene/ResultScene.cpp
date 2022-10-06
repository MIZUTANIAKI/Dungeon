#include <DxLib.h>
#include "ResultScene.h"
#include "ImageMng.h"
#include "CronoMng.h"
#include "PadMng.h"
#include "KeyMng.h"
#include "moneyMng.h"
#include "soundMng.h"
#include "StatusCtr.h"
#include "ReadMng.h"
#include "MouseMng.h"
#include "MapMng.h"


UNBS ResultScene::Update(UNBS own)
{
	if (!lpSoundMng.CheckPlaySound("fanfan.mp3"))
	{
		if (!lpSoundMng.CheckPlaySound("finfin.mp3"))
		{
			lpSoundMng.SoundPlay("finfin.mp3");
		}
	}
	Vector2 mpos = lpMouseMng.GetMousePos();
	if (mpos.x > screenSize_.x / 2 - 450 &&
		mpos.x < screenSize_.x / 2 - 350)
	{
		if (isTarget_ != 0)
		{
			lpSoundMng.SoundPlay("botan.mp3");
		}
		isTarget_ = 0;
	}
	if (mpos.x > screenSize_.x / 2 - 200 &&
		mpos.x < screenSize_.x / 2 - 100)
	{
		if (isTarget_ != 1)
		{
			lpSoundMng.SoundPlay("botan.mp3");
		}
		isTarget_ = 1;
	}
	if (mpos.x > screenSize_.x / 2 + 100 &&
		mpos.x < screenSize_.x / 2 + 200)
	{
		if (isTarget_ != 2)
		{
			lpSoundMng.SoundPlay("botan.mp3");
		}
		isTarget_ = 2;
	}
	if (mpos.x > screenSize_.x / 2 + 350 &&
		mpos.x < screenSize_.x / 2 + 450)
	{
		if (isTarget_ != 3)
		{
			lpSoundMng.SoundPlay("botan.mp3");
		}
		isTarget_ = 3;
	}
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
	if (lpPadMng.GetControllerData(InputID::BtnB) || lpKeyMng.CheckKeyTrg(KeyBindID::Ok) || (lpMouseMng.GetInputDat() & MOUSE_INPUT_LEFT && !(lpMouseMng.GetOldInputDat() & MOUSE_INPUT_LEFT)))
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
				isTarget_ = 1;
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
	if (lpPadMng.GetControllerData(InputID::BtnA) || lpKeyMng.CheckKeyTrg(KeyBindID::No) || (lpMouseMng.GetInputDat() & MOUSE_INPUT_RIGHT && !(lpMouseMng.GetOldInputDat() & MOUSE_INPUT_RIGHT)))
	{
		lpSoundMng.SoundPlay("pusbotan.mp3");
		isTarget_ = 1;
		if (resultNum_ == 0)
		{
			lpReadMng.SetDate(setinglist::Money, lpMoneyMng.GetMoney());
			StatusCtr::SetStates(StatusID::Stage, StatusCtr::GetStates(StatusID::Stage) + 1);
			return std::move(ownS_);
		}
		else
		{
			resultNum_ = 0;
		}
	}

	//else if (graphY_ < 0)
	//{
	//	graphSpeedY_ = 0.5;
	//}

	graphY_ += graphSpeedY_;
	if (graphY_ > 30)
	{
		ChangeVolumeSoundMem(paVal_,lpSoundMng.GetSoundHandle("pa.mp3"));
		paVal_--;
		lpSoundMng.SoundPlay("pa.mp3");
		graphSpeedY_ = 10;
		graphSpeedY_ *= -1;
	}
	else
	{
		graphSpeedY_++;
	}

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
	lpImglMng.DeleteGraph("gameWin.png");
	lpImglMng.DeleteGraph("backGL.png");
}

void ResultScene::Draw()
{
	ownS_->Draw();
	SetDrawScreen(screenH_);
	ClsDrawScreen();
	DrawGraph(0, 0, lpImglMng.GetGraphHandle("backGL.png"), true);
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	//DrawBox(0, -screenSize_.y, screenSize_.x, screenSize_.y, 0x000000, true);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//lpImglMng.DrawImg("gameWin.png", { 0,static_cast<int>(graphY_) - 50 /*% 30 - 50*/ });
	DrawGraph(0, static_cast<int>(graphY_) - 50, lpImglMng.GetGraphHandle("gameWin.png"), true);

	DrawFormatString(screenSize_.x / 3, screenSize_.y / 2 - 160, 0xffffff, "���݂̃X�e�[�W�́@%4d", StatusCtr::GetStates(StatusID::Stage));
	DrawFormatString(screenSize_.x / 3, screenSize_.y / 2 - 140, 0xffffff, "�Q�b�g�����S�[���h�@%4d", resultMoney_);
	DrawFormatString(screenSize_.x / 3, screenSize_.y / 2 - 100, 0xffffff, "�����Ă���S�[���h�@%4d", lpMoneyMng.GetMoney());
	DrawFormatString(screenSize_.x / 4, screenSize_.y / 2 - 50, 0xffffff, "���傤�����������̂�I��ł��������@���i100�S�[���h");

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
	if (isTarget_ == 0)
	{
		if (resultNum_ == 0)
		{
			DrawFormatString(screenSize_.x / 4, screenSize_.y / 2, 0xffffff, "�}�b�v�� ���Ă̂Ȃ����� �ӂ����B\n���܂� �}�b�v���x���@%d", StatusCtr::GetStates(StatusID::MapSize) - 11);
		}
		else
		{
			DrawFormatString(screenSize_.x / 4, screenSize_.y / 2, 0xffffff, "�r�V���b�v�� �������A����������傭�� �������B\n���܂� �r�V���b�v���x���@%d", StatusCtr::GetStates(StatusID::Monster3));
		}
	}
	if (isTarget_ == 1)
	{
		if (resultNum_ == 0)
		{
			DrawFormatString(screenSize_.x / 4, screenSize_.y / 2, 0xffffff, "�|�[���� �������A����������傭�� �������\n���܂� �|�[�����x���@%d", StatusCtr::GetStates(StatusID::Monster1));
		}
		else
		{
			DrawFormatString(screenSize_.x / 4, screenSize_.y / 2, 0xffffff, "�X�p�C�N�� �������A����������傭�� �������\n���܂� �X�p�C�N���x���@%d", StatusCtr::GetStates(StatusID::GImmick1));
		}
	}
	if (isTarget_ == 2)
	{
		if (resultNum_ == 0)
		{
			DrawFormatString(screenSize_.x / 4, screenSize_.y / 2, 0xffffff, "���[�N�� �������A����������傭�� �������\n���܂� ���[�N���x���@%d", StatusCtr::GetStates(StatusID::Monster2));
		}
		else
		{
			DrawFormatString(screenSize_.x / 4, screenSize_.y / 2, 0xffffff, "�ڂ��ւ��� �������� �������\n���܂� �ڂ��ւ����x���@%d", StatusCtr::GetStates(StatusID::GImmick2));
		}
	}
	if (isTarget_ == 3)
	{
		if (resultNum_ == 0)
		{
			DrawFormatString(screenSize_.x / 4, screenSize_.y / 2, 0xffffff, "�ق��� ���񂽂��� ���݂�");
		}
		else
		{
			DrawFormatString(screenSize_.x / 4, screenSize_.y / 2, 0xffffff, "����Ă�� �������A�G�l���M�[�����ӂ������ǂ� �������\n���܂̂���Ă񃌃x���@%d", StatusCtr::GetStates(StatusID::PlayerHP));
		}
	}
	DrawName();

	if (resultNum_ == 0)
	{
		DrawFormatString(screenSize_.x / 2 - 50, screenSize_.y - 100, 0xffffff, "�݂��N���b�N�ŃL�����Z������");
	}
	else
	{
		DrawFormatString(screenSize_.x / 2 - 50, screenSize_.y - 100, 0xffffff, "�݂��N���b�N�ŃQ�[���ɂ��ǂ�");
	}

	lpImglMng.ScreenAddDrawQue(screenH_, 49);
}

void ResultScene::DrawName()
{
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
		DrawFormatString(screenSize_.x / 2 - 450, screenSize_.y - screenSize_.y / 5, 0xffffff, "�}�b�v");
	}
	else
	{
		DrawFormatString(screenSize_.x / 2 - 450, screenSize_.y - screenSize_.y / 5, 0xffffff, "�r�V���b�v");
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
		DrawFormatString(screenSize_.x / 2 - 200, screenSize_.y - screenSize_.y / 5, 0xffffff, "�|�[��");
	}
	else
	{
		DrawFormatString(screenSize_.x / 2 - 200, screenSize_.y - screenSize_.y / 5, 0xffffff, "�X�p�C�N");
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
		DrawFormatString(screenSize_.x / 2 + 100, screenSize_.y - screenSize_.y / 5, 0xffffff, "���[�N");
	}
	else
	{
		DrawFormatString(screenSize_.x / 2 + 100, screenSize_.y - screenSize_.y / 5, 0xffffff, "�ڂ��ւ�");
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
		DrawFormatString(screenSize_.x / 2 + 350, screenSize_.y - screenSize_.y / 5, 0xffffff, "�ق�");
	}
	else
	{
		DrawFormatString(screenSize_.x / 2 + 350, screenSize_.y - screenSize_.y / 5, 0xffffff, "���Ԃ�");
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void ResultScene::SetOwn(UNBS own)
{
	ownS_ = std::move(own);
}

void ResultScene::Init(void)
{
	lpSoundMng.StopSound("game.mp3");
	lpSoundMng.LoadSound("pa.mp3");
	lpSoundMng.LoadSound("fanfan.mp3");
	lpSoundMng.LoadSound("finfin.mp3");
	lpSoundMng.SoundPlay("fanfan.mp3");
	resultMoney_ = lpMoneyMng.GettmpMoney();
	lpMoneyMng.AddMoney(resultMoney_);

	lpReadMng.SetDate(setinglist::Money, lpMoneyMng.GetMoney());
	isTarget_ = 0;
	time_ = 0;
	graphSpeedY_ = 0.5f;
	graphY_ = 21;
	GetDrawScreenSize(&screenSize_.x, &screenSize_.y);
	screenH_ = MakeScreen(screenSize_.x, screenSize_.y, true);
	lpImglMng.LoadGraph("gameWin.png");
	lpImglMng.LoadGraph("backGL.png");
	lpSoundMng.LoadSound("not.mp3"); 

	paVal_ = lpSoundMng.GetSoundVol();

	lpMapMng.GetDropEndF(MapDropDateID::Desmodus);
	lpMapMng.GetDropEndF(MapDropDateID::Gate);
	lpMapMng.GetDropEndF(MapDropDateID::Rook);
	lpMapMng.GetDropEndF(MapDropDateID::Slime);
	lpMapMng.GetDropEndF(MapDropDateID::Spike);
}
