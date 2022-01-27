#include <DxLib.h>
#include "PlayMode.h"
#include "ImageMng.h"
#include "RouteSearch.h"
#include "MoneyMng.h"
#include "RightHandSearch.h"
#include "MouseMng.h"
#include "MapMng.h"
#include "EnergyMng.h"
#include "UIMng.h"
#include "SoundMng.h"
#include "KeyMng.h"

#include "Aster.h"
#include "UIScrolller.h"
#include "UIMapBuildMenu.h"
#include "Adventurer.h"
#include "Knight.h"
#include "Monster.h"
#include "Desmodus.h"
#include "Spike.h"
#include "Rook.h"
#include "Goal.h"
#include "Gate.h"
#include "Fire.h"
#include "EnemyPawn.h"
#include "StatusCtr.h"

PlayMode::PlayMode()
{
	blockImg_.try_emplace(BlockDate::Start, lpImglMng.LoadGraph("start.png"));
	blockImg_.try_emplace(BlockDate::Block, lpImglMng.LoadGraph("block.png"));
	blockImg_.try_emplace(BlockDate::Goal, lpImglMng.LoadGraph("End.png"));
	blockImg_.try_emplace(BlockDate::Road, lpImglMng.LoadGraph("Nonblock.png"));
	blockImg_.try_emplace(BlockDate::DRoad, lpImglMng.LoadGraph("Nonblock.png"));
	blockImg_.try_emplace(BlockDate::Gate, blockImg_.at(BlockDate::Road));
	blockImg_.try_emplace(BlockDate::Spike, blockImg_.at(BlockDate::Road));
	roadImg_.emplace_back(lpImglMng.LoadGraph("Up.png"));
	roadImg_.emplace_back(lpImglMng.LoadGraph("Right.png"));
	roadImg_.emplace_back(lpImglMng.LoadGraph("Down.png"));
	roadImg_.emplace_back(lpImglMng.LoadGraph("Left.png"));

	GetDrawScreenSize(&screenSize_.x, &screenSize_.y);
	screenH_ = MakeScreen(1000 - 32, 550, true);
	mapPos_.x = 0;
	mapPos_.y = 0;

	routeSearch_ = std::make_unique<RouteSearch>();

	mapSize_.x = 35;
	mapSize_.y = 17;
	mapdat_.resize(mapSize_.y);
	dorpDir_ = 0;
	for (int y = 0; y < mapSize_.y; y++)
	{
		mapdat_[y].resize(mapSize_.x);
	}

	for (int y = 0; y < mapSize_.y; y++)
	{
		for (int x = 0; x < mapSize_.x; x++)
		{
			if (y == 0 && x == mapSize_.x / 2 - 1)
			{
				mapdat_[y][x] = BlockDate::Start;
			}
			else if (y == mapSize_.y - 1 && x == mapSize_.x / 2 - 1)
			{
				mapdat_[y][x] = BlockDate::Goal;
			}
			//else if (((y == 0 || y == mapSize_.y - 1) && x < mapSize_.x / 2 - 1)|| x == 0)
			//{
			//	mapdat_[y][x] = BlockDate::Road;
			//}
			else
			{
				mapdat_[y][x] = BlockDate::Block;
			}
		}
	}

	spF = false;
	con_ = 0;
	mapPos_ = { 0,0 };

		//std::string str = GetCommandLine();
		//int pos = str.find(' ');
		//auto tmpt = str.substr(pos + 1);
	
		//if (!tmpt.empty())
		//{
		//	lpMoneyMng.SetMoney(9999);
		//}
		//else
		//{
		//	lpMoneyMng.SetMoney(150);
		//}
	eneF = false;
	uIScrolller_ = std::make_unique<UIScrolller>();
	spawnRate_ = 500;
}

PlayMode::~PlayMode()
{
}

void PlayMode::SetMapDate(mapChipDate mapdate)
{
	mapdat_ = mapdate;
	//マップからデータを設定
	InitMapDate();
}

void PlayMode::Update(void)
{
	if (lpMouseMng.GetInputDat() & MOUSE_INPUT_RIGHT&& !lpMouseMng.GetOldInputDat() & MOUSE_INPUT_RIGHT)
	{
		dorpDir_++;
		if (dorpDir_ >= 4)
		{
			dorpDir_ = 0;
		}
	}

	if (!lpSoundMng.CheckPlaySound("game.mp3"))
	{
		lpSoundMng.SoundPlay("game.mp3");
	}
	if (lpCronoMng.IsOneSecond())
	{
		con_++;
	}
	if (enemyKillCount_ >= 30 + 10 * nowStage_)
	{
		lpMoneyMng.SetStartFlag(false);
		return;
	}
	lpEnergyMng.Update();
	uIScrolller_->Update();
	//if (con_ / 30 % 2 == 0)
	if (/*CheckHitKey(KEY_INPUT_SPACE)*/con_ % spawnRate_ == 0)
	{
		//if (eneF)
		//{
		//	return;
		//}
		//eneF = true;
		bool tmpfinf = false;
		{
			std::unique_lock<std::mutex> lock(finG_);
			tmpfinf = finF_;
		}
		if (tmpfinf /*&& rand() % (200 - min(con_ / 30 / 60, 150)) == 0*/)
		{
			if (con_ % 200 == 150 && !BoseF_ && nowStage_ != 0)
			{
				BoseF_ = true;
			}
			else
			{
				if (!BoseF_ && eneSpawnCount_ <= 30 + 10 * nowStage_)
				{
					SpawnEnemy();
				}
			}
			SpawnRateSub();
		}
	}
	//else
	//{
	//	eneF = false;
	//}
	Vector2 nowMPos = lpMouseMng.GetMousePos();

	if (lpMapMng.IsDrop())
	{
		MapDropDateID id = lpMapMng.GetDropID();
		Vector2 droppos = lpMapMng.GetDropPos();
		if (droppos.x >= 145 && droppos.y >= 65 && droppos.y <= 582 && droppos.x <= 1110)
		{
			DropToMap(droppos, id);
		}
	}

	if (lpKeyMng.CheckKeyNow(KeyBindID::Up))
	{
		if ((mapSize_.y - 1) * 32 + mapPos_.y - 1 > 550 - 60)
		{
			mapPos_.y--;
		}

		if(!explorerVector_.empty())
		{
			Explorer::SetMapMos(mapPos_);
		}
	}

	if (lpKeyMng.CheckKeyNow(KeyBindID::Up))
	{
		if (mapPos_.y < 1)
		{
			mapPos_.y++;
		}

		if (!explorerVector_.empty())
		{
			Explorer::SetMapMos(mapPos_);
		}
	}
	bool spawnF = false;
	std::vector<std::pair<std::pair<Vector2,bool>, std::pair<float, float>>> spawnFireVec_;
	for (auto& explorer : explorerVector_)
	{
		explorer->Update();

		for (auto& target : explorerVector_)
		{
			if (explorer != target)
			{
				if (!explorer->IsSleep()&&explorer->GetObjectID() == ObjectID::Rook)
				{
					CheckFireSpawnPlayer(target, explorer, spawnF, spawnFireVec_);
				}
				if (!explorer->IsSleep() && explorer->GetObjectID() == ObjectID::Adventurer)
				{
					CheckFireSpawnEnemy(target, explorer, spawnF, spawnFireVec_);
				}

				explorer->HitCheck((*target));
				target->HitCheck((*explorer));
			}
		}
	}

	if (!spawnFireVec_.empty())
	{
		for (const auto& spawn : spawnFireVec_)
		{
			std::unique_ptr<Fire> tmpAdventure = std::make_unique<Fire>();
			tmpAdventure->Init();
			tmpAdventure->SetMapMos(mapPos_);
			tmpAdventure->ReSetPos(spawn.first.first / 32);
			MoveDir tmpDir = MoveDir::Up;
			tmpAdventure->SetDir(lpRHSMng.CheckMove(spawn.first.first, tmpDir));
			Vector2 movedir;
			float c = sqrt(spawn.second.first * spawn.second.first + spawn.second.second * spawn.second.second);
			movedir.x = static_cast<int>(spawn.second.first / c * 350.0f);
			movedir.y = static_cast<int>(spawn.second.second / c * 350.0f);
			tmpAdventure->SetMoveDir(movedir);
			if (spawn.first.second)
			{
				tmpAdventure->Fire::SetEneF();
			}
			explorerVector_.emplace_back(std::move<>(tmpAdventure));
		}
	}

	auto itr = explorerVector_.begin();
	while (itr != explorerVector_.end())
	{
		if ((*itr)->GetHP() <= 0)
		{
			if ((*itr)->GetObjectID() == ObjectID::Adventurer)
			{
				enemyKillCount_++;
			}
			if ((*itr)->GetObjectID() == ObjectID::Knight)
			{
				enemyKillCount_++;
			}
			if ((*itr)->GetObjectID() == ObjectID::Pawn)
			{
				enemyKillCount_++;
			}
			if ((*itr)->GetObjectID() == ObjectID::Goal)
			{
				goalDelF_ = true; 
			}
			if ((*itr)->GetObjectID() == ObjectID::Gate || (*itr)->GetObjectID() == ObjectID::Spike)
			{
				mapdat_[(*itr)->GetPos().y / 32][(*itr)->GetPos().x / 32] = BlockDate::Road;
				CheckGoal();
			}

			itr = explorerVector_.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

void PlayMode::CheckRouteForPlay()
{
	for (auto& explorer : explorerVector_)
	{
		if (explorer->GetObjectID() != ObjectID::Adventurer &&
			explorer->GetObjectID() != ObjectID::Knight &&
			explorer->GetObjectID() != ObjectID::Pawn)
		{
		}
		else
		{
			goalNoade_.clear();
			//初期化
			lpAsterMng.Init(mapdat_, mapSize_);
			//探索開始
			lpAsterMng.Start(explorer->GetPos() / 32);
			InitMovingDate();
			explorer->SetMoveVec(goalNoade_);
		}
	}
}

void PlayMode::SpawnEnemy()
{
	if (rand() % 10 == 0)
	{
		eneSpawnCount_++;
		SpawnAdventer();
	}
	else if (rand() % 5 == 0)
	{
		eneSpawnCount_++;
		SpawnKnight();
	}
	else
	{
		eneSpawnCount_++;
		SpawnPawn();
	}
}

void PlayMode::SpawnPawn()
{
	std::unique_ptr<EnemyPawn> tmpAdventure = std::make_unique<EnemyPawn>();
	tmpAdventure->Init();
	tmpAdventure->SetMoveVec(goalNoade_);
	tmpAdventure->SetMapMos(mapPos_);
	tmpAdventure->ReSetPos(firstPos_);
	tmpAdventure->EnemyPawn::SetHP(10);
	tmpAdventure->SetDir(MoveDir::Down);
	tmpAdventure->SetStatus(nowStage_);
	explorerVector_.emplace_back(std::move<>(tmpAdventure));
}

void PlayMode::CheckFireSpawnEnemy(std::unique_ptr<Explorer>& target, std::unique_ptr<Explorer>& explorer, bool& spawnF, std::vector<std::pair<std::pair<Vector2, bool>, std::pair<float, float>>>& spawnFireVec_)
{
	//範囲内に敵がいるか
	if (target->GetObjectID() == ObjectID::Goal)
	{
		return;
	}
	if (target->GetObjectID() == ObjectID::EFire)
	{
		return;
	}
	if (target->GetObjectID() == ObjectID::Fire)
	{
		return;
	}
	if (target->GetObjectID() == ObjectID::Adventurer || target->GetObjectID() == ObjectID::Knight || target->GetObjectID() == ObjectID::Pawn)
	{
		return;
	}
	int a = target->GetPos().x - explorer->GetPos().x;
	int b = target->GetPos().y - explorer->GetPos().y;
	int c = a * a + b * b;
	if (c < 100 * 100)
	{
		//敵がいた。
		spawnF = true;
		explorer->SetSleep();
		spawnFireVec_.emplace_back(std::pair<std::pair<Vector2, bool>, std::pair<float, float>>(std::pair<Vector2, bool>(explorer->GetPos(), true), std::pair<float, float>(a, b)));
	}
}

void PlayMode::CheckFireSpawnPlayer(std::unique_ptr<Explorer>& target, std::unique_ptr<Explorer>& explorer, bool& spawnF, std::vector<std::pair<std::pair<Vector2, bool>, std::pair<float, float>>>& spawnFireVec_)
{
	//範囲内に敵がいるか
	if (target->GetObjectID() != ObjectID::Adventurer && target->GetObjectID() != ObjectID::Knight && target->GetObjectID() != ObjectID::Pawn)
	{
		return;
	}
	int a = target->GetPos().x - explorer->GetPos().x;
	int b = target->GetPos().y - explorer->GetPos().y;
	int c = a * a + b * b;
	if (c < 100 * 100)
	{
		//敵がいた。
		spawnF = true;
		explorer->SetSleep();
		spawnFireVec_.emplace_back(std::pair<std::pair<Vector2, bool>, std::pair<float, float>>(std::pair<Vector2, bool>(explorer->GetPos(), false), std::pair<float, float>(a, b)));
	}
}

void PlayMode::DropToMap(Vector2& droppos, MapDropDateID id)
{
	droppos.x -= 145;
	droppos.y -= 65;
	droppos.x -= mapPos_.x;
	droppos.y -= mapPos_.y;
	droppos.x /= 32;
	droppos.y /= 32;
	if (droppos.y >= 0 &&
		droppos.x >= 0 &&
		droppos.x < mapSize_.x &&
		droppos.y < mapSize_.y && droppos.y != 0)
	{
		NowPlacement(droppos, id);
	}
}

void PlayMode::NowPlacement(Vector2& droppos, MapDropDateID id)
{
	bool rtnF = false;
	for (auto& dbox : explorerVector_)
	{
		if (droppos == dbox->GetPos())
		{
			rtnF = true;
		}
	}
	if (!rtnF)
	{
		if (mapdat_[droppos.y][droppos.x] != BlockDate::Start && mapdat_[droppos.y][droppos.x] != BlockDate::Goal)
		{
			PlacementUnit(id, droppos);
		}
	}
}

void PlayMode::PlacementUnit(MapDropDateID id, Vector2& droppos)
{
	if (id == MapDropDateID::Slime)
	{
		if (mapdat_[droppos.y][droppos.x] != BlockDate::Block)
		{
			SpawnMonster1(droppos, id);
		}
	}
	else if (id == MapDropDateID::Desmodus)
	{
		if (mapdat_[droppos.y][droppos.x] != BlockDate::Block)
		{
			SpawnMonster2(droppos, id);
		}
	}
	else if (id == MapDropDateID::Rook)
	{
		if (mapdat_[droppos.y][droppos.x] != BlockDate::Block)
		{
			SpawnMonster3(droppos, id);
		}
	}
	else if (mapdat_[droppos.y][droppos.x] == BlockDate::Road)
	{
		SpawnGimmick(droppos, id);
	}
}

void PlayMode::SpawnGimmick(Vector2& droppos, MapDropDateID id)
{
	if (!IsDubDate(droppos))
	{
		if (id == MapDropDateID::Spike)
		{
			SpawnGimmick1(droppos, id);
		}
		else if (id == MapDropDateID::Gate)
		{
			SpawnGimmick2(droppos, id);
		}
	}
}

void PlayMode::SpawnGimmick2(Vector2& droppos, MapDropDateID id)
{
	if (lpEnergyMng.SubEnergy(60))
	{
		std::unique_ptr<Gate> tmpMonster = std::make_unique<Gate>();
		tmpMonster->Init();
		tmpMonster->SetMapMos(mapPos_);
		tmpMonster->ReSetPos(droppos);
		tmpMonster->SetStatus(StatusCtr::GetStates(StatusID::GImmick2));
		explorerVector_.emplace_back(std::move<>(tmpMonster));
		mapdat_[droppos.y][droppos.x] = BlockDate::Gate;
		CheckGoal();
		stable_sort(explorerVector_.begin(), explorerVector_.end(), [](auto& x, auto& y) {
			return x->GetPos().y < y->GetPos().y;
			});
		lpMapMng.SetDropEndF(id, true);
		lpSoundMng.SoundPlay("koto.mp3");
	}
}

void PlayMode::SpawnGimmick1(Vector2& droppos, MapDropDateID id)
{
	if (lpEnergyMng.SubEnergy(50))
	{
		std::unique_ptr<Spike> tmpMonster = std::make_unique<Spike>();
		tmpMonster->Init();
		tmpMonster->SetMapMos(mapPos_);
		tmpMonster->ReSetPos(droppos);
		tmpMonster->SetStatus(StatusCtr::GetStates(StatusID::GImmick1));
		explorerVector_.emplace_back(std::move<>(tmpMonster));
		mapdat_[droppos.y][droppos.x] = BlockDate::Spike;
		CheckGoal();
		stable_sort(explorerVector_.begin(), explorerVector_.end(), [](auto& x, auto& y) {
			return x->GetPos().y < y->GetPos().y;
			});
		lpMapMng.SetDropEndF(id, true);
		lpSoundMng.SoundPlay("koto.mp3");
	}
}

void PlayMode::SpawnMonster3(const Vector2& droppos, MapDropDateID id)
{
	if (lpEnergyMng.SubEnergy(40))
	{
		std::unique_ptr<Rook> tmpAdventure = std::make_unique<Rook>();
		tmpAdventure->Init();
		tmpAdventure->SetMapMos(mapPos_);
		tmpAdventure->ReSetPos(droppos);
		MoveDir tmpDir = MoveDir::Down;
		SetDropDir(tmpDir);
		tmpAdventure->SetDir(lpRHSMng.CheckMove(droppos, tmpDir));
		tmpAdventure->SetStatus(StatusCtr::GetStates(StatusID::Monster3));
		explorerVector_.emplace_back(std::move<>(tmpAdventure));
		lpMapMng.SetDropEndF(id, true);
		lpSoundMng.SoundPlay("koto.mp3");
	}
}

void PlayMode::SetDropDir(MoveDir& tmpDir)
{
	int tnum = dorpDir_;
	if (tnum == 0)
	{
		tmpDir = MoveDir::Up;
	}
	else
		if (tnum == 1)
		{
			tmpDir = MoveDir::Right;
		}
		else
			if (tnum == 2)
			{
				tmpDir = MoveDir::Down;
			}
			else
				if (tnum == 3)
				{
					tmpDir = MoveDir::Left;
				}
				else
				{
					tmpDir = MoveDir::None;
				}
}

void PlayMode::SpawnMonster2(const Vector2& droppos, MapDropDateID id)
{
	if (lpEnergyMng.SubEnergy(30))
	{
		std::unique_ptr<Desmodus> tmpAdventure = std::make_unique<Desmodus>();
		tmpAdventure->Init();
		tmpAdventure->SetMapMos(mapPos_);
		tmpAdventure->ReSetPos(droppos);
		MoveDir tmpDir = MoveDir::Down;
		SetDropDir(tmpDir);
		tmpAdventure->SetDir(lpRHSMng.CheckMove(droppos, tmpDir));
		tmpAdventure->SetStatus(StatusCtr::GetStates(StatusID::Monster2));
		explorerVector_.emplace_back(std::move<>(tmpAdventure));
		lpMapMng.SetDropEndF(id, true);
		lpSoundMng.SoundPlay("koto.mp3");
	}
}

void PlayMode::SpawnMonster1(const Vector2& droppos, MapDropDateID id)
{
	if (lpEnergyMng.SubEnergy(10))
	{
		std::unique_ptr<Monster> tmpAdventure = std::make_unique<Monster>();
		tmpAdventure->Init();
		tmpAdventure->SetMapMos(mapPos_);
		tmpAdventure->ReSetPos(droppos);
		MoveDir tmpDir = MoveDir::Down;
		SetDropDir(tmpDir);
		tmpAdventure->SetDir(lpRHSMng.CheckMove(droppos, tmpDir));
		tmpAdventure->SetStatus(StatusCtr::GetStates(StatusID::Monster1));
		explorerVector_.emplace_back(std::move<>(tmpAdventure));
		lpMapMng.SetDropEndF(id, true);
		lpSoundMng.SoundPlay("koto.mp3");
	}
}

void PlayMode::SpawnKnight()
{
	std::unique_ptr<Knight> tmpAdventure = std::make_unique<Knight>();
	tmpAdventure->Init();
	tmpAdventure->SetMoveVec(goalNoade_);
	tmpAdventure->SetMapMos(mapPos_);
	tmpAdventure->ReSetPos(firstPos_);
	tmpAdventure->Knight::SetHP(100);
	tmpAdventure->SetDir(MoveDir::Down);
	tmpAdventure->SetStatus(nowStage_);
	explorerVector_.emplace_back(std::move<>(tmpAdventure));
}

void PlayMode::SpawnAdventer()
{
	std::unique_ptr<Adventurer> tmpAdventure = std::make_unique<Adventurer>();
	tmpAdventure->Init();
	tmpAdventure->SetMoveVec(goalNoade_);
	tmpAdventure->SetMapMos(mapPos_);
	tmpAdventure->ReSetPos(firstPos_);
	tmpAdventure->Adventurer::SetHP(2);
	tmpAdventure->SetDir(MoveDir::Down);
	tmpAdventure->SetStatus(nowStage_);
	explorerVector_.emplace_back(std::move<>(tmpAdventure));
}

void PlayMode::SpawnRateSub()
{
	if (spawnRate_ <= 50)
	{
		return;
	}
	if (con_ / 60 % 2)
	{
		spawnRate_--;
	}
}

void PlayMode::Draw(void)
{
	lpMouseMng.Draw();
	lpImglMng.GraphAddDrawQue("wood.png", { 0,0 }, 0);
	lpImglMng.GraphAddDrawQue("MapBack.png", { screenSize_.x / 10,screenSize_.y / 14 }, 0);
	SetDrawScreen(screenH_);
	ClsDrawScreen();

	for (int y = 0; y < mapSize_.y; y++)
	{
		for (int x = 0; x < mapSize_.x; x++)
		{
			//if (x * 32 + mapPos_.x - 32 > 1280 || y * 32 + mapPos_.y - 32 > 720 || x * 32 + mapPos_.x + 32 < 0 || y * 32 + mapPos_.y + 32 < 0)
			//{
			//	break;
			//}

			if (mapdat_[y][x] != BlockDate::Block)
			{
				DrawEdge(Vector2{ x,y });
			}
			DrawGraph(x * 32 + mapPos_.x, y * 32 + mapPos_.y, lpImglMng.GetGraphHandle(blockImg_[mapdat_[y][x]]), true);
#ifdef _DEBUG
			{
				std::unique_lock<std::mutex> lock(mapG_);
				DrawFormatString(x * 32 + mapPos_.x, y * 32 + mapPos_.y, 0xff0000, "%d", map_[y][x].nowstep);
			}
#endif // _DEBUG

		}
	}

	stable_sort(explorerVector_.begin(), explorerVector_.end(), [](auto& x, auto& y) {
		return x->GetPos().y < y->GetPos().y;
		});

	for (auto& explorer : explorerVector_)
	{
		explorer->Draw();
	}
	SetDrawScreen(DX_SCREEN_BACK);
	lpImglMng.ScreenAddDrawQue(screenH_, Vector2(155, 65), 2);
	uIScrolller_->Draw();
}

void PlayMode::Init(void)
{
	//各種初期化
	spF = false;
	BoseF_ = false;
	nowStage_ = 0;
	con_ = 0;
	eneSpawnCount_ = 0;
	enemyKillCount_ = 0;
	knightHP_ = 500;
	goalDelF_ = false;
	spawnRate_ = 500;
	mapPos_.x = -10;
	mapPos_.y = 0;
	explorerVector_.clear();
	srand(100);
	//UI初期化
	UIInit();
	//Energy初期化
	lpEnergyMng.Init();
	//ゴール地点を設定
	InitGoalNode();
	SetMousePoint(screenSize_.x / 2, screenSize_.y / 2);
}

void PlayMode::CheckGoal(void)
{
	//各種初期化
	finF_ = false;
	clearF_ = false;
	goalNoade_.clear();
	//スレッドを作成
	//std::thread findRoute(&PlayMode::AsterCheck,this);]

	AsterCheck();
	//スレッドを開始
	//findRoute.detach();
	return;
}

void PlayMode::InitMapDate(void)
{
	//マップサイズを設定
	mapSize_ = Vector2(static_cast<int>(mapdat_[0].size()), static_cast<int>(mapdat_.size()));
	//スタート地点、ゴール地点を設定
	for (int y = 0; y < mapSize_.y; y++)
	{
		for (int x = 0; x < mapSize_.x; x++)
		{
			if (mapdat_[y][x] == BlockDate::Start)
			{
				firstPos_ = Vector2(x, y);
			}
			if (mapdat_[y][x] == BlockDate::Goal)
			{
				goalPos_ = Vector2(x, y);
			}
			if (mapdat_[y][x] == BlockDate::DRoad)
			{
				mapdat_[y][x] = BlockDate::Road;
			}
		}
	}
}

void PlayMode::InitGoalNode(void)
{
	std::unique_ptr<Goal> tmpGoal = std::make_unique<Goal>();
	tmpGoal->Init();
	tmpGoal->SetMapMos(mapPos_);
	tmpGoal->ReSetPos(goalPos_);
	//１0ポイントに設定
	tmpGoal->SetHp(10);
	tmpGoal->SetDir(MoveDir::Up);
	explorerVector_.emplace_back(std::move<>(tmpGoal));
}

void PlayMode::UIInit(void)
{
	//座標設定
	//Vector2 tpos = { 15,25 };
	//Vector2 tsize = { 100,100 };
	//mapPos_ = { 0,0 };
	//lpUIMng.CreateUI(std::move<>(std::make_unique<UIMapBuildMenu>(std::move(tpos), std::move(tsize))), true);
	lpMapMng.SetMapMode(MapMode::Main);
	//UIを設定
	uIScrolller_->Init();
	lpSoundMng.StopSound("crea.mp3");
}

void PlayMode::DrawEdge(Vector2 pos)
{
	BlockEdge edge;
	//壁があるか調べる
	edge = isMapEdge(pos);
	//四方が囲まれていない場合
	if (edge.up && edge.right && edge.down && edge.left)
	{
		return;
	}
	//各方を描画
	if (!edge.up)
	{
		DrawGraph(pos.x * 32 + mapPos_.x, pos.y * 32 + mapPos_.y, lpImglMng.GetGraphHandle(roadImg_[0] ), true);
	}
	if (!edge.right)
	{
		DrawGraph(pos.x * 32 + mapPos_.x, pos.y * 32 + mapPos_.y, lpImglMng.GetGraphHandle(roadImg_[1]), true);
	}
	if (!edge.down)
	{
		DrawGraph(pos.x * 32 + mapPos_.x, pos.y * 32 + mapPos_.y, lpImglMng.GetGraphHandle(roadImg_[2]), true);
	}
	if (!edge.left)
	{
		DrawGraph(pos.x * 32 + mapPos_.x, pos.y * 32 + mapPos_.y, lpImglMng.GetGraphHandle(roadImg_[3]), true);
	}
}

BlockEdge PlayMode::isMapEdge(Vector2 pos)
{
	//Y座標がマップより大きい場合は空で返す
	if (mapdat_.size() <= pos.y)
	{
		return BlockEdge();
	}
	//Y座標がマイナス値の場合は空で返す
	if (0 > pos.y)
	{
		return BlockEdge();
	}
	//X座標がマップより大きい場合は空で返す
	if (mapdat_[pos.y].size() <= pos.x)
	{
		return BlockEdge();
	}
	//ｘ座標がマイナス値の場合は空で返す
	if (0 > pos.x)
	{
		return BlockEdge();
	}
	//チェック開始
	return CheckEdge(pos);
}

const BlockEdge PlayMode::CheckEdge(Vector2& pos)
{
	BlockEdge rtnEdge;
	//上側に壁がないかどうか
	if (0 <= pos.y - 1)
	{
		if (mapdat_[static_cast<size_t>(pos.y) - 1][pos.x] != BlockDate::Block)
		{
			rtnEdge.up = true;
		}
	}
	//右側に壁がないかどうか
	if (mapdat_[pos.y].size() > static_cast<size_t>(pos.x) + 1)
	{
		if (mapdat_[pos.y][static_cast<size_t>(pos.x) + 1] != BlockDate::Block)
		{
			rtnEdge.right = true;
		}
	}
	//下側に壁がないかどうか
	if (mapdat_.size() > static_cast<size_t>(pos.y) + 1)
	{
		if (mapdat_[static_cast<size_t>(pos.y) + 1][pos.x] != BlockDate::Block)
		{
			rtnEdge.down = true;
		}
	}
	//左側に壁がないかどうか
	if (0 <= pos.x - 1)
	{
		if (mapdat_[pos.y][static_cast<size_t>(pos.x) - 1] != BlockDate::Block)
		{
			rtnEdge.left = true;
		}
	}
	return rtnEdge;
}

void PlayMode::AsterCheck(void)
{
	//初期化
	lpAsterMng.Init(mapdat_, mapSize_);
	//探索開始
 	lpAsterMng.Start(firstPos_);
	//ゴールできるかどうか
	if (!lpAsterMng.IsGoal())
	{
		//ゴールできない場合
		//クリアできないマップであることを設定
		{
			std::unique_lock<std::mutex> lock(clearG_);
			clearF_ = false;
		}
		//ここで終了
		{
			std::unique_lock<std::mutex> lock(finG_);
			finF_ = true;
		}
		return;
	}
	//もしゴールしているならば
	
	//移動用のデータを初期化
	InitMovingDate();
	
	//クリアできるマップであることを設定
	{
		std::unique_lock<std::mutex> lock(clearG_);
		clearF_ = true;
	}
	//探索結果のマップを取得
	{
		std::unique_lock<std::mutex> lock(mapG_);
		map_ = lpAsterMng.Getmap();
	}
	//ここで終了
	{
		std::unique_lock<std::mutex> lock(finG_);
		finF_ = true;
	}
}

void PlayMode::InitMovingDate()
{
	//片手法移動用にマップデータを提供
	lpRHSMng.SetMapDate(mapdat_);
	
	//ゴールまでの道順を取得
	std::list<Vector2> gpos = lpAsterMng.GetGoalRoute();
	
	//逆順なので使えるように変更。
	{
		std::unique_lock<std::mutex> lock(clearG_);
		for (auto i = gpos.crbegin(); i != gpos.crend(); i++)
		{
			goalNoade_.emplace_back((*i));
		}
	}
}
