#pragma once
#include <map>
#include "KeyBindID.h"

class KeyCtl
{
public:
	KeyCtl();
	void Update(void);
	bool CheckKeyNow(KeyBindID id);
	bool CheckKeyOld(KeyBindID id);
	bool CheckKeyTrg(KeyBindID id);
private:
	void CheckKeyHit(void);
	void SetKeyDate(KeyBindID id, bool flg);
	bool GetKeyDate(KeyBindID id);
	bool GetOldKeyDate(KeyBindID id);
	char KeyBuf[256];
	std::map<KeyBindID, bool> keyDate_;
	std::map<KeyBindID, bool> oldKeyDate_;
};

