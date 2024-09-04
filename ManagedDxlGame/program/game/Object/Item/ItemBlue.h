#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include "ItemBase.h"

class Camera;

class ItemBlue : public ItemBase {
private:
	

public:
	ItemBlue() = default;

	//引数１：複製モデル
	ItemBlue(const int& mv1model);
	~ItemBlue();

	//実行関数
	//引数１：時間
	void Update(const float& delta_time)override;
};