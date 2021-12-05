#pragma once
#include "Explorer.h"
class Desmodus :
	public Explorer
{
public:
	Desmodus();
	~Desmodus() override;
	void Update(void)override;
	void Draw()override;
	void Init()override;
	void SetStatus(int num) override;
private:
	void Damage(Explorer& target)override;
};
