#pragma once
#include "UIBase.h"

class UIGimmickMenu :
	public UIBase
{
public:
	UIGimmickMenu();
	UIGimmickMenu(Vector2 pos, Vector2 size);
	~UIGimmickMenu();

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

