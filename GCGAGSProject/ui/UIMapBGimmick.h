#pragma once
#include "UIBase.h"
class UIMapBGimmick :
    public UIBase
{
public:
	UIMapBGimmick();
	UIMapBGimmick(Vector2 pos, Vector2 size);
	~UIMapBGimmick();

	void Update(void)override;
	void SetDate(void)override;
	void Draw(void)override;
private:

	int subUi_;
	bool subUIDispF_;
	int mousecount_;

	int gimmickUi_;
	bool gimmickUiDispF_;
};

