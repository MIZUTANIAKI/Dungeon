#include <DxLib.h>
#include "EnemyPawn.h"
#include "RightHandSearch.h"
#include "ImageMng.h"
#include "MoneyMng.h"

EnemyPawn::EnemyPawn()
{
	nowMoveVec_ = 0;
	hp_ = 1;
	pos_ = { 0,0 };
	dir_ = MoveDir::None;
	MoveF_ = true;
	MoveFCon_ = 1.0f;
	oneTimeRetreatF_ = false;
}

EnemyPawn::~EnemyPawn()
{
}

void EnemyPawn::Update(void)
{
	if (!DoMove())
	{
		return;
	}
	DefoltMove(lpCronoMng.GetDeltaTime());
	Vector2 tmpPos = WFUtility::VecFltToVecInt(pos_);
	if (Vector2(tmpPos.x / 32 * 32, tmpPos.y / 32 * 32) == tmpPos)
	{
		ChangeNone();
		auto dir = lpRHSMng.GetMapChipHit(tmpPos / 32);

		{
			if (dir.up && dir.right && dir.down && dir.left)
			{
				dir_ = lpRHSMng.CheckMoveSweev(tmpPos / 32, dir_); \
			}
			else
			{
				if (rand() % 2)
				{
					dir_ = lpRHSMng.CheckMove(tmpPos / 32, dir_);
				}
				else
				{
					dir_ = lpRHSMng.CheckMoveL(tmpPos / 32, dir_);
				}
			}
		}
	}
	/*if (WFUtility::VecFltToVecInt(pos_) <= goalPos_ && WFUtility::VecFltToVecInt(pos_) >= goalPos_)
	{
		hp_ = 0;
		return;
	}
	if (!DoMove())
	{
		if (static_cast<size_t>(nowMoveVec_) >= moveVec_.size())
		{
			hp_ = 0;
		}
		return;
	}
	if (!moveVec_.empty())
	{
		MoveTo(lpCronoMng.GetDeltaTime());
		return;
	}
	DefoltMove(lpCronoMng.GetDeltaTime());
	Vector2 tmpPos = WFUtility::VecFltToVecInt(pos_);
	if (Vector2(tmpPos.x / 32 * 32, tmpPos.y / 32 * 32) == tmpPos)
	{
		if (dir_ == MoveDir::None)
		{
			int tnum = rand() % 5;
			if (tnum == 0)
			{
				dir_ = MoveDir::Up;
			}
			if (tnum == 1)
			{
				dir_ = MoveDir::Right;
			}
			if (tnum == 2)
			{
				dir_ = MoveDir::Down;
			}
			if (tnum == 3)
			{
				dir_ = MoveDir::Left;
			}
		}

		ChangeNone();
		auto dir = lpRHSMng.GetMapChipHit(tmpPos / 32);
		if (dir.up && dir.right && dir.down && dir.left)
		{
			dir_ = lpRHSMng.CheckMoveSweev(tmpPos / 32, dir_);
		}
		else
		{
			dir_ = lpRHSMng.CheckMoveL(tmpPos / 32, dir_);
		}
	}*/
}

void EnemyPawn::SetStatus(int num)
{
	atk_ += 0.3 * num;
	hp_ += 0.3 * num;
}

void EnemyPawn::MoveTo(float deltaTime)
{
	if (static_cast<size_t>(nowMoveVec_) >= moveVec_.size())
	{
		return;
	}
	if ((moveVec_[nowMoveVec_].x * 32) - WFUtility::VecFltToVecInt(pos_).x > 0)
	{
		pos_.x += 30 * deltaTime;
		dir_ = MoveDir::Right;
	}
	else
		if ((moveVec_[nowMoveVec_].x * 32) - WFUtility::VecFltToVecInt(pos_).x < 0)
		{
			pos_.x += -30 * deltaTime;
			dir_ = MoveDir::Left;
		}
		else
			if ((moveVec_[nowMoveVec_].y * 32) - WFUtility::VecFltToVecInt(pos_).y > 0)
			{
				pos_.y += 30 * deltaTime;
				dir_ = MoveDir::Down;
			}
			else
				if ((moveVec_[nowMoveVec_].y * 32) - WFUtility::VecFltToVecInt(pos_).y < 0)
				{
					pos_.y += -30 * deltaTime;
					dir_ = MoveDir::Up;
				}
	if (Vector2(moveVec_[nowMoveVec_].x * 32, moveVec_[nowMoveVec_].y * 32) == WFUtility::VecFltToVecInt(pos_))
	{
		if (static_cast<size_t>(nowMoveVec_) + static_cast<size_t>(1) < moveVec_.size())
		{
			nowMoveVec_++;
		}
		else
		{
			hp_ = 0;
			moveVec_.clear();
		}
	}
}

void EnemyPawn::Draw()
{
	Vector2 pos = { static_cast<int>(pos_.x) + mapPos_.x + 155, static_cast<int>(pos_.y) + mapPos_.y + 65 - 32 };
	DrawCheck(pos);
	lpImglMng.GraphAddDrawQue("testP3.png", pos, 21);
}

void EnemyPawn::Init()
{
	id_ = ObjectID::Pawn;
	hp_ = 0.0f;
	atk_ = 1.0f;
}

void EnemyPawn::Damage(Explorer& target)
{
	if (ObjectID::Goal == target.GetObjectID())
	{
		if (oneTimeRetreatF_)
		{
			return;
		}
		oneTimeRetreatF_ = true;
	}
	if (ObjectID::Monster == target.GetObjectID())
	{
		HitAttack(target.GetAtk());
	}
	if (ObjectID::Desmodus == target.GetObjectID())
	{
		HitAttack(target.GetAtk());
	}
	if (ObjectID::Gate == target.GetObjectID())
	{
		HitAttack(target.GetAtk());
	}
	if (ObjectID::Spike == target.GetObjectID())
	{
		hp_ -= target.GetAtk();
	}
	if (ObjectID::Rook == target.GetObjectID())
	{
		hp_ -= target.GetAtk();
	}
	if (ObjectID::Fire == target.GetObjectID())
	{
		hp_ -= target.GetAtk();
	}
	if (hp_ <= 0)
	{
		lpMoneyMng.AddTmpMoney(2);
		lpSoundMng.SoundPlay("baki.mp3");
	}
}