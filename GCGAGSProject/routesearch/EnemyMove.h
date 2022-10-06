#pragma once
#include <vector>
#include <list>
#include "Vector2.h"
#include "MapMng.h"

struct mynode
{
	int nowstep = 0;		//現在のステップ
	int aboutstep = 0;		//推定のこりステップ
	int aboutAlltep = 0;	//推定合計ステップ
	int StepCost = 1;		//コスト
};

class EnemyMove
{
public:
	EnemyMove();
	~EnemyMove();
	void Init(mapChipDate date, Vector2 mapsize);
	void SetGoalPos(Vector2 pos)
	{
		goalPos_ = pos;
	}
	int StartCheck(int x,int y);
	//ゴールルートを返す
	std::list<Vector2>  GetGoalRoute(void)
	{
		return goalRoute_;
	}
private:
	bool CheckMapPoint(int x, int y, int num);
	std::list<Vector2> CheckMap(int x, int y, int point);


	std::vector < std::vector<mynode>> map_;
	Vector2 goalPos_;
	Vector2 startPos_;
	Vector2 mapSize_;
	mapChipDate mapdate_;
	std::list<Vector2> goalRoute_;
	std::vector<std::pair<std::list<Vector2>, int>> goalRouteList_;
};

