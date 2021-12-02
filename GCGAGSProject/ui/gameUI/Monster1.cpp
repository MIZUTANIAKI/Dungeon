#include "Monster1.h"
#include "ImageMng.h"


Monster1::Monster1()
{
	pos_ = { 0,0 };
	Init();
}

Monster1::Monster1(Vector2 pos)
{
	pos_ = pos;
	Init();
}

Monster1::~Monster1()
{
}

void Monster1::Update(void)
{
	DragMove();
	DeleteUi();
}

void Monster1::Draw(void)
{
	lpImglMng.DrawImg("menu1.png", pos_);
	GrabDraw();
}

void Monster1::Init()
{
	delF_ = false;
	id_ = MapDropDateID::Slime;
	cost_ = 10;
}
