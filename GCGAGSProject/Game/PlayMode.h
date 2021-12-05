#pragma once
#include "MapMng.h"
#include <map>
#include <memory>
#include <string>
#include "Explorer.h"
#include "Aster.h"
#include <mutex>
#include <thread>

class RouteSearch;
class UIScrolller;

enum class SpawnName
{
	Slime,
	Desmodus,
};

class PlayMode
{
public:
	PlayMode();
	~PlayMode();

	void SetStage(int num)
	{
		nowStage_ = num;
	}
	void SetSpawnRate(int num)
	{
		spawnRate_ = num;
	}

	bool GetGoalDelF(void)
	{
		return goalDelF_;
	}

	void SetMapDate(mapChipDate mapdate);

	void Update(void);

	void SpawnEnemy();

	void SpawnPawn();

	void Draw(void);

	void Init(void);

	void CheckGoal(void);

	bool IsCheckClear(void)
	{
		bool tmpfinf = false;
		while (!tmpfinf && ProcessMessage() == 0)
		{
			{
				std::unique_lock<std::mutex> lock(finG_);
				tmpfinf = finF_;
			}
		}
		{
			std::unique_lock<std::mutex> lock(clearG_);
			return clearF_;
		}
	}
	int GetEnemyKillCount(void)
	{
		return enemyKillCount_;
	}
private:
	void CheckFireSpawnEnemy(std::unique_ptr<Explorer>& target, std::unique_ptr<Explorer>& explorer, bool& spawnF, std::vector<std::pair<std::pair<Vector2, bool>, std::pair<float, float>>>& spawnFireVec_);

	void CheckFireSpawnPlayer(std::unique_ptr<Explorer>& target, std::unique_ptr<Explorer>& explorer, bool& spawnF, std::vector<std::pair<std::pair<Vector2, bool>, std::pair<float, float>>>& spawnFireVec_);

	void DropToMap(Vector2& droppos, MapDropDateID id);

	void NowPlacement(Vector2& droppos, MapDropDateID id);

	void PlacementUnit(MapDropDateID id, Vector2& droppos);

	void SpawnGimmick(Vector2& droppos, MapDropDateID id);

	void SpawnGimmick2(Vector2& droppos, MapDropDateID id);

	void SpawnGimmick1(Vector2& droppos, MapDropDateID id);

	void SpawnMonster3(const Vector2& droppos, MapDropDateID id);

	void SpawnMonster2(const Vector2& droppos, MapDropDateID id);

	void SpawnMonster1(const Vector2& droppos, MapDropDateID id);

	void SpawnKnight();

	void SpawnAdventer();

	void SpawnRateSub();

	void InitGoalNode(void);

	void UIInit(void);
	void DrawEdge(Vector2 pos);
	BlockEdge isMapEdge(Vector2 pos);

	const BlockEdge CheckEdge(Vector2& pos);

	void InitMapDate(void);
	void AsterCheck(void);

	void InitMovingDate(void);

	bool IsDubDate(Vector2 pos)
	{
		for (const auto& dbox : explorerVector_)
		{
			if (dbox->GetPos() == pos)
			{
				return true;
			}
		}
		return false;
	}

	std::mutex clearG_;
	std::mutex finG_;
	std::mutex mapG_;

	mapChipDate mapdat_;
	std::unique_ptr< RouteSearch> routeSearch_;
	std::unique_ptr< UIScrolller> uIScrolller_;
	Vector2 mapSize_;
	std::map<BlockDate, std::string> blockImg_;

	int screenH_;
	Vector2 screenSize_;
	Vector2 mapPos_;
	Vector2 firstPos_;
	Vector2 goalPos_;
	std::vector<std::string>roadImg_;

	std::vector<std::unique_ptr<Explorer>> explorerVector_;

	std::vector<Vector2> goalNoade_;
	std::vector<Vector2> reNoade_;
	std::vector < std::vector<nodepoint>> map_;
	int con_;
	int spawnRate_;
	int eneSpawnCount_;
	int knightHP_;
	int enemyKillCount_;

	bool eneF;

	int nowStage_;

	bool spF = false;
	bool BoseF_;
	bool finF_;
	bool clearF_;
	bool goalDelF_;
};

