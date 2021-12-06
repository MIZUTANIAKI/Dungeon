#pragma once
#include "Vector2.h"
#include "MapMng.h"

class ScrollUIBase
{
public:
	ScrollUIBase();
	ScrollUIBase(Vector2 pos);
	virtual ~ScrollUIBase() = default;

	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void SetLockOff(void);

	bool GetDelFlag()const noexcept
	{
		return delF_;
	}

	Vector2 GetPos(void)
	{
		return pos_;
	}
	void SetPos(Vector2 pos)
	{
		pos_ = pos;
	}

	MapDropDateID GetID()
	{
		return id_;
	}
	int GetCost()
	{
		return cost_;
	}
protected:
	virtual void Init() = 0;
	void DragMove(void);
	void DeleteUi();
	void GrabDraw(void);

	Vector2 pos_;
	bool delF_;
	MapDropDateID id_;
	int cost_;

	bool isClick_;
	static bool isLock_;
	Vector2 clickPos_;
};

