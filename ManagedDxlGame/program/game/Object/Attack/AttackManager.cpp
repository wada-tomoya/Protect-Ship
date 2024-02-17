#include "AttackManager.h"

AttackManager::AttackManager() {
	//マップ
	map_ = std::make_shared<Play_Map>();
	//テクスチャ　ロード
	textures_.emplace_back(ResourceManager::GetInstance_ResourceManager()->LoadTexture_("NORMALATTACK_1"));
	//NormalAttack複製元メッシュ
	noratk.origine_mesh_ = dxe::Mesh::CreatePlaneMV(noratk.size_, 1, 1);
	//メッシュ複製
	noratk.mesh_pool_ = dxe::InstMeshPool::Create(noratk.origine_mesh_, noratk.instmax_, &textures_);
	//ブレンドモード設定
	noratk.mesh_pool_->dxe::InstMeshPool::setBlendState(dxe::eBlendState::ALPHA);
	//メッシュの色設定
	noratk.mesh_pool_->dxe::InstMeshPool::setMtrlEmissive({ 1,1,1 });
}

AttackManager::~AttackManager() {
	//mesh_pool_の参照カウンタを0に
	noratk.mesh_pool_.reset();
}

void AttackManager::Update(float delta_time) {
	//NormalAttackの実行と消去
	auto it = noratk.normalattacks_.begin();
	while (it != noratk.normalattacks_.end()) {
		//実行
		(*it)->Update(delta_time);
		//消去 normalattackのis_aliveがfalseになれば消去
		if (!(*it)->Getter_is_alive()) {
			it = noratk.normalattacks_.erase(it);
			continue;
		}
		it++;
	}
}

void AttackManager::NormalAttack_Create(tnl::Vector3 spwan_pos, tnl::Vector3 target_pos) {
	//複製メッシュ生成
	auto inst = noratk.mesh_pool_->CreateInstMesh();
	//テクスチャ設定
	inst->setUseTextureIndex(0);
	//listに挿入
	noratk.normalattacks_.emplace_back(std::make_shared<NormalAttack>(map_->MapEdge_Getter("upleft"),map_->MapEdge_Getter("lowright"),
		spwan_pos, target_pos, inst));
}