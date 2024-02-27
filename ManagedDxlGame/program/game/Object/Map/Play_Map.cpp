 #include "Play_Map.h"

Play_Map::Play_Map() {	
	//マップの端（左上、右下）の座標
	map_upleft_ = { -DXE_WINDOW_WIDTH, -DXE_WINDOW_HEIGHT, 0 };
	map_lowright_ = { DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, 0 };
	//プレイヤーの移動限界座標
	player_upleft_ = { map_upleft_.x / 2, map_upleft_.y / 2, 0 };
	player_lowright_ = { map_lowright_.x / 2, map_lowright_.y / 2,0 };

	//背景画像読み込み
	texture_.emplace_back(ResourceManager::GetInstance_ResourceManager()->LoadTexture_("PlayScene_BackGround"));
	//メッシュ生成
	mesh_ = dxe::Mesh::CreatePlaneMV({ DXE_WINDOW_WIDTH * 2, DXE_WINDOW_HEIGHT * 2, 0 },1,1);
	//インスタンスメッシュ複製
	mesh_pool_ = dxe::InstMeshPool::Create(mesh_, 1, &texture_);
	//ブレンドモード設定
	//mesh_pool_->dxe::InstMeshPool::setBlendState(dxe::eBlendState::ALPHA);
	//メッシュの色設定
	mesh_pool_->dxe::InstMeshPool::setMtrlEmissive({ 1,1,1 });
	//インスタンスメッシュ生成、座標設定、テクスチャ設定
	auto inst = mesh_pool_->CreateInstMesh();
	inst->setPosition({ 0, 0, 0 });
	inst->setUseTextureIndex(0);
	inst_meshs_.emplace_back(inst);
}

Play_Map::~Play_Map() {
	//mesh_pool_の参照カウンタを0に
	mesh_pool_.reset();
}

const tnl::Vector3& Play_Map::MapEdge_Getter(std::string s) const {
	//マップの端の座標を返す
	if (s == "upleft") return map_upleft_;
	else if (s == "lowright") return map_lowright_;
}

const tnl::Vector3& Play_Map::MapEdgePlsyer_Getter(std::string s) const {
	//マップの端の座標を返す
	if (s == "upleft") return player_upleft_;
	else if (s == "lowright") return player_lowright_;
}
