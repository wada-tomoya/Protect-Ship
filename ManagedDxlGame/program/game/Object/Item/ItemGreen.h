#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include "ItemBase.h"

class Camera;

class ItemGreen : public ItemBase {
private:
	

public:
	ItemGreen() = default;

	//引数１：複製モデル
	ItemGreen(const int& mv1model);
	~ItemGreen();

	//実行関数
	//引数１：時間
	void Update(const float& delta_time)override;
};
