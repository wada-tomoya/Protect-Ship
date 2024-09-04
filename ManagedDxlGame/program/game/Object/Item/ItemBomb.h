#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include "ItemBase.h"

class Camera;

class ItemBomb : public ItemBase {
private:


public:
	ItemBomb() = default;

	//引数１：複製モデル
	ItemBomb(const int& mv1model);
	~ItemBomb();

	//実行関数
	//引数１：時間
	void Update(const float& delta_time)override;
};