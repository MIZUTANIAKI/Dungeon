#include "RouteSearch.h"

RouteSearch::RouteSearch()
{
	goalNode = 0;
}

RouteSearch::~RouteSearch()
{
}

int RouteSearch::MarginCost(Vector2 topos)
{
	int cost = 1;
	const auto& gpos = NavGraphNodeVector[goalNode]->GetPosition();
	if (gpos.x > topos.x)
	{
		cost += (gpos.x - topos.x) * 2;
	}
	else if (gpos.x < topos.x)
	{
		cost += (topos.y - gpos.y) * 2;
	}
	if (gpos.y > topos.y)
	{
		cost += (gpos.y - topos.y) * 2;
	}
	else if (gpos.y < topos.y)
	{
		cost += (topos.y - gpos.y) * 2;
	}
	return cost;
};

void RouteSearch::check1(std::list<int>&topenlist)
{
	for (auto i = topenlist.begin(); i != topenlist.end(); i++)
	{
		nowNode = static_cast<int>(*i);
		for (auto& edgeList : edgevector)
		{
			for (auto i = edgeList.begin(); i != edgeList.end(); i++)
			{
				if (i->From() == nowNode)
				{
					if (NavGraphNodeVector[i->To()]->Node() != -1 || NavGraphNodeVector[i->To()]->Cost() != 0)
					{
						if (!closeList.empty())
						{
							if (closeList.front() == i->To())
							{
								break;
							}
						}
						if (NavGraphNodeVector[i->To()]->Node() == nowNode)
						{
							break;
						}
						if (NavGraphNodeVector[i->To()]->Cost() != -1)
						{
							int plusCost = MarginCost(NavGraphNodeVector[i->To()]->GetPosition());
							if (NavGraphNodeVector[i->To()]->Cost() <= NavGraphNodeVector[nowNode]->Cost() + 10 + plusCost)
							{
								break;
							}
						}
					}
					bool checkF = false;
					for (auto tmpNode = tmpopenList.begin(); tmpNode != tmpopenList.end(); tmpNode++)
					{
						if (i->From() == static_cast<int>(*tmpNode))
						{
							checkF = true;
						}
					}
					if (!checkF)
					{
						tmpopenList.emplace_back(i->To());
						int plusCost = MarginCost(NavGraphNodeVector[i->To()]->GetPosition());
						NavGraphNodeVector[i->To()]->SetCost(NavGraphNodeVector[nowNode]->Cost() + 10 + plusCost);
						NavGraphNodeVector[i->To()]->SetNode(nowNode);
					}
				}
				else if (i->To() == nowNode)
				{
					if (NavGraphNodeVector[i->From()]->Node() != -1 || NavGraphNodeVector[i->From()]->Cost() != 0)
					{
						if (!closeList.empty())
						{
							if (closeList.front() == i->From())
							{
								break;
							}
						}
						if (NavGraphNodeVector[i->From()]->Node() == nowNode)
						{
							break;
						}
						if (NavGraphNodeVector[i->From()]->Cost() != -1)
						{
							int plusCost = MarginCost(NavGraphNodeVector[i->From()]->GetPosition());
							if (NavGraphNodeVector[i->From()]->Cost() <= NavGraphNodeVector[nowNode]->Cost() + 10 + plusCost)
							{
								break;
							}
						}
					}

					bool checkF = false;
					for (auto tmpNode = tmpopenList.begin(); tmpNode != tmpopenList.end(); tmpNode++)
					{
						if (i->From() == static_cast<int>(*tmpNode))
						{
							checkF = true;
						}
					}
					if (!checkF)
					{
						tmpopenList.emplace_back(i->From());
						int plusCost = MarginCost(NavGraphNodeVector[i->From()]->GetPosition());
						NavGraphNodeVector[i->From()]->SetCost(NavGraphNodeVector[nowNode]->Cost() + 10 + plusCost);
						NavGraphNodeVector[i->From()]->SetNode(nowNode);
					}
				}
			}
		}
	}
};

void RouteSearch::check3(int node, std::list<int>&topenlist, std::list<int>&tcloselist, int& cost)
{
	for (auto& edgeList : edgevector)
	{
		for (auto i = edgeList.begin(); i != edgeList.end(); i++)
		{
			if (i->From() == node)
			{
				if (NavGraphNodeVector[i->To()]->Node() != -1 || NavGraphNodeVector[i->To()]->Cost() != 0)
				{
					if (!tcloselist.empty())
					{
						if (tcloselist.front() == i->To())
						{
							break;
						}
					}
					if (NavGraphNodeVector[i->To()]->Cost() != -1 || NavGraphNodeVector[i->To()]->Node() == node)
					{
						int plusCost = MarginCost(NavGraphNodeVector[i->To()]->GetPosition());
						if (NavGraphNodeVector[i->To()]->Cost() <= NavGraphNodeVector[node]->Cost() + 10 + plusCost)
						{
							break;
						}
					}
				}

				bool checkF = false;
				for (auto tmpNode = topenlist.begin(); tmpNode != topenlist.end(); tmpNode++)
				{
					if (i->From() == static_cast<int>(*tmpNode))
					{
						checkF = true;
					}
				}
				if (!checkF)
				{
					topenlist.emplace_back(i->To());
					cost = NavGraphNodeVector[node]->Cost() + 10 + MarginCost(NavGraphNodeVector[i->To()]->GetPosition());
					NavGraphNodeVector[i->To()]->SetCost(cost);
					NavGraphNodeVector[i->To()]->SetNode(node);
				}
			}
			else if (i->To() == node)
			{
				if (NavGraphNodeVector[i->From()]->Node() != -1 || NavGraphNodeVector[i->From()]->Cost() != 0)
				{
					if (!tcloselist.empty())
					{
						if (tcloselist.front() == i->From())
						{
							break;
						}
					}
					if (NavGraphNodeVector[i->From()]->Cost() != -1 || NavGraphNodeVector[i->From()]->Node() == node)
					{
						int plusCost = MarginCost(NavGraphNodeVector[i->From()]->GetPosition());
						if (NavGraphNodeVector[i->From()]->Cost() <= NavGraphNodeVector[node]->Cost() + 10 + plusCost)
						{
							break;
						}
					}
				}

				bool checkF = false;
				for (auto tmpNode = topenlist.begin(); tmpNode != topenlist.end(); tmpNode++)
				{
					if (i->From() == static_cast<int>(*tmpNode))
					{
						checkF = true;
					}
				}
				if (!checkF)
				{
					topenlist.emplace_back(i->From());
					cost = NavGraphNodeVector[node]->Cost() + 10 + MarginCost(NavGraphNodeVector[i->From()]->GetPosition());
					NavGraphNodeVector[i->From()]->SetCost(cost);
					NavGraphNodeVector[i->From()]->SetNode(node);
				}
			}
		}
	}
};
std::tuple<bool, int, std::list<int>> RouteSearch::check2(int node, std::list<int> tmpcloselist, int& cost)
{
	if (cost > 1000)
	{
		return std::tuple<bool, int, std::list<int>>(false, cost, tmpcloselist);
	}
	std::list<int> tmplist;
	if (goalNode == node)
	{
		return std::tuple<bool, int, std::list<int>>(true, cost, tmpcloselist);
	}
	else
	{

		check3(node, tmplist, tmpcloselist, cost);
		//if (tmplist.size() > 1)
		if (tmplist.size() > 1)
		{
			int a = 0;
		}
		{
			std::vector<std::tuple<int, int, std::list<int>>>costVector;
			bool rtnF = false;
			tmpcloselist.emplace_front(node);
			for (auto i = tmplist.begin(); i != tmplist.end(); i++)
			{
				int tcost = cost;
				auto cresurt = check2(static_cast<int>(*i), tmpcloselist, tcost);
				if (std::get<0>(cresurt))
				{
					costVector.emplace_back(static_cast<int>(*i), std::get<1>(cresurt), std::get<2>(cresurt));
					rtnF = true;
					cost = std::get<int>(cresurt);
				}
			}
			if (tmplist.size() > 1)
			{
				int a = 0;
			}
			if (tmplist.size() > 0)
			{
				if (!costVector.empty())
				{
					stable_sort(costVector.begin(), costVector.end(), [](auto x, auto y) {
						return (std::get<1>(x)) < (std::get<1>(y));
						});

					return std::tuple<bool, int, std::list<int>>(rtnF, std::get<1>(costVector[0]), std::get<2>(costVector[0]));
				}
			}

			//stable_sort(costVector.begin(), costVector.end(), [](int x, int y) { return (x) > (y); });

			return std::tuple<bool, int, std::list<int>>(false, cost, tmpcloselist);
		}
	}
	return std::tuple<bool, int, std::list<int>>(false, cost, tmpcloselist);
}

bool RouteSearch::check(std::list<int>&topenlist)
{
	while (!topenlist.empty())
	{
		tmpopenList.clear();
		closeList.emplace_front(nowNode);
		nowNode = topenlist.front();
		if (goalNode == nowNode)
		{
			closeList.pop_back();
			for (auto i = closeList.begin(); i != closeList.end(); i++)
			{
				goalMapList.emplace_back(static_cast<int>(*i));
			}
			topenlist.clear();
			return true;
		}
		else
		{
			check1(topenlist);

			if (tmpopenList.size() > 1)
			{
				std::vector<std::tuple<int, int, std::list<int>>>costVector;
				for (auto i = tmpopenList.begin(); i != tmpopenList.end(); i++)
				{
					int cost = NavGraphNodeVector[nowNode]->Cost();
					std::list<int> tmpcloseList = closeList;
					tmpcloseList.emplace_front(nowNode);
					NavGraphNodeVector[goalNode]->SetCost(-1);
					NavGraphNodeVector[goalNode]->SetNode(-1);
					auto cresurt = check2(static_cast<int>(*i), tmpcloseList, cost);

					if (std::get<0>(cresurt))
					{
						costVector.emplace_back(static_cast<int>(*i), std::get<1>(cresurt), std::get<2>(cresurt));
						//std::pair<int, int> tmppairInt(static_cast<int>(*i), cresurt.second);
					}
					std::cout << cost << std::endl;
				}
				topenlist.clear();
				if (!costVector.empty())
				{
					stable_sort(costVector.begin(), costVector.end(), [](auto x, auto y) {
						return (std::get<1>(x)) < (std::get<1>(y));
						});
					closeList = std::get<2>(costVector[0]);
					topenlist.emplace_back(goalNode);
					nowNode = goalNode;
					break;
				}
			}
			else
			{
				topenlist.clear();
				if (!tmpopenList.empty())
				{
					topenlist.emplace_front(tmpopenList.front());
				}
				//topenlist = tmpopenList;
			}
		}
	}
	if (goalNode == nowNode)
	{
		closeList.pop_back();
		for (auto i = closeList.begin(); i != closeList.end(); i++)
		{
			goalMapList.emplace_back(static_cast<int>(*i));
		}
		topenlist.clear();
		return true;
	}
	return false;
}

void RouteSearch::MakeEdge()
{
	for (auto node : NavGraphNodeVector)
	{

		GraphEdge* edge = new GraphEdge();
		bool isEdge = false;
		for (auto tmpnode : NavGraphNodeVector)
		{
			if (node != tmpnode)
			{
				if (node->GetPosition().x == tmpnode->GetPosition().x)
				{
					if (node->GetPosition().y + 1 == tmpnode->GetPosition().y)
					{
						edge->SetFrom(node->Index());
						edge->SetTo(tmpnode->Index());
						sparseGraph.AddEdge(std::move<>(*edge));
						isEdge = true;
					}
				}
				if (node->GetPosition().y == tmpnode->GetPosition().y)
				{
					if (node->GetPosition().x + 1 == tmpnode->GetPosition().x)
					{
						edge->SetFrom(node->Index());
						edge->SetTo(tmpnode->Index());
						sparseGraph.AddEdge(std::move<>(*edge));
						isEdge = true;
					}
				}
			}
		}
		delete edge;
	}
}

void RouteSearch::MakeNode(mapChipDate& mapChipDate, Vector2 mapSize, bool goalF)
{
	int sparseCount = 0;
	for (int x = 0; x < mapSize.x; x++)
	{
		for (int y = 0; y < mapSize.y; y++)
		{
			if (mapChipDate[x][y] != BlockDate::Block)
			{
				NavGraphNode* node = new NavGraphNode();
				node->SetPosition({ y, x });
				node->SetIndex(sparseCount++);

				if (goalPos_.x == x && goalPos_.y == y)
				{
					SetFirstNode(GetNavGraphNodeVectorSize());
				}
				if (firstPos_.x == x && firstPos_.y == y)
				{
					SetGoalNode(GetNavGraphNodeVectorSize());
				}
				AddNavGraphNodeVector(node);
				AddSparseGraph(*node);
			}
		}
	}
}

bool RouteSearch::StartSearch(mapChipDate& mapChipDate, Vector2 mapSize, bool goalF)
{
	Init();
	MakeNode(mapChipDate, mapSize, goalF);
	mapChip_ = mapChipDate;
	goalMapList.clear();
	openList.clear();
	closeList.clear();
	MakeEdge();
	mapSize_ = mapSize;
	nowNode = firstNode;
	edgevector = sparseGraph.GetEdges();
	openList.emplace_front(firstNode);
	NavGraphNodeVector[0]->SetNode(0);

	return check(openList);
}

bool RouteSearch::StartSearch(Vector2 fpos, Vector2 gpos)
{
	for (auto& node : NavGraphNodeVector)
	{
		node->Reset();
	}
	goalMapList.clear();
	openList.clear();
	closeList.clear();
	//MakeEdge();
	int tmpFnode = firstNode;
	int tmpgnode = goalNode;
	SetFGNode(gpos, fpos);
	nowNode = firstNode;
	edgevector = sparseGraph.GetEdges();
	openList.emplace_front(firstNode);
	NavGraphNodeVector[nowNode]->SetNode(0);
	bool rtnF = check(openList);

	firstNode = tmpFnode;
	goalNode = tmpgnode;
	return rtnF;
}

bool RouteSearch::DoGoal()
{
	if (goalMapList.size() == 0)
	{
		return false;
	}
	return true;
}

std::vector<Vector2> RouteSearch::SetGoalRoute()
{
	if (!DoGoal())
	{
		return std::vector<Vector2>();
	}
	std::vector<Vector2> posVector;
	posVector.emplace_back(NavGraphNodeVector[firstNode]->GetPosition());
	for (auto moveNode : goalMapList)
	{
		posVector.emplace_back(NavGraphNodeVector[moveNode]->GetPosition());

	}
	return posVector;
}
