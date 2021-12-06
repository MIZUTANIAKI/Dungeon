#include <string>
#include <algorithm>
#include <DxLib.h>
#include "UIMapBuildMenu.h"
#include "Monster.h"
#include "Spike.h"
#include "Gate.h"
#include "MoneyMng.h"
#include "MouseMng.h"
#include "SaveMap.h"
#include "PadMng.h"
#include "MapDatList.h"
#include "MapSelect.h"
#include "ImageMng.h"
#include "UIMng.h"
#include "SoundMng.h"
#include "StatusCtr.h"

MapSelect::MapSelect()
{
	mapNum_ = 0;
	GetDrawScreenSize(&screenSize_.x, &screenSize_.y);
	screenH_ = MakeScreen(1000 - 32, 550, true);
	mapSize_.x = 31;
	mapSize_.y = 10/*17*/;
	mapdat_.resize(mapSize_.y);
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
			else
			{
				mapdat_[y][x] = BlockDate::Block;
			}
		}
	}
	MapDatList::AddDate(mapdat_);
	blockImg_.try_emplace(BlockDate::Start, lpImglMng.LoadGraph("start.png"));
	blockImg_.try_emplace(BlockDate::Block, lpImglMng.LoadGraph("block.png"));
	blockImg_.try_emplace(BlockDate::Goal, lpImglMng.LoadGraph("End.png"));
	blockImg_.try_emplace(BlockDate::Road, lpImglMng.LoadGraph("Nonblock.png"));
	blockImg_.try_emplace(BlockDate::DRoad, lpImglMng.LoadGraph("NonblockD.png"));
	roadImg_.emplace_back(lpImglMng.LoadGraph("Up.png"));
	roadImg_.emplace_back(lpImglMng.LoadGraph("Right.png"));
	roadImg_.emplace_back(lpImglMng.LoadGraph("Down.png"));
	roadImg_.emplace_back(lpImglMng.LoadGraph("Left.png"));

	//screenH_ = MakeScreen(1000 - 32, 550, true);

	Init();
	//std::unique_ptr<SaveMap> smap = std::make_unique<SaveMap>();
	//smap->StartInPut(NULL);
	//mapdat_ = smap->GetMapdate();
}

MapSelect::~MapSelect()
{
}

void MapSelect::Update(float deltaTime_)
{
	if (!lpSoundMng.CheckPlaySound("crea.mp3"))
	{
		lpSoundMng.SoundPlay("crea.mp3");
	}
	//if (CheckHitKey(KEY_INPUT_LCONTROL) && CheckHitKey(KEY_INPUT_R))
	//{
	//	mapPos_.x = -10;
	//	mapPos_.y = 0;
	//	ResetMap();
	//	MapDatList::AddDate(mapdat_);
	//}

	//if (CheckHitKey(KEY_INPUT_LCONTROL) && CheckHitKey(KEY_INPUT_C))
	//{
	//	SaveMapDat();
	//}

	//if (CheckHitKey(KEY_INPUT_LCONTROL) && CheckHitKey(KEY_INPUT_V))
	//{
	//	RoadMapDat();
	//	MapDatList::AddDate(mapdat_);
	//}
	

	if (CheckHitKey(KEY_INPUT_LCONTROL) && CheckHitKey(KEY_INPUT_Z))
	{
		if (!pressZ_)
		{
			pressZ_ = true;
			auto tmpMapDat = MapDatList::GetDate();
			if (!tmpMapDat.empty())
			{
				mapdat_ = tmpMapDat;
			}
		}
	}
	else
	{
		pressZ_ = false;
	}

	Vector2 nowMPos = lpMouseMng.GetMousePos();

	BuildRoad(nowMPos);
	if (CheckHitKey(KEY_INPUT_W))
	{
		if ((mapSize_.y - 1) * 32 + mapPos_.y - 1 > 550 - 60)
		{
			mapPos_.y--;
		}
	}
	//if (CheckHitKey(KEY_INPUT_D))
	//{
	//	if (mapPos_.x < 1)
	//	{
	//		mapPos_.x++;
	//	}
	//
	if (CheckHitKey(KEY_INPUT_S))
	{
		if (mapPos_.y < 1)
		{
			mapPos_.y++;
		}
	}
	//if (CheckHitKey(KEY_INPUT_A))
	//{
	//	if ((mapSize_.x) * 32 + mapPos_.x - 1 > 1000 - 35)
	//	{
	//		mapPos_.x--;
	//	}
	//}


	if (lpPadMng.GetControllerData(InputID::BtnB))
	{
		mapNum_ = 1;
	}

	//if (CheckHitKey(KEY_INPUT_SPACE))
	//{
	//	if (mapNum_ == 1)
	//	{
	//		return;
	//	}
	//	mapNum_ = 1;
	//}
	//else
	//{
	//	mapNum_ = 0;
	//}

	SetPlaterPos();
}

void MapSelect::SetPlaterPos()
{
	//if (lpMouseMng.GetMousePos().x < 145 && lpMouseMng.GetMousePos().y < 65 && lpMouseMng.GetMousePos().y > 582 && lpMouseMng.GetMousePos().x > 1110)
	//{
	//	return;
	//}
	//if (!lpPadMng.IsPlugInForGamePad())
	//{
	//	return;
	//}
	//if(!lpPadMng.GetNowControllerData(InputID::Up)&& !lpPadMng.GetNowControllerData(InputID::Right) && !lpPadMng.GetNowControllerData(InputID::Down) && !lpPadMng.GetNowControllerData(InputID::Left))
	//{
	//	lpMouseMng.SetPos({ lpMouseMng.GetMousePos().x / 32 * 32 + 10 + 16,lpMouseMng.GetMousePos().y / 32 * 32 + 16 });
	//}
}

void MapSelect::BuildRoad(Vector2& nowMPos)
{
	if (lpMapMng.GetMapMode() != MapMode::Main)
	{
		return;
	}
	if (nowMPos.x < 145 && nowMPos.y < 65 && nowMPos.y > 582 && nowMPos.x > 1110)
	{
		return;
	}
	nowMPos.x -= 145;
	nowMPos.y -= 65;
	nowMPos.x -= mapPos_.x;
	nowMPos.y -= mapPos_.y;
	nowMPos.x /= 32;
	nowMPos.y /= 32;
	if (nowMPos.y >= mapSize_.y - 1)
	{
		return;
	}
	if (nowMPos.y > 0 &&
		nowMPos.x > 0 &&
		nowMPos.x < mapSize_.x-1 &&
		nowMPos.y < mapSize_.y)
	{
		if (!lpMouseMng.IsExclusive())
		{
		}
			if (lpMouseMng.IsLeftClick()/*&& !(lpMouseMng.GetOldInputDat() & MOUSE_INPUT_LEFT)*/)
			{
				if (mapdat_[nowMPos.y][nowMPos.x] == BlockDate::Block)
				{
					if (lpMoneyMng.SubMoney(2))
					{
						MapDatList::AddDate(mapdat_);
						mapdat_[nowMPos.y][nowMPos.x] = BlockDate::Road;
						lpSoundMng.StopSound("kaku.mp3");
						lpSoundMng.SoundPlay("kaku.mp3");
					}
				}
			}
			if (lpMouseMng.IsRightClick() /*&& !(lpMouseMng.GetOldInputDat() & MOUSE_INPUT_RIGHT)*/)
			{
				if (mapdat_[nowMPos.y][nowMPos.x] == BlockDate::Road)
				{
					MapDatList::AddDate(mapdat_);
					mapdat_[nowMPos.y][nowMPos.x] = BlockDate::Block;
					lpMoneyMng.AddMoney(2);
					lpSoundMng.StopSound("kaku.mp3");
					lpSoundMng.SoundPlay("kaku.mp3");
					auto itr = dateBox_.begin();
					while (itr != dateBox_.end())
					{
						if ((*itr)->GetPos() / 32 == nowMPos)
						{

							itr = dateBox_.erase(itr);
						}
						else
						{
							itr++;
						}
					}
				}
			}
		
	}
}

void MapSelect::Draw(float deltaTime_)
{
	lpMouseMng.Draw();
	lpImglMng.GraphAddDrawQue("wood.png", { 0,0 }, 0);
	lpImglMng.GraphAddDrawQue("MapBack.png", { screenSize_.x / 10,screenSize_.y / 14 }, 0);
	SetDrawScreen(screenH_);
	ClsDrawScreen();
	//SetDrawScreen(screenH_);
	//ClsDrawScreen();

	for (auto& dbox : dateBox_)
	{
		dbox->SetMapMos(mapPos_);
		dbox->Draw();
	}

	for (int y = 0; y < mapSize_.y; y++)
	{
		for (int x = 0; x < mapSize_.x; x++)
		{
  			if (!CheckDraw(x, y))
			{
				break;
			}
			if (mapdat_[y][x] != BlockDate::Block)
			{
				DrawEdge(Vector2{ x,y });
			}
			if (mapdat_[y][x] != BlockDate::Gate && mapdat_[y][x] != BlockDate::Spike)
			{
				DrawGraph(x * 32 + mapPos_.x, y * 32 + mapPos_.y, lpImglMng.GetGraphHandle(blockImg_[mapdat_[y][x]]), true);
			}
		}
	}

	//SetDrawScreen(DX_SCREEN_BACK);
	//lpImglMng.ScreenAddDrawQue(screenH_, Vector2(145, 65));
	SetDrawScreen(DX_SCREEN_BACK);
	lpImglMng.ScreenAddDrawQue(screenH_, Vector2(155, 65), 2);
}

bool MapSelect::CheckDraw(int x, int y)
{
	if (y * 32 + mapPos_.y - 32 > 601)
	{
		return false;
	}
	return true;
}

void MapSelect::Init()
{
	lpSoundMng.StopSound("game.mp3");
	pressZ_ = false;
	mapPos_.x = -10;
	mapPos_.y = 0;	
	lpMapMng.SetMapMode(MapMode::Main);
	MapDatList::Init();
	MapDatList::AddDate(mapdat_);
	SetMousePoint(screenSize_.x / 2, screenSize_.y / 2);

	for (int y = 0; y < mapSize_.y; y++)
	{
		for (int x = 0; x < mapSize_.x; x++)
		{
			if(mapdat_[y][x] == BlockDate::Road)
			{
				mapdat_[y][x] = BlockDate::DRoad;
			}
		}
	}
	
	do
	{
		mapdat_.resize(static_cast<size_t>(mapSize_.y) + static_cast<size_t>(1));

		mapdat_[mapSize_.y].resize(mapSize_.x);
		mapSize_.y += 1;
		for (int y = mapSize_.y - 2; y < mapSize_.y; y++)
		{

			for (int x = 0; x < mapSize_.x; x++)
			{
				if (y == mapSize_.y - 1 && x == mapSize_.x / 2 - 1)
				{
					mapdat_[y][x] = BlockDate::Goal;
				}
				else
				{
					mapdat_[y][x] = BlockDate::Block;
				}
			}
		}
	} while (StatusCtr::GetStates(StatusID::MapSize) > mapSize_.y);
	StatusCtr::SetStates(StatusID::MapSize, mapSize_.y);
	StatusCtr::OutPutD();
	lpMoneyMng.SetStartFlag(false);
}

void MapSelect::SetStageID(int stageID)
{
	RoadMapDat(stageID);
	MapDatList::AddDate(mapdat_);
}

void MapSelect::SaveStage(void)
{
	SaveMapDat(2);
}


bool MapSelect::IsDubDate(Vector2 pos)
{
	for (auto& dbox : dateBox_)
	{
		if (dbox->GetPos() / 32 == pos)
		{
			return true;
		}
	}
	return false;
}

void MapSelect::DrawEdge(Vector2 pos)
{
	BlockEdge edge;
	edge = isMapEdge(pos);
	if (edge.up && edge.right && edge.down && edge.left)
	{
		return;
	}
	if (!edge.up)
	{
		DrawGraph(pos.x * 32 + mapPos_.x, pos.y * 32 + mapPos_.y, lpImglMng.GetGraphHandle(roadImg_[0]), true);
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

BlockEdge MapSelect::isMapEdge(Vector2 pos)
{
	if (mapdat_.size() <= pos.y)
	{
		return BlockEdge();
	}
	if (0 > pos.y)
	{
		return BlockEdge();
	}
	if (mapdat_[pos.y].size() <= pos.x)
	{
		return BlockEdge();
	}
	if (0 > pos.x)
	{
		return BlockEdge();
	}
	BlockEdge rtnEdge;
	if (0 <= pos.y - 1)
	{
		if (mapdat_[pos.y - static_cast<size_t>(1)][pos.x] != BlockDate::Block)
		{
			rtnEdge.up = true;
		}
	}
	if (mapdat_[pos.y].size() > pos.x + static_cast<size_t>(1))
	{
		if (mapdat_[pos.y][pos.x + static_cast<size_t>(1)] != BlockDate::Block)
		{
			rtnEdge.right = true;
		}
	}
	if (mapdat_.size() > pos.y + static_cast<size_t>(1))
	{
		if (mapdat_[pos.y + static_cast<size_t>(1)][pos.x] != BlockDate::Block)
		{
			rtnEdge.down = true;
		}
	}
	if (0 <= pos.x - 1)
	{
		if (mapdat_[pos.y][pos.x - static_cast<size_t>(1)] != BlockDate::Block)
		{
			rtnEdge.left = true;
		}
	}

	return rtnEdge;
}

void MapSelect::ResetMap(void)
{
	for (int y = 0; y < mapSize_.y; y++)
	{
		for (int x = 0; x < mapSize_.x; x++)
		{
			if (mapdat_[y][x] != BlockDate::Block && mapdat_[y][x] != BlockDate::Goal && mapdat_[y][x] != BlockDate::Start)
			{
				mapdat_[y][x] = BlockDate::Block;
			}
		}
	}
	auto itr = dateBox_.begin();
	while (itr != dateBox_.end())
	{
		itr = dateBox_.erase(itr);
	}
}

void MapSelect::RoadMapDat(int stageID)
{
	mapPos_.x = -10;
	mapPos_.y = 0;
	ResetMap();
	std::unique_ptr<SaveMap> smap = std::make_unique<SaveMap>();
	smap->StartInPut(stageID);
	mapdat_ = smap->GetMapdate();
	mapSize_ = Vector2(static_cast<int>(mapdat_[0].size()), static_cast<int>(mapdat_.size()));
}

void MapSelect::SaveMapDat(int num)
{
	std::unique_ptr<SaveMap> smap = std::make_unique<SaveMap>();
	smap->SetMapdate(mapdat_);
	smap->StartOutPut(num);
}
