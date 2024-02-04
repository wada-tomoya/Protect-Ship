#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../Manager/ResourceManager.h"
#include "Block.h"

class Play_Map {
private:
	//マップチップ関係
	//ブロック表示場所のcsvデータ
	std::vector<std::vector<int>> mapchip_csv_;
	//マップチップのlist
	std::list<std::shared_ptr<Block>> blocks_;
	//ブロック画像ハンドル
	std::shared_ptr<std::vector<int>> mapchip_hdl_;

	//背景の画像ハンドル
	int background_hdl_ = 0;

public:
	Play_Map();
	void Background_Draw();
	void MapChip_Draw();
};
