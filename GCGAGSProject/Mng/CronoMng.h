#pragma once
#include <chrono>
#define lpCronoMng CronoMng::GetInstance()
class CronoMng
{
public:
	static CronoMng& GetInstance(void)
	{
		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new CronoMng();
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
	void Start();
	void Last();
	float GetDeltaTime()const noexcept
	{
		return deltaTime_;
	}
	bool IsOneSecond()
	{
		return static_cast<int>(deltaCount_) % 2 == 0 ? true : false;
	}
private:
	static CronoMng* sInstance;
	CronoMng();
	~CronoMng();

	std::chrono::time_point<std::chrono::system_clock> start_;
	std::chrono::time_point<std::chrono::system_clock> end_;

	float deltaTime_;
	float deltaCount_;
};

