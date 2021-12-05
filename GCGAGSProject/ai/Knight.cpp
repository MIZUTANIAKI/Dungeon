#include <DxLib.h>
#include "Knight.h"
#include "ImageMng.h"
#include "MoneyMng.h"

Knight::Knight()
{
	nowMoveVec_ = 0;
	hp_ = 1;
	pos_ = { 0,0 };
	dir_ = MoveDir::None;
	MoveF_ = true;
	MoveFCon_ = 0.0f;
	oneTimeRetreatF_ = false;
}

Knight::~Knight()
{
}

void Knight::Update(void)
{
	if (WFUtility::VecFltToVecInt(pos_) <= goalPos_ && WFUtility::VecFltToVecInt(pos_) >= goalPos_)
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
}

void Knight::SetStatus(int num)
{
	atk_ += 0.3 * num;
	hp_ += 0.3 * num;
}

void Knight::MoveTo(float deltaTime)
{
	if (static_cast<size_t>(nowMoveVec_) >= moveVec_.size())
	{
		return;
	}
	if ((moveVec_[nowMoveVec_].x * 32) - WFUtility::VecFltToVecInt(pos_).x > 0)
	{
		pos_.x += 20 * deltaTime;
		dir_ = MoveDir::Right;
	}
	else
		if ((moveVec_[nowMoveVec_].x * 32) - WFUtility::VecFltToVecInt(pos_).x < 0)
		{
			pos_.x += -20 * deltaTime;
			dir_ = MoveDir::Left;
		}
		else
			if ((moveVec_[nowMoveVec_].y * 32) - WFUtility::VecFltToVecInt(pos_).y > 0)
			{
				pos_.y += 20 * deltaTime;
				dir_ = MoveDir::Down;
			}
			else if ((moveVec_[nowMoveVec_].y * 32) - WFUtility::VecFltToVecInt(pos_).y < 0)
			{
				pos_.y += -20 * deltaTime;
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

void Knight::Draw()
{
	Vector2 pos = { static_cast<int>(pos_.x) + mapPos_.x + 155, static_cast<int>(pos_.y) + mapPos_.y + 65 - 32 };
	DrawCheck(pos);
	lpImglMng.GraphAddDrawQue("testP.png", pos, 21);
}

void Knight::Init()
{
	id_ = ObjectID::Knight;
	hp_ = 0.0f;
	atk_ = 10.0f;
}

void Knight::Damage(Explorer& target)
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
		lpMoneyMng.AddTmpMoney(5);
		lpSoundMng.LoadSound("baki.mp3");
	}
}