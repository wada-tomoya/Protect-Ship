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
	//mv1モデルcsv読み込み
	mv1model_csv_ = tnl::LoadCsv("csv/Resource_csv/mv1model.csv");
	//パーティクルcsv読み込み
	ptcl_csv_ = tnl::LoadCsv("csv/Resource_csv/ptcl.csv");
}

ResourceManager::~ResourceManager() {
	graphics_csv_.clear();
	graphics_map_.clear();
	animation_csv_.clear();
	animation_map_.clear();
	texture_csv_.clear();
	texture_map_.clear();
	sound_csv_.clear();
	sound_map_.clear();
	mv1model_csv_.clear();
	mv1model_map_.clear();
	ptcl_csv_.clear();
	ptcl_map_.clear();
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

int ResourceManager::LoadGraph_(const std::string& graph_name) {
	//mapからgraph_nameに対応する画像ハンドルをさがす
	auto it = graphics_map_.find(graph_name);

	//すでにロードしている場合、その画像ハンドルをかえす
	if (it != graphics_map_.end()) {
		return graphics_map_[graph_name];
	}

	//ロードしてない場合、画像読み込み
	for (int y = 0; y < graphics_csv_.size(); ++y) {
		//名前が一致する物を探す
		if (graphics_csv_[y][0].getString().c_str() == graph_name) {
			int gpc_hdl = LoadGraph(graphics_csv_[y][1].getString().c_str(), true);

			//mapに読み込んだ画像を保存
			graphics_map_.insert(std::make_pair(graph_name,gpc_hdl));

			//画像ハンドルを返す
			return gpc_hdl;
		}
	}
	//一致する物がなかった場合
	return 0;
}

std::shared_ptr<std::vector<int>> ResourceManager::LoadAnim_(const std::string& animation_name) {
	//animation_nameに対応するアニメーションハンドルを探す
	auto it = animation_map_.find(animation_name);

	//すでにロードしている場合、そのアニメーションハンドルをかえす
	if (it != animation_map_.end()) {
		return animation_map_[animation_name];
	}

	//ロードしていない場合、読み込み
	for (int y = 0; y < animation_csv_.size(); ++y) {
		//名前が一致する物を探す
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
	//名前が一致する物がない場合
	return nullptr;
}

Shared<dxe::Texture> ResourceManager::LoadTexture_(const std::string& texture_name) {
	auto it = texture_map_.find(texture_name);
	
	//すでにロードしている場合
	if (it != texture_map_.end()) {
		//読み込んでいる物を返す
		return texture_map_[texture_name];
	}

	//ロードしていない場合
	for (int y = 0; y < texture_csv_.size(); ++y) {
		//名前が一致する物を探す
		if (texture_csv_[y][0].getString().c_str() == texture_name) {
			
			Shared<dxe::Texture> texture_hdl
				= dxe::Texture::CreateFromFile(texture_csv_[y][1].getString().c_str());

			//ロードしたテクスチャをマップに保存
			texture_map_.insert(std::make_pair(texture_name, texture_hdl));

			//テクスチャハンドルをかえす
			return texture_hdl;
		}
	}
	//名前の一致する物がない場合
	return nullptr;
}

int ResourceManager::LoadSound_(const std::string& sound_name) {
	auto it = sound_map_.find(sound_name);

	//すでにロードしている場合
	if (it != sound_map_.end()) {
		//読み込んでいる物を返す
		return sound_map_[sound_name];
	}

	//ロードしていない場合
	for (int y = 0; y < sound_csv_.size(); ++y) {
		//名前が一致する物を探す
		if (sound_csv_[y][0].getString().c_str() == sound_name) {
			int sound = LoadSoundMem(sound_csv_[y][1].getString().c_str());

			//mapに読み込んだ音を保存
			sound_map_.insert(std::make_pair(sound_name, sound));

			//音を返す
			return sound;
		}
	}
	//名前の一致する物がない場合
	return -1;
}

int ResourceManager::LoadMV1Model_(const std::string& model_name) {
	auto it = mv1model_map_.find(model_name);

	//すでにロードしてmapに保存している場合
	if (it != mv1model_map_.end()) {
		//読み込んでいる物を返す
		return mv1model_map_[model_name];
	}

	//ロードしていない場合
	for (int y = 0; y < mv1model_csv_.size(); ++y) {
		//名前が一致する物を探す
		if (mv1model_csv_[y][MV1MODEL_CSV_ITEM::MODEL_NAME].getString().c_str() == model_name) {
			//モデルロード
			int model = MV1LoadModel(mv1model_csv_[y][MV1MODEL_CSV_ITEM::MODEL_FILE_PATH].getString().c_str());
			
			//mapに読み込んだモデルを保存
			mv1model_map_.insert(std::make_pair(model_name, model));

			//mv1モデルを返す
			return model;		
		}
	}
	//一致する名前がない場合
	return -1;
}

Shared<dxe::Particle> ResourceManager::LoadPtcl_(const std::string& ptcl_name){
	auto it = ptcl_map_.find(ptcl_name);
	//すでにロードしている場合
	if (it != ptcl_map_.end()) {
		return ptcl_map_[ptcl_name];
	}

	//ロードしてない場合
	for (int y = 0; y < ptcl_csv_.size(); ++y) {
		//名前が一致する物を探す
		if (ptcl_csv_[y][0].getString().c_str() == ptcl_name) {
			//パーティクル読み込み
			Shared<dxe::Particle> ptcl = std::make_shared<dxe::Particle>(ptcl_csv_[y][1].getString().c_str());

			//mapに保存
			ptcl_map_.insert(std::make_pair(ptcl_name, ptcl));

			return ptcl;
		}
	}

	return nullptr;
}
