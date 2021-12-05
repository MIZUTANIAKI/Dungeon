#pragma once
#include "Explorer.h"
class Rook :
    public Explorer
{
public:
	Rook();
	~Rook() override;
	void Update(void)override;
	void Draw()override;
	void Init()override;
	void SetStatus(int num) override;
private:
	void Damage(Explorer& target)override;
};

