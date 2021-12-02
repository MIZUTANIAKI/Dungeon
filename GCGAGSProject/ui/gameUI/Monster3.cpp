#include "Monster3.h"
#include "ImageMng.h"

Monster3::Monster3()
{
	pos_ = { 0,0 };
	Init();
}

Monster3::Monster3(Vector2 pos)
{
	pos_ = pos;
	Init();
}

Monster3::~Monster3()
{
}

void Monster3::Update(void)
{
	DragMove();
	DeleteUi();
}

void Monster3::Draw(void)
{
	lpImglMng.DrawImg("menu5.png", pos_);
	GrabDraw();
}

void Monster3::Init()
{
	delF_ = false;
	id_ = MapDropDateID::Rook;
	cost_ = 40;
}
