#pragma once
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

private:
	static KeyMng* sInstance;

	KeyMng();
	~KeyMng();
};

