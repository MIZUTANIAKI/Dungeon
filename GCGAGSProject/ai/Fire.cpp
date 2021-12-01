#include <math.h>
#include <DxLib.h>
#include "Fire.h"
#include "ImageMng.h"
#include "RightHandSearch.h"
#include "MonsterMng.h"

Fire::Fire()
{
	nowMoveVec_ = 0;
	hp_ = 1;
	pos_ = { 0,0 };
	dir_ = MoveDir::None;
	oneTimeRetreatF_ = false;
	MoveF_ = false;
	timecount_ = 0.0f;
	MoveFCon_ = 0.0f;
}

Fire::~Fire()
{
}

void Fire::Update(void)
{
	//if (!DoMove())
	//{
	//	return;
	//}

	MoveFCon_ += lpCronoMng.GetDeltaTime();

	MoveMagic(moveDir_, lpCronoMng.GetDeltaTime());
	if (MoveFCon_ > 0.3f)
	{
		hp_ = 0;
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
 
void Fire::Draw()
{
	Vector2 pos = { static_cast<int>(pos_.x) + mapPos_.x + 155, static_cast<int>(pos_.y) + mapPos_.y + 65 };
	DrawCheck(pos);

	if (ObjectID::Fire == id_)
	{
		lpImglMng.GraphAddDrawQue("fire.png", pos, 22);
	}
	else
	{
		lpImglMng.GraphAddDrawQue("dfire.png", pos, 22);
	}
}

void Fire::Init()
{
	id_ = ObjectID::Fire;
	hp_ = 1.0f;
	atk_ = 0.5f;
	defhp_ = hp_;
}

void Fire::SetEneF(void)
{
	id_ = ObjectID::EFire;
}

void Fire::Damage(Explorer& target)
{
	if (ObjectID::Adventurer == target.GetObjectID())
	{
		HitAttack(target.GetAtk());
	}
}