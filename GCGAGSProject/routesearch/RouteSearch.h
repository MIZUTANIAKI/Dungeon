#pragma once
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include "SparseGraph.h"

class RouteSearch
{
public:
	RouteSearch();
	~RouteSearch();

	void SetGoalPos(Vector2 pos)
	{
		goalPos_ = pos;
	}

	void SetFirstPos(Vector2 pos)
	{
		firstPos_ = pos;
	}

	bool StartSearch(mapChipDate& mapChipDate, Vector2 mapSize, bool goalF = true);

	bool StartSearch(Vector2 fpos, Vector2 gpos);

	bool DoGoal();

	std::vector<Vector2> SetGoalRoute();

private:
	int MarginCost(Vector2 topos);
	void check1(std::list<int>& topenlist);
	void check3(int node, std::list<int>& topenlist, std::list<int>& tcloselist, int& cost);
	std::tuple<bool, int, std::list<int>> check2(int node, std::list<int> tmpcloselist, int& cost);
	bool check(std::list<int>& topenlist);

	void SetGoalNode(int node)
	{
		goalNode = node;
	}

	void SetFirstNode(int node)
	{
		firstNode = node;
	}
	void Init()
	{
		goalNode = 0;
		sparseGraph.Clear();
		NavGraphNodeVector.clear();
		firstNode = 0;

	};
	void AddNavGraphNodeVector(NavGraphNode* node)
	{
		NavGraphNodeVector.emplace_back(node);
	}

	int GetNavGraphNodeVectorSize()
	{
		return static_cast<int>(NavGraphNodeVector.size());
	}

	void AddSparseGraph(NavGraphNode& node)
	{
		sparseGraph.AddNode(std::move<>(node));
	}

	void SetFGNode(Vector2 fpos, Vector2 gpos) 
	{
		int count = 0;
		int gcount = 0;
		for (int x = 0; x < mapSize_.x; x++)
		{
			for (int y = 0; y < mapSize_.y; y++)
			{
				if (mapChip_[x][y] != BlockDate::Block)
				{
					if (gpos.x == y && gpos.y == x)
					{
						SetGoalNode(count);
						gcount++;
					}
					if (fpos.x == y && fpos.y == x)
					{
						SetFirstNode(count);
						gcount++;
					}
					if (gcount >= 2)
					{
						return;
					}
					count++;
				}
			}
		}
	};

	void MakeEdge();

	void MakeNode(mapChipDate& mapChipDate, Vector2 mapSize, bool goalF = true);

	std::list<int> goalMapList;
	std::list<int> openList;
	std::list<int> closeList;
	std::list<int> tmpopenList;
	int firstNode = 0;
	int nowNode = 0;
	Vector2 firstPos_;
	Vector2 goalPos_;
	Vector2 mapSize_;
	SparseGraph sparseGraph = new SparseGraph(false);

	mapChipDate mapChip_;

	std::vector<SparseGraph::EdgeList> edgevector;

	int goalNode;
	std::vector< NavGraphNode*> NavGraphNodeVector;
};

