#include "Explorer.h"
#include "RightHandSearch.h"
#include "ImageMng.h"
#include "CronoMng.h"

Vector2 Explorer::mapPos_ = { 0,0 };

Explorer::Explorer()
{
	nowMoveVec_ = 0;
	hp_ = 1;
	pos_ = { 0,0 };
	dir_ = MoveDir::None;
	MoveF_ = true;
	MoveFCon_ = 0.0f;
	oneTimeRetreatF_ = false;
}

Explorer::~Explorer()
{
}

void Explorer::Update(void)
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
		if (dir.up && dir.right && dir.down && dir.left)
		{
			dir_ = lpRHSMng.CheckMoveSweev(tmpPos / 32, dir_);
		}
		else
		{
			dir_ = lpRHSMng.CheckMoveRL(tmpPos / 32, dir_);
		}
	}
}

void Explorer::ChangeNone()
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
	}
}

void Explorer::DefoltMove(float deltaTime)
{
	if (dir_ == MoveDir::Up)
	{
		pos_.y += -30 * deltaTime;
	}
	else if (dir_ == MoveDir::Right)
	{
		pos_.x += 30 * deltaTime;
	}
	else if (dir_ == MoveDir::Down)
	{
		pos_.y += 30 * deltaTime;
	}
	else if (dir_ == MoveDir::Left)
	{
		pos_.x += -30 * deltaTime;
	}
}

void Explorer::MoveMagic(Vector2& mdir, float deltaTime)
{
	pos_.x += mdir.x * deltaTime;
	pos_.y += mdir.y * deltaTime;
}

void Explorer::MoveNext(Vector2& tpos)
{
	if (dir_ == MoveDir::Up)
	{
		tpos.y--;
	}
	if (dir_ == MoveDir::Right)
	{
		tpos.x++;
	}
	if (dir_ == MoveDir::Down)
	{
		tpos.y++;
	}
	if (dir_ == MoveDir::Left)
	{
		tpos.x--;
	}
}

void Explorer::Draw()
{
}

bool Explorer::DrawCheck(Vector2& pos)const
{
	if (pos.x - 32 > 1096 || pos.y - 32 > 601 || pos.x + 32 <= 128 || pos.y + 32 < 51)
	{
		return false;
	}
	return true;
}

void Explorer::Init()
{
}

void Explorer::HitCheck(Explorer& target)
{
	Vector2 tpos = WFUtility::VecFltToVecInt(pos_);
	Vector2 pos = target.GetPos();

	switch (dir_)
	{
	case MoveDir::Up:
		if (pos.x + 5 <= tpos.x + 32 - 5 &&
			tpos.x + 5 <= pos.x + 32 - 5 &&
			pos.y - 1 + 5 <= tpos.y + 32 - 5 &&
			tpos.y + 5 <= pos.y + 32 - 5)
		{
			Damage(target);
		}
		break;
	case MoveDir::Right:
		if (pos.x + 5 <= tpos.x + 32 - 5 &&
			tpos.x + 5 <= pos.x + 32 + 1 - 5 &&
			pos.y + 5 <= tpos.y + 32 - 5 &&
			tpos.y + 5 <= pos.y + 32 - 5)
		{
			Damage(target);
		}
		break;
	case MoveDir::Down:
		if (pos.x + 5 <= tpos.x + 32 - 5 &&
			tpos.x + 5 <= pos.x + 32 - 5 &&
			pos.y + 5 <= tpos.y + 32 - 5 &&
			tpos.y + 5 <= pos.y + 32 + 1 - 5)
		{
			Damage(target);
		}
		break;
	case MoveDir::Left:
		if (pos.x - 1 + 5 <= tpos.x + 32 - 5 &&
			tpos.x + 5 <= pos.x + 32 - 5 &&
			pos.y + 5 <= tpos.y + 32 - 5 &&
			tpos.y + 5 <= pos.y + 32 - 5)
		{
			Damage(target);
		}
		break;
	default:
		break;
	}
}

void Explorer::HitAttack(float atk)
{
	MoveF_ = false;
	MoveFCon_ = 0.0f;
	hp_ -= atk;
}

bool Explorer::DoMove()
{
	if (hp_ > defhp_)
	{
		hp_ = defhp_;
	}

	if (!MoveF_)
	{
		if (MoveFCon_ > 1.0f)
		{
			MoveF_ = true;
		}
		
		MoveFCon_ += lpCronoMng.GetDeltaTime();
		return false;
	}
	return true;
}