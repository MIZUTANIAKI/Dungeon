#pragma once
#include <map>

enum class StatusID
{
	MapSize,
	Monster1,
	Monster2,
	Monster3,
	GImmick1,
	GImmick2,
	PlayerHP,
	Stage,
	Max,
};

class StatusCtr
{
public:
	static int GetStates(StatusID id);
	static void SetStates(StatusID id,int num);
	static void Reset(void);
	static void OutPutD(void);
	static void DelDate(void);
private:
	static void InputD(void);
	static std::map<StatusID, int> statusMap_;
};

