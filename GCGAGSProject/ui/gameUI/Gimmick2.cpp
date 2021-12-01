#include "Gimmick2.h"
#include "ImageMng.h"

Gimmick2::Gimmick2()
{
	pos_ = { 0,0 };
	Init();
}

Gimmick2::Gimmick2(Vector2 pos)
{
	pos_ = pos;
	Init();
}

Gimmick2::~Gimmick2()
{
}

void Gimmick2::Update(void)
{
	DragMove();
	if (lpMapMng.GetDropEndF(id_) == true)
	{
		delF_ = true;
	}

}

void Gimmick2::Draw(void)
{
	lpImglMng.DrawImg("menu4.png", pos_);
	GrabDraw();
}

void Gimmick2::Init()
{
	delF_ = false;
	id_ = MapDropDateID::Gate;
	cost_ = 60;
}
