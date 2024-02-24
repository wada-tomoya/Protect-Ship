#include "ResourceManager.h"

ResourceManager::ResourceManager() {
	//画像csv読み込み
	graphics_csv_ = tnl::LoadCsv("csv/Resource_csv/graph.csv");
	//アニメーションcsv読み込み
	animation_csv_ = tnl::LoadCsv("csv/Resource_csv/animation.csv");
	//テクスチャcsv読み込み
	texture_csv_ = tnl::LoadCsv("csv/Resource_csv/texture.csv");
	//音csv読み込み
	sound_csv_ = tnl::LoadCsv("csv/Resource_csv/sound.csv");
}

void ResourceManager::Destroy() {
	delete GetInstance_ResourceManager();
}

ResourceManager* ResourceManager::GetInstance_ResourceManager() {
	static ResourceManager* instance(nullptr);
	if (!instance) {
		instance = new ResourceManager();
	}
	return instance;
}

int ResourceManager::LoadGraph_(std::string graph_name) {
	//mapからgraph_nameに対応する画像ハンドルをさがす
	auto it = graphics_map_.find(graph_name);

	//すでにロードしている場合、その画像ハンドルをかえす
	if (it != graphics_map_.end()) {
		return graphics_map_[graph_name];
	}

	//ロードしてない場合、画像読み込み
	for (int y = 1; y < graphics_csv_.size(); ++y) {
		if (graphics_csv_[y][0].getString().c_str() == graph_name) {
			int gpc_hdl = LoadGraph(graphics_csv_[y][1].getString().c_str(), true);

			//mapに読み込んだ画像を保存
			graphics_map_.insert(std::make_pair(graph_name,gpc_hdl));

			//画像ハンドルを返す
			return gpc_hdl;
		}
	}

	//読み込み出来なかった場合-1を返す
	return -1;
}

void ResourceManager::DeleteGraph_(std::string graph_name) {
	// file_pathに対応する画像ハンドルを探す
	auto it = graphics_map_.find(graph_name);

	// 画像ハンドルを解放
	DeleteGraph(it->second);

	// file_pathの画像パスを削除する
	if (it != graphics_map_.end()) {
		graphics_map_.erase(graph_name);
	}
}

std::shared_ptr<std::vector<int>> ResourceManager::LoadAnim_(std::string animation_name) {
	//animation_nameに対応するアニメーションハンドルを探す
	auto it = animation_map_.find(animation_name);

	//すでにロードしている場合、そのアニメーションハンドルをかえす
	if (it != animation_map_.end()) {
		return animation_map_[animation_name];
	}

	//ロードしていない場合、読み込み
	for (int y = 1; y < animation_csv_.size(); ++y) {
		if (animation_csv_[y][0].getString().c_str() == animation_name) {

			std::shared_ptr<std::vector<int>> anim_hdl_ 
				= std::make_shared<std::vector<int>>(animation_csv_[y][ANIMATION_CSV_ITEM::TOTAL_DIV_NUM].getInt());

			//anim_hdl_にcsvから読み取ったデータを入れる
			LoadDivGraph(animation_csv_[y][ANIMATION_CSV_ITEM::PATH].getString().c_str(),
				(int)animation_csv_[y][ANIMATION_CSV_ITEM::TOTAL_DIV_NUM].getInt(),
				(int)animation_csv_[y][ANIMATION_CSV_ITEM::X_DIV_NUM].getInt(),
				(int)animation_csv_[y][ANIMATION_CSV_ITEM::Y_DIV_NUM].getInt(),
				(int)animation_csv_[y][ANIMATION_CSV_ITEM::X_SIZE].getInt(),
				(int)animation_csv_[y][ANIMATION_CSV_ITEM::Y_SIZE].getInt(),
				anim_hdl_->data());

			//animation_map_に保存
			animation_map_.insert(std::make_pair(animation_name, anim_hdl_));

			//アニメーションハンドルをかえす
			return anim_hdl_;
		}
	}
}

Shared<dxe::Texture> ResourceManager::LoadTexture_(std::string texture_name) {
	auto it = texture_map_.find(texture_name);
	
	//すでにロードしている場合
	if (it != texture_map_.end()) {
		return texture_map_[texture_name];
	}

	//ロードしていない場合
	for (int y = 0; y < texture_csv_.size(); ++y) {
		if (texture_csv_[y][0].getString().c_str() == texture_name) {
			
			Shared<dxe::Texture> texture_hdl
				= dxe::Texture::CreateFromFile(texture_csv_[y][1].getString().c_str());

			//ロードしたテクスチャをマップに保存
			texture_map_.insert(std::make_pair(texture_name, texture_hdl));

			//テクスチャハンドルをかえす
			return texture_hdl;
		}
	}
}

int ResourceManager::LoadSound_(std::string sound_name) {
	auto it = sound_map_.find(sound_name);

	//すでにロードしている場合
	if (it != sound_map_.end()) {
		return sound_map_[sound_name];
	}

	//ロードしていない場合
	for (int y = 0; sound_csv_.size(); ++y) {
		if (sound_csv_[y][0].getString().c_str() == sound_name) {
			int sound = LoadSoundMem(graphics_csv_[y][1].getString().c_str());

			//mapに読み込んだ音を保存
			sound_map_.insert(std::make_pair(sound_name, sound));

			//音を返す
			return sound;
		}
	}

	return -1;
}
