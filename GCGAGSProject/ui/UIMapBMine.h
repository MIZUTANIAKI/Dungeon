#pragma once
#include "UIBase.h"
class UIMapBMine :
    public UIBase
{
public:
	UIMapBMine();
	UIMapBMine(Vector2 pos, Vector2 size);
	~UIMapBMine();

	void Update(void)override;
	void SetDate(void)override;
	void Draw(void)override;
private:

	int subUi_;
	bool subUIDispF_;
	int mousecount_;
};

