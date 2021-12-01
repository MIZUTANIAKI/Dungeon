#pragma once
#include "ScrollUIBase.h"
class Gimmick2 :
    public ScrollUIBase
{
public:
	Gimmick2();
	Gimmick2(Vector2 pos);
	~Gimmick2();

	void Update(void) override;
	void Draw(void) override;
private:
	void Init()  override;
};

