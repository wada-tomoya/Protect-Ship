#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include "ItemBase.h"

class Camera;

class ItemBomb : public ItemBase {
private:


public:
	ItemBomb(int& mv1model);
	~ItemBomb();

	//é¿çsä÷êî
	void Update(float delta_time)override;
};