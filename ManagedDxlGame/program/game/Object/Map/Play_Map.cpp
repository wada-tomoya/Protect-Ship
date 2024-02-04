#include "Play_Map.h"

Play_Map::Play_Map() {
	//マップチップの画像
	mapchip_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadAnim_("MAPCHIP");
	//マップチップcsvデータ
	mapchip_csv_ = tnl::LoadCsv<int>("csv/map.csv");
	//マップチップlistに格納
	for (int y = 0; y < mapchip_csv_.size(); y++) {
		for (int x = 0; x < mapchip_csv_[0].size(); x++) {
			//csv内の数値が0以下なら次に飛ばす
			if (mapchip_csv_[y][x] <= 0) continue;
			//ブロックが持つ座標を計算
			tnl::Vector3 pos;
			pos.x = (x * Block::size_);
			pos.y = (y * Block::size_);
			//listに格納
			blocks_.emplace_back(new Block(pos));
		}
	}

	//背景画像読み込み
	background_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("PlayScene_BackGround");
}

void Play_Map::Background_Draw() {

}

void Play_Map::MapChip_Draw() {
	for () {

	}
	//DrawGraph(draw_pos_.x, draw_pos_.y, (*mapchip_hdl_)[mapchip_csv_[y][x]], true);
}