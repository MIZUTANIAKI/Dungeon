#pragma once
#include <array>
#include "common/Vector2.h"

#define lpMouseMng MouseMng::GetInstance()

class MouseMng
{
public:
	static MouseMng& GetInstance(void)
	{
		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new MouseMng();
		}
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}

	void Update(void);

	void Draw(void);
	
	Vector2 GetMousePos(void)
	{
		return mousePos_;
	}

	Vector2 GetMouseOldPos(void)
	{
		return oldMousePos_[0];
	}
	
	int GetInputDat(void)
	{
		return inputdate_;
	}

	int GetOldInputDat(void)
	{
		return inputdateold_;
	}

	bool GetisMoving(void)
	{
		return isMoving_;
	}

	bool IsLeftClick(void);

	bool IsRightClick(void);

	bool IsExclusive(void)
	{
		return isExclusive_;
	}

	void SetExclusive(bool flag)
	{
		isExclusive_ = flag;
	}
	
	void AddPos(Vector2 pos)
	{
		isMoving_ = true;
		mousePos_ += pos;
	}
	void SetPos(Vector2 pos);
	void SetMouseClickR(void);
	void SetMouseClickL(void);
private:
	static MouseMng* sInstance;

	void SetOldPos(Vector2 pos);

	Vector2 clickPos_;
	int clickCount_;
	bool isClickRight_;
	bool isMoving_;

	int inputdate_;
	int inputdateold_;

	Vector2 mousePos_;

	std::array<Vector2, 10> oldMousePos_;

	int mouseSclH_;

	//int oldMousePointer_;
	bool isExclusive_;
	MouseMng();
	~MouseMng();
};

