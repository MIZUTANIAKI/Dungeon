#include <DxLib.h>
#include "Gate.h"
#include "ImageMng.h"
#include "RightHandSearch.h"

Gate::Gate()
{
}

Gate::~Gate()
{
}

void Gate::Update(void)
{
	MoveF_ = true;
	ChangeNone();
}

void Gate::Draw()
{
	Vector2 pos = { static_cast<int>(pos_.x) + mapPos_.x+155, static_cast<int>(pos_.y) + mapPos_.y + 65 };
	DrawCheck(pos);
	lpImglMng.GraphAddDrawQue("gate.png", pos, 21);
}

void Gate::Init()
{
	id_ = ObjectID::Gate;
	hp_ = 5000;
	atk_ = 0.05f;
	defhp_ = hp_;
}

void Gate::SetStatus(int num)
{
	atk_ += 0.05f * num;
	hp_ += 0.010f * num;
}

void Gate::Damage(Explorer& target)
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
	if (hp_ <= 0)
	{
		lpSoundMng.SoundPlay("baki.mp3");
	}
}
