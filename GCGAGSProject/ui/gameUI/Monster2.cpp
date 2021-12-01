#include "Monster2.h"
#include "ImageMng.h"


Monster2::Monster2()
{
	pos_ = { 0,0 };
	Init();
}

Monster2::Monster2(Vector2 pos)
{
	pos_ = pos;
	Init();
}

Monster2::~Monster2()
{
}

void Monster2::Update(void)
{
	DragMove();
	if (lpMapMng.GetDropEndF(id_) == true)
	{
		delF_ = true;
	}

}

void Monster2::Draw(void)
{
	lpImglMng.DrawImg("menu2.png", pos_);
	GrabDraw();
}

void Monster2::Init()
{
	delF_ = false;
	id_ = MapDropDateID::Desmodus;
	cost_ = 30;
}
