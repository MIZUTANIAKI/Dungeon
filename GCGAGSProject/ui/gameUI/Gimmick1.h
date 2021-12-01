#pragma once
#include "ScrollUIBase.h"
class Gimmick1 :
    public ScrollUIBase
{
public:
	Gimmick1();
	Gimmick1(Vector2 pos);
	~Gimmick1();

	void Update(void) override;
	void Draw(void) override;
private:
	void Init()  override;
};

