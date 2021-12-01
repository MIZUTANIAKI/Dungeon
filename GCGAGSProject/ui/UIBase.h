#pragma once
#include <memory>
#include <string>
#include "Vector2.h"

enum class UiDateType
{
	Btn,
	Txt,
};

class UIBase;
using UNUI = std::unique_ptr<UIBase>;
class UIBase
{
public:
	UIBase();
	UIBase(Vector2 pos, Vector2 size);
	virtual ~UIBase() = default;

	virtual void Update(void) = 0;
	virtual void SetDate(void) = 0;
	virtual void SetDate(std::string str) {};
	virtual void Draw(void) = 0;
	void Reset(void);

	void SetPos(Vector2 pos);
protected:
	Vector2 pos_;
	Vector2 size_;
	int screenHandle_;
	void CreatSscreen(Vector2 pos, Vector2 size);
};