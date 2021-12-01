#pragma once
#include "UIBase.h"
class UIMonsterMenu :
    public UIBase
{
public:
	UIMonsterMenu();
	UIMonsterMenu(Vector2 pos, Vector2 size);
	~UIMonsterMenu();

	void Update(void)override;
	void SetDate(void)override;
	void Draw(void)override;
private:
	Vector2 mouseSubpos_;

	int subUi_;
	bool subUIDispF_;
	bool grabF_;
	bool dropgrabF_;
	int mousecount_;
	int grabNum_;
};

