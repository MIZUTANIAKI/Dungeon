#pragma once
#include <string>
#include <map>
#include <vector>

#define lpReadMng ReadMng::GetInstance()

enum class setinglist
{
	Bright,
	SoundVol,
};

class ReadMng
{
public:

	static ReadMng& GetInstance(void)
	{
		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new ReadMng();
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

	int GetDate(setinglist set)noexcept;

	void SetDate(setinglist set, int num);

private:
	static ReadMng* sInstance;

	void OpenFile();

	int soundVol_;
	int bright_;

	ReadMng();
	~ReadMng();
};
