#include "AttackManager.h"

AttackManager::AttackManager() {
	//マップ
	map_ = std::make_shared<Play_Map>();
	//テクスチャ　ロード
	textures_.emplace_back(ResourceManager::GetInstance_ResourceManager()->LoadTexture_("NORMALATTACK_1"));
	//NormalAttack複製元メッシュ
	noratk_.origine_mesh_ = dxe::Mesh::CreatePlaneMV(noratk_.size_, 1, 1);
	//メッシュ複製
	noratk_.mesh_pool_ = dxe::InstMeshPool::Create(noratk_.origine_mesh_, noratk_.instmax_, &textures_);
	//ブレンドモード設定
	noratk_.mesh_pool_->dxe::InstMeshPool::setBlendState(dxe::eBlendState::ALPHA);
	//メッシュの色設定
	noratk_.mesh_pool_->dxe::InstMeshPool::setMtrlEmissive({ 1,1,1 });
}

AttackManager::~AttackManager() {
	//mesh_pool_の参照カウンタを0に
	noratk_.mesh_pool_.reset();
}

AttackManager* AttackManager::Instance_AttackManager() {
	static AttackManager* instance(nullptr);
	if (!instance) {
		instance = new AttackManager();
	}
	return instance;
}

void AttackManager::Update(float delta_time) {
	//NormalAttackの実行と消去
	auto it = attacks_.begin();
	while (it != attacks_.end()) {
		//実行
		(*it)->Update(delta_time);
		//消去 normalattackのis_aliveがfalseになれば消去
		if (!(*it)->Getter_is_alive()) {
			it = attacks_.erase(it);
			continue;
		}
		it++;
	}
}

void AttackManager::NormalAttack_Create(tnl::Vector3 spwan_pos, tnl::Vector3 target_pos) {
	//複製メッシュ生成
	auto inst = noratk_.mesh_pool_->CreateInstMesh();
	//テクスチャ設定
	inst->setUseTextureIndex(0);
	//listに挿入
	attacks_.emplace_back(std::make_shared<NormalAttack>(map_->MapEdge_Getter("upleft"),map_->MapEdge_Getter("lowright"),
		spwan_pos, target_pos, inst));
}