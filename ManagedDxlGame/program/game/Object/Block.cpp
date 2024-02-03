#include "Block.h"

Block::Block(){
	//マップチップの画像
	mapchip_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadAnim_("MAPCHIP");
	mapchip_csv_ = tnl::LoadCsv<int>("csv/map.csv");
}

void Block::Draw(const Camera& camera) {
	//マップチップ表示
	for (int y = 0; y < mapchip_csv_.size(); y++) {
		for (int x = 0; x < mapchip_csv_[0].size(); x++) {
			if (mapchip_csv_[y][x] <= 0) continue;
			tnl::Vector3 draw_pos_ = tnl::Vector3(x * size_, y * size_, 0.0f) 
				- camera.target_ + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
			DrawGraph(draw_pos_.x, draw_pos_.y, (*mapchip_hdl_)[mapchip_csv_[y][x]], true);
		}
	}
}