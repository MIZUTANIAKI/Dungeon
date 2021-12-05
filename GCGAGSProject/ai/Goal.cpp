#include <DxLib.h>
#include "Goal.h"
#include "ImageMng.h"
#include "RightHandSearch.h"

Goal::Goal()
{
	nowMoveVec_ = 0;
	hp_ = 1;
	pos_ = { 0,0 };
	dir_ = MoveDir::None;
	MoveF_ = true;
	MoveFCon_ = 0.0f;
	oneTimeRetreatF_ = false;
	count_ = 0;
}

Goal::~Goal()
{
}

void Goal::Update(void)
{
	if (dir_ == MoveDir::None)
	{
		int tnum = rand() % 4;
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
		dir_ = lpRHSMng.CheckMoveRL(WFUtility::VecFltToVecInt(pos_) / 32, dir_);
	}
}

void Goal::Draw()
{
	Vector2 pos = { static_cast<int>(pos_.x) + mapPos_.x + 165, static_cast<int>(pos_.y) + mapPos_.y + 55 };
	DrawCheck(pos);
	lpImglMng.GraphAddDrawQue("player.png", pos, 21);
}

void Goal::Init()
{
	id_ = ObjectID::Goal;
}

void Goal::SetStatus(int num)
{
	hp_ = num;
}

void Goal::Damage(Explorer& target)
{
	if (ObjectID::Adventurer == target.GetObjectID())
	{
		HitAttack(target.GetAtk());
	}
	if (ObjectID::Knight == target.GetObjectID())
	{
		HitAttack(target.GetAtk());
	}
	if (ObjectID::Pawn == target.GetObjectID())
	{
		HitAttack(target.GetAtk());
	}

	if (ObjectID::EFire == target.GetObjectID())
	{
		HitAttack(target.GetAtk());
	}
}