#include <DxLib.h>
#include "KeyMng.h"
#include "KeyCtl.h"

KeyMng* KeyMng::sInstance = nullptr;

void KeyMng::Update(void)
{
	keyCtl_->Update();
}

bool KeyMng::CheckKeyNow(KeyBindID id)
{
	return keyCtl_->CheckKeyNow(id);
}

bool KeyMng::CheckKeyTrg(KeyBindID id)
{
	return keyCtl_->CheckKeyTrg(id);
}

KeyMng::KeyMng()
{
	keyCtl_ = std::make_unique< KeyCtl>();
}

KeyMng::~KeyMng()
{
}
