#include <DxLib.h>
#include "Monster.h"
#include "ImageMng.h"
#include "RightHandSearch.h"
#include "MonsterMng.h"

Monster::Monster()
{
	nowMoveVec_ = 0;
	hp_ = 1;
	pos_ = { 0,0 };
	dir_ = MoveDir::None;
	MoveF_ = true;
	MoveFCon_ = 0.0f;
	oneTimeRetreatF_ = false;
	MoveF_ = false;
	MoveFCon_ = 0.0f;
}

Monster::~Monster()
{
}

void Monster::Update(void)
{
	if (!DoMove())
	{
		return;
	}

	DefoltMove(lpCronoMng.GetDeltaTime());

	Vector2 tmpPos = WFUtility::VecFltToVecInt(pos_);

	if (Vector2(tmpPos.x / 32 * 32, tmpPos.y / 32 * 32) == tmpPos)
	{
		Vector2 tpos = tmpPos / 32;
		ChangeNone();
		dir_ = lpRHSMng.CheckMoveRL(tpos, dir_);
	}
}

void Monster::Draw()
{
	Vector2 pos = { static_cast<int>(pos_.x) + mapPos_.x + 155, static_cast<int>(pos_.y) + mapPos_.y + 65 -32};
	DrawCheck(pos);
	lpImglMng.GraphAddDrawQue("testC2.png", pos, 22);
}

void Monster::Init()
{
	hp_ = 0;
	atk_ = 0;
	id_ = ObjectID::Monster;
	hp_ = lpMonsterMng.GetSlimeDate().first;
	atk_ = lpMonsterMng.GetSlimeDate().second;
	defhp_ = hp_;
}

void Monster::SetStatus(int num)
{
	atk_ += 0.3 * num;
	hp_ += 0.3 * num;
}

void Monster::Damage(Explorer& target)
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
		hp_ -= target.GetAtk();
	}
	if (hp_ <= 0)
	{
		lpSoundMng.SoundPlay("baki.mp3");
	}
}