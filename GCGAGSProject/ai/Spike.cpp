#include <DxLib.h>
#include "Spike.h"
#include "ImageMng.h"
#include "RightHandSearch.h"

Spike::Spike()
{
}

Spike::~Spike()
{
}

void Spike::Update(void)
{
	MoveF_ = true;	
	ChangeNone();
}

void Spike::Draw()
{
	Vector2 pos = { static_cast<int>(pos_.x) + mapPos_.x + 155, static_cast<int>(pos_.y) + mapPos_.y + 65 };
	DrawCheck(pos);
	lpImglMng.GraphAddDrawQue("drop.png", pos, 20);
}

void Spike::Init()
{
	id_ = ObjectID::Spike;
	hp_ = 1;
	atk_ = 60.0f;
	defhp_ = hp_;
}

void Spike::Damage(Explorer& target)
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
