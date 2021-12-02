#include "Gimmick1.h"
#include "ImageMng.h"
#include "MouseMng.h"

Gimmick1::Gimmick1()
{
	pos_ = { 0,0 };
	Init();
}

Gimmick1::Gimmick1(Vector2 pos)
{
	pos_ = pos;
	Init();
}

Gimmick1::~Gimmick1()
{
}

void Gimmick1::Update(void)
{
	DragMove();
	DeleteUi();
}

void Gimmick1::Draw(void)
{
	lpImglMng.DrawImg("menu3.png", pos_);
	GrabDraw();
}

void Gimmick1::Init()
{
	delF_ = false;
	id_ = MapDropDateID::Spike;
	cost_ = 50;
}
