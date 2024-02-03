#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "Camera.h"
#include "../Manager/ResourceManager.h"

class Block {
private:
	//ブロックのサイズ
	const float size_ = 48.0f;

	//ブロック画像ハンドル
	std::shared_ptr<std::vector<int>> mapchip_hdl_;
	//ブロック表示場所のcsvデータ
	std::vector<std::vector<int>> mapchip_csv_;

public:
	Block();
	//マップチップ表示
	void Draw(const Camera& camera);
};
