#include "Sspawner.h"

Spawner::Spawner(tnl::Vector3 map_upleft, tnl::Vector3 map_lowright) {
	//マップ情報挿入
	map_upleft_ = map_upleft;
	map_lowright_ = map_lowright;
	//マップの大きさ計算
	map_x_length_ = map_upleft.x - map_lowright.x;
	map_y_length_ = map_upleft.y - map_lowright.y;
	//敵１のテクスチャ
	textures_.emplace_back(ResourceManager::GetInstance_ResourceManager()->LoadTexture_("ENEMY_1_RIGHT"));
	textures_.emplace_back(ResourceManager::GetInstance_ResourceManager()->LoadTexture_("ENEMY_1_LEFT"));
	//ENEMY_1複製元のメッシュ
	enemy1_.origine_mesh_ = dxe::Mesh::CreatePlaneMV(enemy1_.size_, 1, 1);
	enemy1_.origine_mesh_->dxe::Mesh::setBlendMode(DX_BLENDMODE_ALPHA);
	enemy1_.origine_mesh_->dxe::Mesh::setSampleFilterMode(DX_DRAWMODE_NEAREST);
	//ENEMY_1メッシュ複製
	enemy1_.mesh_pool_ = dxe::InstMeshPool::Create(enemy1_.origine_mesh_, enemy1_.instmax_, &textures_);
	//ブレンドモード設定
	enemy1_.mesh_pool_->dxe::InstMeshPool::setBlendState(dxe::eBlendState::ALPHA);
	//色設定
	enemy1_.mesh_pool_->dxe::InstMeshPool::setMtrlEmissive({ 1,1,1 });

	//ProtectObject敵の標的
	protectobject_ = std::make_shared<ProtectObject>();
}

Spawner::~Spawner() {
	//mesh_pool_の参照カウンタを0に
	enemy1_.mesh_pool_.reset();
}

Spawner* Spawner::Instance_Spawner(tnl::Vector3 map_upleft, tnl::Vector3 map_lowright) {
	static Spawner* instance(nullptr);
	if (!instance) {
		instance = new Spawner(map_upleft, map_lowright);
	}
	return instance;
}

void Spawner::Update(float delta_time) {
	//敵生成
	Enemy_Spawn(protectobject_->GetterPos(), delta_time);

	//敵の実行と消去
	auto it = enemys_.begin();
	while (it != enemys_.end())
	{
		//実行
		(*it)->Update(delta_time);
		//消去
		if (!(*it)->Getter_is_alive()) {
			it = enemys_.erase(it);
			continue;
		}
		it++;
	}
}

void Spawner::Enemy_Spawn(tnl::Vector3 target_pos, float delta_time) {
	time += delta_time;
	//0.5秒ごとに生成
	if (time > 0.5f) {
		//敵の生成座標
		tnl::Vector3 spawnpos{ 0,0,0 };
		int a = rand() % 4;
		//左端から生成
		if (a == 0) { spawnpos = { map_upleft_.x, (float)(rand() % 2561) - (1280) ,0 }; }
		//右端から生成
		else if (a == 1) { spawnpos = { map_lowright_.x, (float)(rand() % 2561) - (1280) , 0 }; }
		//上端から生成
		else if (a == 2) { spawnpos = { (float)(rand() % 1441) - (720),map_upleft_.y ,0 }; }
		//下端から生成
		else if (a == 3) { spawnpos = { (float)(rand() % 1441) - (720) ,map_lowright_.y,0 }; }
		//生成
		auto inst = enemy1_.mesh_pool_->CreateInstMesh();
		//listに挿入
		enemys_.emplace_back(std::make_shared<Enemy>(target_pos, spawnpos, inst));
		
		time = 0;
	}
	
}