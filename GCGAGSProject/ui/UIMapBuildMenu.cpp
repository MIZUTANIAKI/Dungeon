#include <DxLib.h>
#include "UIMapBuildMenu.h"
#include "ImageMng.h"
#include "UISubTest.h"
#include "ReadMng.h"
#include "UIMng.h"
#include "UIMapBMine.h"
#include "UIMapBGimmick.h"
#include "UIMapBMonster.h"

UIMapBuildMenu::UIMapBuildMenu()
{
	//SetDate();
	gimmick_ = -1;
	mine_ = -1;
	monster_ = -1;

}

UIMapBuildMenu::UIMapBuildMenu(Vector2 pos, Vector2 size) :UIBase(pos, size)
{

	Vector2 tpos = { 15,25 };
	Vector2 tsize = { 100,100 };
	mine_ = lpUIMng.CreateUI(std::make_unique<UIMapBMine>(tpos, tsize),true);
	tpos.y += 125;
	monster_ = lpUIMng.CreateUI(std::make_unique<UIMapBMonster>(tpos, tsize), true);
	tpos.y += 125;
	gimmick_ = lpUIMng.CreateUI(std::make_unique<UIMapBGimmick>(std::move(tpos), std::move(tsize)), true);
}

UIMapBuildMenu::~UIMapBuildMenu()
{
}

void UIMapBuildMenu::Update(void)
{
}

void UIMapBuildMenu::SetDate(void)
{
}

void UIMapBuildMenu::Draw(void)
{
}
