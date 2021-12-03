#include <math.h>
#include <DxLib.h>
#include "Rook.h"
#include "ImageMng.h"
#include "RightHandSearch.h"
#include "MonsterMng.h"

Rook::Rook()
{
	nowMoveVec_ = 0;
	hp_ = 1;
	pos_ = { 0,0 };
	dir_ = MoveDir::None;
	oneTimeRetreatF_ = false;
	MoveF_ = false;
	MoveFCon_ = 0.0f;
}

Rook::~Rook()
{
}

void Rook::Update(void)
{
	//if (!DoMove())
	//{
	//	return;
	//}
	if (!MoveF_)
	{
		if (MoveFCon_ > 0.5)
		{
			MoveF_ = true;
		}

		MoveFCon_ += lpCronoMng.GetDeltaTime();
		return;
	}
	//DefoltMove(lpCronoMng.GetDeltaTime());

	//Vector2 tmpPos = WFUtility::VecFltToVecInt(pos_);

	//if (Vector2(tmpPos.x / 32 * 32, tmpPos.y / 32 * 32) == tmpPos)
	//{
	//	Vector2 tpos = tmpPos / 32;
	//	ChangeNone();
	//	dir_ = lpRHSMng.CheckMoveRL(tpos, dir_);
	//}
}

void Rook::Draw()
{
	Vector2 pos = { static_cast<int>(pos_.x) + mapPos_.x + 155, static_cast<int>(pos_.y) + mapPos_.y + 65 - 32 };
	if (!DrawCheck(pos))
	{
		return;
	}
	lpImglMng.GraphAddDrawQue("testC4.png", pos, 22);
}

void Rook::Init()
{
	hp_ = 0;
	atk_ = 0;
	id_ = ObjectID::Rook;
	hp_ = lpMonsterMng.GetRookDate().first;
	atk_ = lpMonsterMng.GetRookDate().second;
	defhp_ = hp_;
}

void Rook::Damage(Explorer& target)
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