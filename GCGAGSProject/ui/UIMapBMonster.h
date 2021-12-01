#pragma once
#include "UIBase.h"
class UIMapBMonster :
    public UIBase
{
public:
	UIMapBMonster();
	UIMapBMonster(Vector2 pos, Vector2 size);
	~UIMapBMonster();

	void Update(void)override;
	void SetDate(void)override;
	void Draw(void)override;
private:

	int subUi_;
	bool subUIDispF_;
	int mousecount_;
	int monsterUi_;
	bool monsterUiDispF_;
};

