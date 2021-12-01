#include "RightHandSearch.h"

RightHandSearch* RightHandSearch::sInstance = nullptr;

MoveDir RightHandSearch::CheckMove(Vector2 pos, MoveDir dir)
{

	if (dir == MoveDir::Up)
	{
		if (Check(Vector2(pos.x + 1, pos.y)))
		{
			return MoveDir::Right;
		}
		else if (Check(Vector2(pos.x, pos.y - 1)))
		{
			return MoveDir::Up;
		}
		else if (Check(Vector2(pos.x - 1, pos.y)))
		{
			return MoveDir::Left;
		}
		else if (Check(Vector2(pos.x, pos.y + 1)))
		{
			return MoveDir::Down;
		}
		else
		{
			return MoveDir::None;
		}
	}
	if (dir == MoveDir::Right)
	{
	if (Check(Vector2(pos.x, pos.y + 1)))
		{
			return MoveDir::Down;
		}
		else if (Check(Vector2(pos.x + 1, pos.y)))
		{
			return MoveDir::Right;
		}
		else if (Check(Vector2(pos.x, pos.y - 1)))
		{
			return MoveDir::Up;
		}
		else if (Check(Vector2(pos.x - 1, pos.y)))
		{
			return MoveDir::Left;
		}
		else
	{
		return MoveDir::None;
	}
	}
	if (dir == MoveDir::Down)
	{
		 if (Check(Vector2(pos.x - 1, pos.y)))
		{
			return MoveDir::Left;
		}
		else if (Check(Vector2(pos.x, pos.y + 1)))
		{
			return MoveDir::Down;
		}
		else if (Check(Vector2(pos.x + 1, pos.y)))
		{
			return MoveDir::Right;
		}
		else if (Check(Vector2(pos.x, pos.y - 1)))
		{
			return MoveDir::Up;
		}
		else
		 {
			 return MoveDir::None;
		 }
	}
	if (dir == MoveDir::Left)
	{
		if (Check(Vector2(pos.x, pos.y - 1)))
		{
			return MoveDir::Up;
		}
		else if (Check(Vector2(pos.x - 1, pos.y)))
		{
			return MoveDir::Left;
		}
		else if (Check(Vector2(pos.x, pos.y + 1)))
		{
			return MoveDir::Down;
		}
		else if (Check(Vector2(pos.x + 1, pos.y)))
		{
			return MoveDir::Right;
		}
		else
		{
			return MoveDir::None;
		}
	}

	return dir;
}

MoveDir RightHandSearch::CheckMoveSweev(Vector2 pos, MoveDir dir)
{
	if (dir == MoveDir::Up)
	{
		if (Check(Vector2(pos.x, pos.y - 1)))
		{
			return MoveDir::Up;
		}
		else if (Check(Vector2(pos.x + 1, pos.y)))
		{
			return MoveDir::Right;
		}
		else if (Check(Vector2(pos.x - 1, pos.y)))
		{
			return MoveDir::Left;
		}
		else if (Check(Vector2(pos.x, pos.y + 1)))
		{
			return MoveDir::Down;
		}
		else
		{
			return MoveDir::None;
		}
	}
	if (dir == MoveDir::Right)
	{
		 if (Check(Vector2(pos.x + 1, pos.y)))
		{
			return MoveDir::Right;
		}
		else if (Check(Vector2(pos.x, pos.y + 1)))
		{
			return MoveDir::Down;
		}
		else if (Check(Vector2(pos.x, pos.y - 1)))
		{
			return MoveDir::Up;
		}
		else if (Check(Vector2(pos.x - 1, pos.y)))
		{
			return MoveDir::Left;
		}
		else
		 {
			 return MoveDir::None;
		 }
	}
	if (dir == MoveDir::Down)
	{
		if (Check(Vector2(pos.x, pos.y + 1)))
		{
			return MoveDir::Down;
		}
		else if (Check(Vector2(pos.x - 1, pos.y)))
		{
			return MoveDir::Left;
		}
		else if (Check(Vector2(pos.x + 1, pos.y)))
		{
			return MoveDir::Right;
		}
		else if (Check(Vector2(pos.x, pos.y - 1)))
		{
			return MoveDir::Up;
		}
		else
		{
			return MoveDir::None;
		}
	}
	if (dir == MoveDir::Left)
	{
		if (Check(Vector2(pos.x - 1, pos.y)))
		{
			return MoveDir::Left;
		}
		else if (Check(Vector2(pos.x, pos.y - 1)))
		{
			return MoveDir::Up;
		}
		else if (Check(Vector2(pos.x, pos.y + 1)))
		{
			return MoveDir::Down;
		}
		else if (Check(Vector2(pos.x + 1, pos.y)))
		{
			return MoveDir::Right;
		}
		else
		{
			return MoveDir::None;
		}
	}

	return dir;
}

MoveDir RightHandSearch::CheckMoveL(Vector2 pos, MoveDir dir)
{
	if (dir == MoveDir::Up)
	{
		if (Check(Vector2(pos.x - 1, pos.y)))
		{
			return MoveDir::Left;
		}
		else if (Check(Vector2(pos.x, pos.y - 1)))
		{
			return MoveDir::Up;
		}
		else if (Check(Vector2(pos.x + 1, pos.y)))
		{
			return MoveDir::Right;
		}
		else if (Check(Vector2(pos.x, pos.y + 1)))
		{
			return MoveDir::Down;
		}
		else
		{
			return MoveDir::None;
		}
	}
	if (dir == MoveDir::Right)
	{
		if (Check(Vector2(pos.x, pos.y - 1)))
		{
			return MoveDir::Up;
		}
		else if (Check(Vector2(pos.x + 1, pos.y)))
		{
			return MoveDir::Right;
		}
		else if (Check(Vector2(pos.x, pos.y + 1)))
		{
			return MoveDir::Down;
		}
		else if (Check(Vector2(pos.x - 1, pos.y)))
		{
			return MoveDir::Left;
		}
		else
		{
			return MoveDir::None;
		}
	}
	if (dir == MoveDir::Down)
	{
		if (Check(Vector2(pos.x + 1, pos.y)))
		{
			return MoveDir::Right;
		}
		else if (Check(Vector2(pos.x, pos.y + 1)))
		{
			return MoveDir::Down;
		}
		else if(Check(Vector2(pos.x - 1, pos.y)))
		{
			return MoveDir::Left;
		}
		else if(Check(Vector2(pos.x, pos.y - 1)))
		{
			return MoveDir::Up;
		}
		else
		{
			return MoveDir::None;
		}
	}
	if (dir == MoveDir::Left)
	{
		if (Check(Vector2(pos.x, pos.y + 1)))
		{
			return MoveDir::Down;
		}
		else if (Check(Vector2(pos.x - 1, pos.y)))
		{
			return MoveDir::Left;
		}
		else if (Check(Vector2(pos.x, pos.y - 1)))
		{
			return MoveDir::Up;
		}
		else if(Check(Vector2(pos.x + 1, pos.y)))
		{
			return MoveDir::Right;
		}
		else
		{
			return MoveDir::None;
		}
	}

	return dir;
}

MoveDir RightHandSearch::CheckMoveRL(Vector2 pos, MoveDir dir)
{
	if (dir == MoveDir::Up)
	{
		if (Check(Vector2(pos.x, pos.y - 1)))
		{
			return MoveDir::Up;
		}
		int n = rand() % 2;
		if (n==0)
		{
			if (Check(Vector2(pos.x + 1, pos.y)))
			{
				return MoveDir::Right;
			}
			else if (Check(Vector2(pos.x - 1, pos.y)))
			{
				return MoveDir::Left;
			}
		}
		else
		{
			if (Check(Vector2(pos.x - 1, pos.y)))
			{
				return MoveDir::Left;
			}
			else if (Check(Vector2(pos.x + 1, pos.y)))
			{
				return MoveDir::Right;
			}
		}

		if (Check(Vector2(pos.x, pos.y + 1)))
		{
			return MoveDir::Down;
		}
		else
		{
			return MoveDir::None;
		}
	}
	if (dir == MoveDir::Right)
	{
		if (Check(Vector2(pos.x + 1, pos.y)))
		{
			return MoveDir::Right;
		}
		int n = rand() % 2;
		if (n == 0)
		{
			if (Check(Vector2(pos.x, pos.y - 1)))
			{
				return MoveDir::Up;
			}
			else if (Check(Vector2(pos.x, pos.y + 1)))
			{
				return MoveDir::Down;
			}
		}
		else
		{
			if (Check(Vector2(pos.x, pos.y + 1)))
			{
				return MoveDir::Down;
			}
			else if (Check(Vector2(pos.x, pos.y - 1)))
			{
				return MoveDir::Up;
			}
		}

		if (Check(Vector2(pos.x, pos.y + 1)))
		{
			return MoveDir::Down;
		}
		else
		{
			return MoveDir::None;
		}
	}
	if (dir == MoveDir::Down)
	{
	
		if (Check(Vector2(pos.x, pos.y + 1)))
		{
			return MoveDir::Down;
		}

		int n = rand() % 2;
		if (n == 0)
		{
			if (Check(Vector2(pos.x + 1, pos.y)))
			{
				return MoveDir::Right;
			}
			else if (Check(Vector2(pos.x - 1, pos.y)))
			{
				return MoveDir::Left;
			}
		}
		else
		{
			if (Check(Vector2(pos.x - 1, pos.y)))
			{
				return MoveDir::Left;
			}
			else if (Check(Vector2(pos.x + 1, pos.y)))
			{
				return MoveDir::Right;
			}
		}

		if (Check(Vector2(pos.x, pos.y - 1)))
		{
			return MoveDir::Up;
		}
		else
		{
			return MoveDir::None;
		}
		
	}
	if (dir == MoveDir::Left)
	{
		if (Check(Vector2(pos.x - 1, pos.y)))
		{
			return MoveDir::Left;
		}
		int n = rand() % 2;
		if (n == 0)
		{
			if (Check(Vector2(pos.x, pos.y - 1)))
			{
				return MoveDir::Up;
			}
			else if (Check(Vector2(pos.x, pos.y + 1)))
			{
				return MoveDir::Down;
			}
		}
		else
		{
			if (Check(Vector2(pos.x, pos.y + 1)))
			{
				return MoveDir::Down;
			}
			else if (Check(Vector2(pos.x, pos.y - 1)))
			{
				return MoveDir::Up;
			}
		}

		if (Check(Vector2(pos.x + 1, pos.y)))
		{
			return MoveDir::Right;
		}
		else
		{
			return MoveDir::None;
		}
	}

	return dir;
}

BlockEdge RightHandSearch::GetMapChipHit(Vector2 pos)
{
	BlockEdge tmpbe;

	if (Check(Vector2(pos.x, pos.y - 1)))
	{
		tmpbe.up = true;
	}
	if (Check(Vector2(pos.x + 1, pos.y)))
	{
		tmpbe.right = true;
	}
	if (Check(Vector2(pos.x, pos.y + 1)))
	{
		tmpbe.down = true;
	}
	if (Check(Vector2(pos.x - 1, pos.y)))
	{
		tmpbe.left = true;
	}
	return tmpbe;
}

bool RightHandSearch::Check(Vector2 pos)
{
	if (pos.x < mapdat_[0].size() && pos.y < mapdat_.size() && pos.x >= 0 && pos.y >= 0)
	{
		if (mapdat_[pos.y][pos.x] != BlockDate::Block)
		{
			return true;
		}
	}
	return false;
}

RightHandSearch::RightHandSearch()
{
}

RightHandSearch::~RightHandSearch()
{
}
