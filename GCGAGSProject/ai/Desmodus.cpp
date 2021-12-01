#include <string>
#include <DxLib.h>
#include "Desmodus.h"
#include "ImageMng.h"
#include "RightHandSearch.h"
#include "MonsterMng.h"

Desmodus::Desmodus()
{
	nowMoveVec_ = 0;
	hp_ = 1;
	pos_ = { 0,0 };
	dir_ = MoveDir::None;
	MoveF_ = true;
	oneTimeRetreatF_ = false;
	MoveF_ = false;
	MoveFCon_ = 0.0f;
}

Desmodus::~Desmodus()
{
}

void Desmodus::Update(void)
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
}

void Desmodus::Draw()
{
	Vector2 pos = { static_cast<int>(pos_.x) + mapPos_.x + 155, static_cast<int>(pos_.y) + mapPos_.y + 65 -32};
	DrawCheck(pos);
	lpImglMng.GraphAddDrawQue("testC3.png", pos, 22);
}

void Desmodus::Init()
{
	hp_ = 0;
	atk_ = 0;
	id_ = ObjectID::Desmodus;
	hp_ = lpMonsterMng.GetDesmodusDate().first;
	atk_ = lpMonsterMng.GetDesmodusDate().second;
	defhp_ = hp_;
}

void Desmodus::Damage(Explorer& target)
{
	if (ObjectID::Adventurer == target.GetObjectID())
	{
		HitAttack(target.GetAtk());
	}
	if (ObjectID::EFire == target.GetObjectID())
	{
		HitAttack(target.GetAtk());
	}
	if (ObjectID::Knight == target.GetObjectID())
	{
		HitAttack(target.GetAtk());
	}
}