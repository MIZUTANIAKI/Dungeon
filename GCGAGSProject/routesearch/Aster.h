#pragma once
#include <vector>
#include <list>
#include "Vector2.h"
#include "MapMng.h"

#define lpAsterMng Aster::GetInstance()

struct nodepoint
{
	int nowstep = 0;		//���݂̃X�e�b�v
	int aboutstep = 0;		//����̂���X�e�b�v
	int aboutAlltep = 0;	//���荇�v�X�e�b�v
	int StepCost = 1;	//�R�X�g
};

class Aster
{
public:

	static Aster& GetInstance(void)
	{

		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new Aster();
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

	void Init(mapChipDate date,Vector2 mapsize);
	void Start(Vector2 startPos);

	bool IsGoal(void);

	//�}�b�v�f�[�^��Ԃ�
	std::vector < std::vector<nodepoint>> Getmap(void)
	{
		return map_;
	}
	//�S�[�����[�g��Ԃ�
	std::list<Vector2>  GetGoalRoute(void)
	{
		return goalRoute_;
	}
private:
	static Aster* sInstance;

	void StartCheck(void);

	bool RunCheck(int x,int y,int num);

	/// <summary>
	/// ���̒n�_���ݒ�\�����ׂ�
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="num"></param>
	/// <returns></returns>
	bool CheckMapPoint(int x, int y, int num);

	int CheckMapPointStep(int x,int y, int num);

	std::list<Vector2> CheckMap(int x, int y, int num);

	Aster();
	~Aster();
	std::vector < std::vector<nodepoint>> map_;
	Vector2 goalPos_;
	Vector2 startPos_;
	Vector2 mapSize_;
	mapChipDate mapdate_;
	std::list<Vector2> goalRoute_;
	std::vector<std::pair<std::list<Vector2>,int>> goalRouteList_;
	bool finish_;
};

