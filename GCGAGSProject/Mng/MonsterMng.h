#pragma once
#include <memory>
#include <map>

#define lpMonsterMng MonsterMng::GetInstance()

class MonsterMng
{
public:

	static MonsterMng& GetInstance(void)
	{
		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new MonsterMng();
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

	std::pair<float, float> GetSlimeDate(void)
	{
		if (slime_.first == 0)
		{
			StartInPut();
		}
		return slime_;
	}

	std::pair<float, float> GetDesmodusDate(void)
	{
		if (desmodus_.first == 0)
		{
			StartInPut();
		}
		return desmodus_;
	}

	std::pair<float, float> GetRookDate(void)
	{
		if (rook_.first == 0)
		{
			StartInPut();
		}
		return rook_;
	}

	void StartOutPut();
	void StartInPut();

	std::pair<float, float> StartInPutAdven(int num);

private:
	static MonsterMng* sInstance;
	void InputAdven();

	//		  HP   ATK
	std::pair<float, float> slime_;
	std::pair<float, float> desmodus_;
	std::pair<float, float> rook_;
	std::pair<float, float> Onibi_;
	std::map<int, std::pair<float, float>> adventurerMap_;

	MonsterMng();
	~MonsterMng();
};
