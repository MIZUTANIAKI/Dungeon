#include <DxLib.h>
#include "KeyCtl.h"

KeyCtl::KeyCtl()
{
	keyDate_.try_emplace(KeyBindID::Up,false);
	keyDate_.try_emplace(KeyBindID::Right,false);
	keyDate_.try_emplace(KeyBindID::Down,false);
	keyDate_.try_emplace(KeyBindID::Left,false);
	keyDate_.try_emplace(KeyBindID::Ok,false);
	keyDate_.try_emplace(KeyBindID::No,false);
	oldKeyDate_ = keyDate_;
}

void KeyCtl::Update(void)
{
	oldKeyDate_ = keyDate_;
	GetHitKeyStateAll(KeyBuf);
	SetKeyDate(KeyBindID::Up, false);
	SetKeyDate(KeyBindID::Right, false);
	SetKeyDate(KeyBindID::Left, false);
	SetKeyDate(KeyBindID::Down, false);
	SetKeyDate(KeyBindID::Up, false);
	SetKeyDate(KeyBindID::Ok, false);
	SetKeyDate(KeyBindID::No, false);
	CheckKeyHit();
}

bool KeyCtl::CheckKeyNow(KeyBindID id)
{
	return GetKeyDate(id);
}

bool KeyCtl::CheckKeyOld(KeyBindID id)
{
	return GetOldKeyDate(id);
}

bool KeyCtl::CheckKeyTrg(KeyBindID id)
{
	return GetKeyDate(id) && !GetOldKeyDate(id);
}

void KeyCtl::CheckKeyHit(void)
{
	if (KeyBuf[KEY_INPUT_UP] || KeyBuf[KEY_INPUT_W])
	{
		SetKeyDate(KeyBindID::Up, true);
	}
	if (KeyBuf[KEY_INPUT_RIGHT] || KeyBuf[KEY_INPUT_D])
	{
		SetKeyDate(KeyBindID::Right, true);
	}
	if (KeyBuf[KEY_INPUT_DOWN] || KeyBuf[KEY_INPUT_S])
	{
		SetKeyDate(KeyBindID::Down, true);
	}
	if (KeyBuf[KEY_INPUT_LEFT] || KeyBuf[KEY_INPUT_A])
	{
		SetKeyDate(KeyBindID::Left, true);
	}
	if (KeyBuf[KEY_INPUT_Z] || KeyBuf[KEY_INPUT_RETURN] || KeyBuf[KEY_INPUT_NUMPADENTER])
	{
		SetKeyDate(KeyBindID::Ok, true);
	}
	if (KeyBuf[KEY_INPUT_X])
	{
		SetKeyDate(KeyBindID::No, true);
	}
	if (KeyBuf[KEY_INPUT_P])
	{
		SetKeyDate(KeyBindID::Pose, true);
	}
}

void KeyCtl::SetKeyDate(KeyBindID id, bool flg)
{
	if (keyDate_.find(id) == keyDate_.end())
	{
		return;
	}
	keyDate_.at(id) = flg;
}

bool KeyCtl::GetKeyDate(KeyBindID id)
{
	if (keyDate_.find(id) == keyDate_.end())
	{
		return false;
	}

	return keyDate_.at(id);
}

bool KeyCtl::GetOldKeyDate(KeyBindID id)
{
	if (oldKeyDate_.find(id) == oldKeyDate_.end())
	{
		return false;
	}

	return oldKeyDate_.at(id);
}
