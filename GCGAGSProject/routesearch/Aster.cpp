#include <algorithm>

#include "Aster.h"

Aster* Aster::sInstance = nullptr;

void Aster::Init(mapChipDate date, Vector2 mapsize)
{
	goalPos_ = { 0,0 };
	startPos_ = { 0,0 };
	mapSize_ = { 0,0 };
	map_.clear();
	goalRoute_.clear();
	goalRouteList_.clear();
	mapdate_ = date;
	map_.resize(mapsize.y);
	for (int count = 0; count < mapsize.y; count++)
	{
		map_[count].resize(mapsize.x);
	}
	for (int y = 0; y < mapSize_.y; y++)
	{
		for (int x = 0; x < mapSize_.x; x++)
		{
			map_[y][x].nowstep = 0;
			map_[y][x].aboutstep = 0;
			map_[y][x].aboutAlltep = 0;
			map_[y][x].StepCost = 1;
		}
	}
	mapSize_ = mapsize;
	for (int y = 0; y < mapsize.y; y++)
	{
		for (int x = 0; x < mapsize.x; x++)
		{
			if (date[y][x] == BlockDate::Block)
			{
				map_[y][x].nowstep = -1;
				map_[y][x].aboutstep = -1;
				map_[y][x].aboutAlltep = -1;
			}
			if (date[y][x] == BlockDate::Gate)
			{
				map_[y][x].StepCost = 50;
			}
			if (date[y][x] == BlockDate::Spike)
			{
				map_[y][x].StepCost = 3;
			}
			if (date[y][x] == BlockDate::Start)
			{
				goalPos_ = { x,y };
			}
			if (date[y][x] == BlockDate::Goal)
			{
				map_[y][x].nowstep = 1;
				startPos_ = { x,y };
			}
		}
	}

	map_[startPos_.y][startPos_.x].nowstep = 1;
	map_[startPos_.y][startPos_.x].aboutstep = (startPos_.x- startPos_.y)- (goalPos_.x - startPos_.y);
	map_[startPos_.y][startPos_.x].aboutAlltep = 1+ (startPos_.x - startPos_.y) - (goalPos_.x - startPos_.y);

}

void Aster::PlayInit(mapChipDate date, Vector2 mapsize)
{
	goalPos_ = { 0,0 };
	startPos_ = { 0,0 };
	mapSize_ = { 0,0 };
	goalRoute_.clear();
	goalRouteList_.clear();
	mapdate_ = date;
	for (int y = 0; y < mapSize_.y; y++)
	{
		for (int x = 0; x < mapSize_.x; x++)
		{
			map_[y][x].nowstep = 0;
			map_[y][x].aboutstep = 0;
			map_[y][x].aboutAlltep = 0;
		}
	}
	mapSize_ = mapsize;
	for (int y = 0; y < mapsize.y; y++)
	{
		for (int x = 0; x < mapsize.x; x++)
		{
			if (date[y][x] == BlockDate::Block)
			{
				map_[y][x].nowstep = -1;
				map_[y][x].aboutstep = -1;
				map_[y][x].aboutAlltep = -1;
			}
			if (date[y][x] == BlockDate::Gate)
			{
				map_[y][x].StepCost = 50;
			}
			if (date[y][x] == BlockDate::Spike)
			{
				map_[y][x].StepCost = 3;
			}
			if (date[y][x] == BlockDate::Start)
			{
				goalPos_ = { x,y };
			}
			if (date[y][x] == BlockDate::Goal)
			{
				map_[y][x].nowstep = 1;
				startPos_ = { x,y };
			}
		}
	}
	map_[startPos_.y][startPos_.x].nowstep = 1;
	map_[startPos_.y][startPos_.x].aboutstep = (startPos_.x - startPos_.y) - (goalPos_.x - startPos_.y);
	map_[startPos_.y][startPos_.x].aboutAlltep = 1 + (startPos_.x - startPos_.y) - (goalPos_.x - startPos_.y);

}

void Aster::Start(Vector2 startPos)
{
	if (startPos.x < 0|| startPos.y < 0)
	{
		goalRoute_.clear();
		return;
	}
	goalPos_ = { startPos.x,startPos.y };

	for (int y = 0; y < mapSize_.y; y++)
	{
		for (int x = 0; x < mapSize_.x; x++)
		{
			if (mapdate_[y][x] == BlockDate::Block)
			{
				map_[y][x].nowstep = -1;
				map_[y][x].aboutstep = -1;
				map_[y][x].aboutAlltep = -1;
			}
			else
			if (mapdate_[y][x] == BlockDate::Goal)
			{
				map_[y][x].nowstep = 1;
				startPos_ = { x,y };
			}
			else
			{
				map_[y][x].nowstep = 0;
				map_[y][x].aboutstep = 0;
				map_[y][x].aboutAlltep = 0;
			}
		}
	}

	StartCheck();

	for (int y = 0; y < mapSize_.y; y++)
	{
		for (int x = 0; x < mapSize_.x; x++)
		{
			if (map_[y][x].nowstep == 0)
			{
				map_[y][x].nowstep = -1;
				map_[y][x].aboutstep = -1;
				map_[y][x].aboutAlltep = -1;
			}		
			bool checkNoHit = true;
			for (const auto& glist : goalRoute_)
			{
				if (glist.x == x && glist.y == y)
				{
					checkNoHit = false;
				}
			}
			if (checkNoHit)
			{
				map_[y][x].nowstep = -1;
				map_[y][x].aboutstep = -1;
				map_[y][x].aboutAlltep = -1;
			}
		}
	}

}

bool Aster::IsGoal(void)
{
	if (map_[goalPos_.y][goalPos_.x].nowstep == -1)
	{
		return false;
	}
	return true;
}

void Aster::AddCost(Vector2 pos)
{
	if (pos.x >= mapSize_.x)
	{
		return;
	}
	if (pos.y >= mapSize_.y)
	{
		return;
	}
	if (pos.x < 0)
	{
		return;
	}
	if (pos.y < 0)
	{
		return;
	}
	if (map_[pos.y][pos.x].nowstep != -1)
	{
		map_[pos.y][pos.x].StepCost+=10;
	}
}

void Aster::StartCheck(void)
{
	finish_ = false;
	goalRoute_.clear();
	RunCheck(startPos_.x, startPos_.y, 1);

	if (map_[goalPos_.y][goalPos_.x].nowstep <= 0)
	{
		goalRoute_.clear();
		return;
	}
	goalRoute_.clear();
	finish_ = false;
	goalRoute_.push_back({ startPos_.x,startPos_.y });
	CheckMapPointStep(goalPos_.x, goalPos_.y, map_[goalPos_.y][goalPos_.x].nowstep);

	goalRoute_.push_back({ goalPos_.x,goalPos_.y });
}

bool Aster::RunCheck(int x, int y, int num)
{
	if (goalPos_.x == x && goalPos_.y == y)
	{
		goalRoute_.push_back({ x,y });
		return true;
	}

	num += map_[y][x].StepCost;
	Vector2 pos;
	std::list<std::pair<Vector2,int>> node;
	if (CheckMapPoint(x, y - 1, num))
	{
		pos = { x,y - 1 };
		map_[pos.y][pos.x].nowstep = num;
		map_[pos.y][pos.x].aboutstep = (x - (y - 1)) - (goalPos_.x - startPos_.y);
		map_[pos.y][pos.x].aboutAlltep = map_[pos.y][pos.x].nowstep + map_[pos.y][pos.x].aboutstep;
		node.push_back(std::pair<Vector2, int>(Vector2{ x, y - 1 }, map_[pos.y][pos.x].aboutAlltep));
	}
	if (CheckMapPoint(x, y + 1, num))
	{
		pos = { x,y + 1 };
		map_[pos.y][pos.x].nowstep = num;
		map_[pos.y][pos.x].aboutstep = (x - (y - 1)) - (goalPos_.x - startPos_.y);
		map_[pos.y][pos.x].aboutAlltep = map_[pos.y][pos.x].nowstep + map_[pos.y][pos.x].aboutstep;
		node.push_back(std::pair<Vector2, int>(Vector2{ x, y + 1 }, map_[pos.y][pos.x].aboutAlltep));
	}
	if (CheckMapPoint(x - 1, y, num))
	{
		pos = { x - 1,y };
		map_[pos.y][pos.x].nowstep = num;
		map_[pos.y][pos.x].aboutstep = (x - (y - 1)) - (goalPos_.x - startPos_.y);
		map_[pos.y][pos.x].aboutAlltep = map_[pos.y][pos.x].nowstep + map_[pos.y][pos.x].aboutstep;
		node.push_back(std::pair<Vector2, int>(Vector2{ x- 1 , y }, map_[pos.y][pos.x].aboutAlltep));
	}
	if (CheckMapPoint(x + 1, y, num))
	{
		pos = { x + 1,y };
		map_[pos.y][pos.x].nowstep = num;
		map_[pos.y][pos.x].aboutstep = (x - (y - 1)) - (goalPos_.x - startPos_.y);
		map_[pos.y][pos.x].aboutAlltep = map_[pos.y][pos.x].nowstep + map_[pos.y][pos.x].aboutstep;
		node.push_back(std::pair<Vector2, int>(Vector2{ x + 1 , y }, map_[pos.y][pos.x].aboutAlltep));
	}
	if (node.empty())
	{
		return false;
	}
	std::stable_sort(node.begin(), node.end(), [](auto& node1, auto& node2) {
		return node1.second > node2.second;
		});
	std::vector<std::pair<std::list<Vector2>, int>> tmplisvector;
	for (const auto& date : node)
	{
		auto mc = CheckMap(date.first.x, date.first.y, num);
		if (!mc.empty())
		{
			goalRoute_.push_back({ x,y });
			if (num - 1 != 1)
			{
				tmplisvector.push_back(std::pair<std::list<Vector2>, int>(mc, map_[goalPos_.y][goalPos_.x].nowstep));
			}
			else
			{
				goalRouteList_.push_back(std::pair<std::list<Vector2>, int>(mc, map_[goalPos_.y][goalPos_.x].nowstep));
				goalRoute_.clear();

			}
		}
	}
	if (goalRouteList_.empty())
	{
		return false;
	}

	std::stable_sort(goalRouteList_.begin(), goalRouteList_.end(), [](auto& node1, auto& node2) {
		return node1.second > node2.second;
		});
	return true;
}

bool Aster::CheckMapPoint(int x, int y, int num)
{
	if (x >= mapSize_.x)
	{
		return false;
	}
	if (y >= mapSize_.y)
	{
		return false;
	}
	if (x < 0)
	{
		return false;
	}
	if (y < 0)
	{
		return false;
	}
	if (map_[y][x].nowstep == -1)
	{
		return false;
	}
	if (map_[y][x].nowstep <= num && map_[y][x].nowstep != 0)
	{
		return false;
	}
	return true;
}

int Aster::CheckMapPointStep(int x, int y, int num)
{
	if (startPos_.x == x && startPos_.y == y)
	{
		finish_ = true;
		return true;
	}
	if (finish_)
	{
		return true;
	}
	if (x >= mapSize_.x)
	{
		return false;
	}
	if (y >= mapSize_.y)
	{
		return false;
	}
	if (x < 0)
	{
		return false;
	}
	if (y < 0)
	{
		return false;
	}
	if (map_[y][x].nowstep == -1)
	{
		return false;
	}
	if (map_[y][x].nowstep > num)
	{
		return false;
	}
	std::list<std::pair<Vector2, int>> node;
	Vector2 pos;
	num -= map_[y][x].StepCost;
	if (CheckMapPointStep(x, y - 1, num))
	{
		pos = { x,y - 1 };
		map_[pos.y][pos.x].nowstep = num;
		map_[pos.y][pos.x].aboutstep = (x - (y - 1)) - (goalPos_.x - startPos_.y);
		map_[pos.y][pos.x].aboutAlltep = map_[pos.y][pos.x].nowstep + map_[pos.y][pos.x].aboutstep;
		node.push_back(std::pair<Vector2, int>(Vector2{ x, y - 1 }, map_[pos.y][pos.x].aboutAlltep));
	}
	if (CheckMapPointStep(x, y + 1, num))
	{
		pos = { x,y + 1 };
		map_[pos.y][pos.x].nowstep = num;
		map_[pos.y][pos.x].aboutstep = (x - (y - 1)) - (goalPos_.x - startPos_.y);
		map_[pos.y][pos.x].aboutAlltep = map_[pos.y][pos.x].nowstep + map_[pos.y][pos.x].aboutstep;
		node.push_back(std::pair<Vector2, int>(Vector2{ x, y + 1 }, map_[pos.y][pos.x].aboutAlltep));
	}
	if (CheckMapPointStep(x - 1, y, num))
	{
		pos = { x - 1,y };
		map_[pos.y][pos.x].nowstep = num;
		map_[pos.y][pos.x].aboutstep = (x - (y - 1)) - (goalPos_.x - startPos_.y);
		map_[pos.y][pos.x].aboutAlltep = map_[pos.y][pos.x].nowstep + map_[pos.y][pos.x].aboutstep;
		node.push_back(std::pair<Vector2, int>(Vector2{ x - 1 , y }, map_[pos.y][pos.x].aboutAlltep));
	}
	if (CheckMapPointStep(x + 1, y, num))
	{
		pos = { x + 1,y };
		map_[pos.y][pos.x].nowstep = num;
		map_[pos.y][pos.x].aboutstep = (x - (y - 1)) - (goalPos_.x - startPos_.y);
		map_[pos.y][pos.x].aboutAlltep = map_[pos.y][pos.x].nowstep + map_[pos.y][pos.x].aboutstep;
		node.push_back(std::pair<Vector2, int>(Vector2{ x + 1 , y }, map_[pos.y][pos.x].aboutAlltep));
	}
	if (node.empty())
	{
		return false;
	}
	std::stable_sort(node.begin(), node.end(), [](auto& node1, auto& node2) {
		return node1.second > node2.second;
		});

	goalRoute_.push_back(node.front().first);

	return true;
}

std::list<Vector2> Aster::CheckMap(int x, int y, int point)
{
	//もし現在地がゴールならば
	if (goalPos_.x == x && goalPos_.y == y)
	{
		//終わったフラグを立てて地点をリターンする
		std::list<Vector2> tmp;
		tmp.push_back({ x,y });
		finish_ = true;
		return tmp;
	}
	//この地点のコストを保存する。
	point += map_[y][x].StepCost;
	Vector2 pos = { 0,0 };
	//隣接した地点の方向に進めた場合のコストを格納する変数
	std::list<std::pair<Vector2, int>> node;
	//下方向を調べる
	if (CheckMapPoint(x, y - 1, point))
	{
		//一つ下に行くことができる/自分のほうが軽い　ならば
		pos = { x,y - 1 };
		//ポイントを格納する
		map_[pos.y][pos.x].nowstep = point;
		//予想この地点からのコスト
		map_[pos.y][pos.x].aboutstep = (x - (y - 1)) - (goalPos_.x - startPos_.y);
		//想定合計コスト
		map_[pos.y][pos.x].aboutAlltep = map_[pos.y][pos.x].nowstep + map_[pos.y][pos.x].aboutstep;
		//この方向のコストを格納する
		node.push_back(std::pair<Vector2, int>(Vector2{ x, y - 1 }, map_[pos.y][pos.x].aboutAlltep));
	}
	//上方向を調べる
	if (CheckMapPoint(x, y + 1, point))
	{
		//一つ上に行くことができる/自分のほうが軽い　ならば
		pos = { x,y + 1 };
		//ポイントを格納する
		map_[pos.y][pos.x].nowstep = point;
		//予想この地点からのコスト
		map_[pos.y][pos.x].aboutstep = (x - (y - 1)) - (goalPos_.x - startPos_.y);
		//想定合計コスト
		map_[pos.y][pos.x].aboutAlltep = map_[pos.y][pos.x].nowstep + map_[pos.y][pos.x].aboutstep;
		//この方向のコストを格納する
		node.push_back(std::pair<Vector2, int>(Vector2{ x, y + 1 }, map_[pos.y][pos.x].aboutAlltep));
	}
	//左方向を調べる
	if (CheckMapPoint(x - 1, y, point))
	{
		//一つ左に行くことができる/自分のほうが軽い　ならば
		pos = { x - 1,y };
		//ポイントを格納する
		map_[pos.y][pos.x].nowstep = point;
		//予想この地点からのコスト
		map_[pos.y][pos.x].aboutstep = (x - (y - 1)) - (goalPos_.x - startPos_.y);
		//想定合計コスト
		map_[pos.y][pos.x].aboutAlltep = map_[pos.y][pos.x].nowstep + map_[pos.y][pos.x].aboutstep;
		//この方向のコストを格納する
		node.push_back(std::pair<Vector2, int>(Vector2{ x - 1 , y }, map_[pos.y][pos.x].aboutAlltep));
	}
	//右方向を調べる
	if (CheckMapPoint(x + 1, y, point))
	{
		//一つ右に行くことができる/自分のほうが軽い　ならば
		pos = { x + 1,y };
		//ポイントを格納する
		map_[pos.y][pos.x].nowstep = point;
		//予想この地点からのコスト
		map_[pos.y][pos.x].aboutstep = (x - (y - 1)) - (goalPos_.x - startPos_.y);
		//想定合計コスト
		map_[pos.y][pos.x].aboutAlltep = map_[pos.y][pos.x].nowstep + map_[pos.y][pos.x].aboutstep;
		//この方向のコストを格納する
		node.push_back(std::pair<Vector2, int>(Vector2{ x + 1 , y }, map_[pos.y][pos.x].aboutAlltep));
	}
	if (node.empty())
	{
		//もし隣接した地点が移動不可だったらリターンする
		return std::list<Vector2>();
	}
	//コストの軽い順でソート
	std::stable_sort(node.begin(), node.end(), [](auto& node1, auto& node2) {
		return node1.second > node2.second;
		});

	std::vector<std::pair<std::list<Vector2>, int>> tmplisvector;
	for (const auto& date : node)
	{
		//各方向をチェックする。
		auto mc = CheckMap(date.first.x, date.first.y, point);
		if (!mc.empty())
		{
			mc.push_back({ x,y });
			tmplisvector.push_back(std::pair<std::list<Vector2>, int>(mc, map_[goalPos_.y][goalPos_.x].nowstep));
		}
	}
	if (tmplisvector.empty())
	{
		//ゴールできなかったらリターンする
		return std::list<Vector2>();
	}
	//コストの軽い順でソート
	std::stable_sort(tmplisvector.begin(), tmplisvector.end(), [](auto& node1, auto& node2) {
		return node1.second > node2.second;
		});

	return tmplisvector.front().first;
}

Aster::Aster()
{
	goalPos_ = { 0,0 };
	startPos_ = { 0,0 };
	mapSize_ = { 0,0 };
	map_.clear();
	goalRoute_.clear();
	goalRouteList_.clear();
}

Aster::~Aster()
{
}
