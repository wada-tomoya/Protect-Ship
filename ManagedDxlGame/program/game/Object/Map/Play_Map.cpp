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
			blocks_.emplace_back(new Block(pos, (*mapchip_hdl_)[mapchip_csv_[y][x]]));
		}
	}
	
	//背景画像読み込み
	background_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("PlayScene_BackGround");
	//マップの端（右下）の座標計算
	map_lowright_ = { Block::size_ * (float)mapchip_csv_[0].size(), Block::size_ * (float)mapchip_csv_.size(), 0 };
	//地面の位置計算
	ground_ = (blocks_.front()->pos_.y + (Block::size_ / 2.0f));
}

Play_Map* Play_Map::GetInstance_PlayMap(){
	static Play_Map* instance(nullptr);
	if (!instance) {
		instance = new Play_Map();
	}
	return instance;
}

void Play_Map::Background_Draw(std::shared_ptr<Camera> camera) {
	//描画位置の調整
	tnl::Vector3 draw_pos = bg_pos_ - camera->pos_ + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
	//背景表示
	DrawExtendGraph(draw_pos.x, draw_pos.y, draw_pos.x + map_lowright_.x, draw_pos.y + ground_, background_hdl_, false);
}

void Play_Map::MapChip_Draw(std::shared_ptr<Camera> camera) {
	//マップチップ表示
	for (auto blk : blocks_) {
		//描画位置の調整
		tnl::Vector3 draw_pos = blk->pos_ - camera->pos_ + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
		DrawGraph(draw_pos.x, draw_pos.y, blk->graph_, true);
	}
	DrawStringEx(10,170,-1,"マップチップ表示");
}

tnl::Vector3 Play_Map::MapEdge_Getter(std::string s) {
	//マップの端の座標を返す
	if (s == "upleft") return map_upleft_;
	else if (s == "lowright") return map_lowright_;
}

float Play_Map::Groundpos_Getter() {
	//地面の座標を返す
	return ground_;
}