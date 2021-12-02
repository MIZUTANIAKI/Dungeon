#pragma once
#include <memory>
#include "KeyBindID.h"

#define lpKeyMng KeyMng::GetInstance()

class KeyCtl;

class KeyMng
{
public:

	static KeyMng& GetInstance(void)
	{
		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new KeyMng();
		}
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}

	void Update(void);

	bool CheckKeyNow(KeyBindID id);
	bool CheckKeyTrg(KeyBindID id);
private:
	static KeyMng* sInstance;
	std::unique_ptr< KeyCtl> keyCtl_;
	KeyMng();
	~KeyMng();
};

