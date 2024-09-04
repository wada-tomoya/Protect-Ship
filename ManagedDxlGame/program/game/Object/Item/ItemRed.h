#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include "ItemBase.h"

class Camera;

class ItemRed : public ItemBase {
private:


public:
	ItemRed() = default;

	//引数１：複製モデル
	ItemRed(const int& mv1model);
	~ItemRed();

	//実行関数
	//引数１：時間
	void Update(const float& delta_time)override;
};
