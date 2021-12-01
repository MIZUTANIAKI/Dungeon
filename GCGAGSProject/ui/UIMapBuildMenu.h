#pragma once
#include "UIBase.h"
class UIMapBuildMenu :
    public UIBase
{
public:
	UIMapBuildMenu();
	UIMapBuildMenu(Vector2 pos, Vector2 size);
	~UIMapBuildMenu();

	void Update(void)override;
	void SetDate(void)override;
	void Draw(void)override;
private:
	int mine_;
	int gimmick_;
	int monster_;
};

