#include <string>
#include <algorithm>
#include "MapTest.h"
#include "ImageMng.h"
#include <DxLib.h>
#include "UIMng.h"
#include "UIMapBuildMenu.h"
#include "Monster.h"
#include "Spike.h"
#include "Gate.h"
#include "MoneyMng.h"
#include "MouseMng.h"
#include "SaveMap.h"

MapTest::MapTest()
{
	mapSize_.x = 35;
	mapSize_.y = 17;
	mapdat_.resize(mapSize_.y);
	for (int y = 0; y < mapSize_.y; y++)
	{
		mapdat_[y].resize(mapSize_.x);
	}

	for (int y = 0; y < mapSize_.y; y++)
	{
		for (int x = 0; x < mapSize_.x; x++)
		{
			if (y == 0 && x == mapSize_.x / 2-1)
			{
				mapdat_[y][x] = BlockDate::Start;
			}
			else if (y == mapSize_.y - 1 && x == mapSize_.x / 2-1)
			{
				mapdat_[y][x] = BlockDate::Goal;
			}
			else
			{
				mapdat_[y][x] = BlockDate::Block;
			}
		}
	}
	blockImg_.try_emplace(BlockDate::Start, lpImglMng.LoadGraph("start.png"));
	blockImg_.try_emplace(BlockDate::Block, lpImglMng.LoadGraph("block.png"));
	blockImg_.try_emplace(BlockDate::Goal, lpImglMng.LoadGraph("End.png"));
	roadImg_.emplace_back(lpImglMng.LoadGraph("Up.png"));
	roadImg_.emplace_back(lpImglMng.LoadGraph("Right.png"));
	roadImg_.emplace_back(lpImglMng.LoadGraph("Down.png"));
	roadImg_.emplace_back(lpImglMng.LoadGraph("Left.png"));

	screenH_ = MakeScreen(1000-32, 550, true);
	mapPos_.x = 0;
	mapPos_.y = 0;
	Init();
}

MapTest::~MapTest()
{
}

void MapTest::Update()
{
	if (CheckHitKey(KEY_INPUT_LCONTROL) && CheckHitKey(KEY_INPUT_R))
	{
		mapPos_.x = 0;
		mapPos_.y = 0;
		ResetMap();
	}

	if(CheckHitKey(KEY_INPUT_LCONTROL) && CheckHitKey(KEY_INPUT_C))
	{
		SaveMapDat();
	}

	if (CheckHitKey(KEY_INPUT_LCONTROL) && CheckHitKey(KEY_INPUT_V))
	{
		RoadMapDat();
	}

	Vector2 nowMPos = lpMouseMng.GetMousePos();

	if (lpMapMng.GetMapMode() == MapMode::Main)
	{
		if (nowMPos.x >= 145 && nowMPos.y >= 65 && nowMPos.y <= 582 && nowMPos.x <= 1110)
		{
			nowMPos.x -= 145;
			nowMPos.y -= 65;
			nowMPos.x -= mapPos_.x;
			nowMPos.y -= mapPos_.y;
			nowMPos.x /= 32;
			nowMPos.y /= 32;
			if (nowMPos.y > 0 &&
				nowMPos.x >= 0 &&
				nowMPos.x < mapSize_.x &&
				nowMPos.y < mapSize_.y)
			{
				if (!lpMouseMng.IsExclusive())
				{
					if (lpMouseMng.IsLeftClick()/*&& !(lpMouseMng.GetOldInputDat() & MOUSE_INPUT_LEFT)*/)
					{
						if (mapdat_[nowMPos.y][nowMPos.x] == BlockDate::Block)
						{
							if (lpMoneyMng.SubMoney(2))
							{
								mapdat_[nowMPos.y][nowMPos.x] = BlockDate::Road;
							}
						}
					}
					if (lpMouseMng.IsRightClick() /*&& !(lpMouseMng.GetOldInputDat() & MOUSE_INPUT_RIGHT)*/)
					{
						if (mapdat_[nowMPos.y][nowMPos.x] == BlockDate::Road)
						{
							mapdat_[nowMPos.y][nowMPos.x] = BlockDate::Block;
							lpMoneyMng.AddMoney(2);
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
		}
	}
	if (CheckHitKey(KEY_INPUT_W))
	{
		if ((mapSize_.y - 1) * 32 + mapPos_.y - 1 > 550 - 60)
		{
			mapPos_.y--;
		}
	}

	if (CheckHitKey(KEY_INPUT_D))
	{
		if (mapPos_.x < 1)
		{
			mapPos_.x++;
		}
	}

	if (CheckHitKey(KEY_INPUT_S))
	{
		if (mapPos_.y < 1)
		{
			mapPos_.y++;
		}
	}

	if (CheckHitKey(KEY_INPUT_A))
	{
		if ((mapSize_.x) * 32 + mapPos_.x - 1 > 1000 - 35)
		{
			mapPos_.x--;
		}
	}
}

void MapTest::Draw()
{
	SetDrawScreen(screenH_);
	ClsDrawScreen();

	for (auto& dbox : dateBox_)
	{
		dbox->SetMapMos(mapPos_);
		dbox->Draw();
	}
	Vector2 slimePos, desmodusPos;
	slimePos = desmodusPos = { 0, 0 };
	for (int y = 0; y < mapSize_.y; y++)
	{
		for (int x = 0; x < mapSize_.x; x++)
		{

			switch (mapdat_[y][x])
			{
			case BlockDate::Block:
				//DrawGraph(x * 32+ mapPos_.x, y * 32 + mapPos_.y, lpImglMng.GetGraphHandle(blockImg_[mapdat_[y][x]]).first, true);
				break;
			case BlockDate::Road:
				DrawEdge(Vector2{ x,y });
				break;
			case BlockDate::Start:
				lpImglMng.DrawImg(blockImg_[mapdat_[y][x]], Vector2(x * 32 + mapPos_.x, y * 32 + mapPos_.y));
				//DrawGraph(x * 32 + mapPos_.x, y * 32 + mapPos_.y, lpImglMng.GetGraphHandle(blockImg_[mapdat_[y][x]]), true);
				DrawEdge(Vector2{ x,y });
				break;
			case BlockDate::Goal:
				lpImglMng.DrawImg(blockImg_[mapdat_[y][x]], Vector2(x * 32 + mapPos_.x, y * 32 + mapPos_.y));
				//DrawGraph(x * 32 + mapPos_.x, y * 32 + mapPos_.y, lpImglMng.GetGraphHandle(blockImg_[mapdat_[y][x]]), true);
				DrawEdge(Vector2{ x,y });
				break;
			default:
				break;
			}
		}
	}
	if (slimePos != Vector2(0, 0))
	{
		lpImglMng.GraphAddDrawQue("testC2.png", slimePos, 20);
	}
	if (desmodusPos != Vector2(0, 0))
	{
		lpImglMng.GraphAddDrawQue("testC3.png", desmodusPos, 20);
	}
	SetDrawScreen(DX_SCREEN_BACK);
	lpImglMng.ScreenAddDrawQue(screenH_, Vector2(145, 65),10);
}

void MapTest::Init()
{
	//Vector2 tpos = { 15,25 };
	//Vector2 tsize = { 100,100 };
	//mapPos_ = {0,0};
	//lpUIMng.CreateUI(std::move<>(std::make_unique<UIMapBuildMenu>(std::move(tpos), std::move(tsize))), true);
	lpMapMng.SetMapMode(MapMode::Main);
}

bool MapTest::IsDubDate(Vector2 pos)
{

	for (auto& dbox : dateBox_)
	{
		if (dbox->GetPos()/32 == pos)
		{
			return true;
		}
	}
	return false;
}

void MapTest::DrawEdge(Vector2 pos)
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

BlockEdge MapTest::isMapEdge(Vector2 pos)
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
		if (mapdat_[pos.y - static_cast<size_t>(1)][pos.x]!=BlockDate::Block)
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

void MapTest::ResetMap(void)
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
	lpMoneyMng.SetMoney(9999);
}

void MapTest::RoadMapDat(void)
{
	mapPos_.x = 0;
	mapPos_.y = 0;
	ResetMap();
	std::unique_ptr<SaveMap> smap = std::make_unique<SaveMap>();
	smap->StartInPut(NULL);
	mapdat_ = smap->GetMapdate();
}

void MapTest::SaveMapDat(void)
{
	std::unique_ptr<SaveMap> smap = std::make_unique<SaveMap>();
	smap->SetMapdate(mapdat_);
	smap->StartOutPut();
}
