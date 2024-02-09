#include "AttackManager.h"

AttackManager::AttackManager() {
	//テクスチャ　ロード
	noratk.textures_.emplace_back(ResourceManager::GetInstance_ResourceManager()->LoadTexture_("NORMALATTACK_1"));
	//NormalAttack複製元メッシュ
	noratk.origine_mesh_ = dxe::Mesh::CreatePlaneMV(noratk.size_, 1, 1);
	//メッシュ複製
	noratk.mesh_pool_ = dxe::InstMeshPool::Create(noratk.origine_mesh_, noratk.instmax_, &noratk.textures_);
	noratk.mesh_pool_->dxe::InstMeshPool::setBlendState(dxe::eBlendState::ALPHA);
	noratk.mesh_pool_->dxe::InstMeshPool::setMtrlEmissive({1,1,1});
}

AttackManager::~AttackManager() {
	noratk.mesh_pool_.reset();
}

void AttackManager::Update(float delta_time) {
	//NormalAttackの実行と消去
	auto it = noratk.normalattacks_.begin();
	while (it != noratk.normalattacks_.end()) {
		//実行
		(*it)->Update(delta_time);
		//消去
		if (!(*it)->Getter_is_alive()) {
			it = noratk.normalattacks_.erase(it);
			continue;
		}
		it++;
	}
}

void AttackManager::Draw(float delta_time, std::shared_ptr<Camera> camera) {
	dxe::DirectXRenderBegin();
	//NormalAttackの表示
	noratk.mesh_pool_->render(camera);
	
	dxe::DirectXRenderEnd();
}

void AttackManager::NormalAttack_Create(tnl::Vector3 spwan_pos, int target_pos_x, int target_pos_y) {
	//複製メッシュ生成
	auto inst = noratk.mesh_pool_->CreateInstMesh();
	//座標設定
	inst->setPosition(spwan_pos);
	//テクスチャ設定
	inst->setUseTextureIndex(0);
	//listに挿入
	noratk.normalattacks_.emplace_back(std::make_shared<NormalAttack>(spwan_pos, target_pos_x, target_pos_y, inst));
}