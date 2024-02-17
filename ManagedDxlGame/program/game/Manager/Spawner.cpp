#include "Sspawner.h"

Spawner::Spawner(tnl::Vector3 map_upleft, tnl::Vector3 map_lowright) {
	//マップ情報挿入
	map_upleft_ = map_upleft;
	map_lowright_ = map_lowright;

	textures_.emplace_back(ResourceManager::GetInstance_ResourceManager()->LoadTexture_("ENEMY_1_RIGHT"));
	textures_.emplace_back(ResourceManager::GetInstance_ResourceManager()->LoadTexture_("ENEMY_1_LEFT"));
	//ENEMY_1複製元のメッシュ
	enemy1_.origine_mesh_ = dxe::Mesh::CreatePlaneMV(enemy1_.size_, 1, 1);
	//ENEMY_1メッシュ複製
	enemy1_.mesh_pool_ = dxe::InstMeshPool::Create(enemy1_.origine_mesh_, enemy1_.instmax_, &textures_);
	//ブレンドモード設定
	enemy1_.mesh_pool_->dxe::InstMeshPool::setBlendState(dxe::eBlendState::ALPHA);
	//色設定
	enemy1_.mesh_pool_->dxe::InstMeshPool::setMtrlEmissive({ 1,1,1 });

	//ProtectObject敵の標的
	protectobject_ = std::make_shared<ProtectObject>();

	//-----------------------------------------------------------
	auto inst = enemy1_.mesh_pool_->CreateInstMesh();
	//テクスチャ設定
	inst->setUseTextureIndex(0);
	//listに挿入
	enemys_.emplace_back(std::make_shared<Enemy>(protectobject_->GetterPos(), map_upleft_, inst));
}

Spawner::~Spawner() {
	//mesh_pool_の参照カウンタを0に
	enemy1_.mesh_pool_.reset();
}

void Spawner::Update(float delta_time) {
	//Enemy_Spawn(protectobject_->GetterPos(), tnl::Vector3{30,30,0}, delta_time);
	
	//敵１の実行と消去
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

	int aaa = enemys_.size();
	DrawStringEx(10,10,-1,"敵数　%d", aaa);
}

void Spawner::Enemy_Spawn(tnl::Vector3 target_pos, tnl::Vector3 spawn_pos, float delta_time) {
	time += delta_time;

	//2秒ごとに生成
	if (time > 2.0f) {
		//生成
		auto inst = enemy1_.mesh_pool_->CreateInstMesh();
		//listに挿入
		enemys_.emplace_back(std::make_shared<Enemy>(target_pos, spawn_pos, inst));
		
		time = 0;
	}
	
}