#include "AttackManager.h"
#include "../Object/Camera.h"
#include "../Character/CharacterBase.h"

void AttackManager::Attack_Update( const float& delta_time, std::list<std::shared_ptr<AttackBase>>& attacks) {
	//NormalAttackの実行と消去
	auto it = attacks.begin();
	while (it != attacks.end()) {
		//実行
		(*it)->Update(delta_time);
		
		//消去 攻撃のis_aliveがfalseになれば消去
		if (!(*it)->Getter_is_alive()) {
			it = attacks.erase(it);
			continue;
		}

		it++;
	}
}

void AttackManager::Attack_Draw(const std::shared_ptr<Camera>& camera, const std::list<std::shared_ptr<AttackBase>>& attacks, const ATTACK& normalatk) {
	dxe::DirectXRenderBegin();

	//パーティクル描画
	auto it = attacks.begin();
	while (it != attacks.end()) {
		(*it)->Draw_Ptcl(camera);
		it++;
	}

	//NormalAttackの描画
	normalatk.mesh_pool_->render(camera);

	dxe::DirectXRenderEnd();

	////当たり判定表示
	//auto aa = attacks_.begin();
	//while (aa != attacks_.end()) {
	//	
	//	DrawSphere3D(VGet((*aa)->Getter_pos().x, (*aa)->Getter_pos().y, (*aa)->Getter_pos().z), (*aa)->Getter_bullet_rad(),
	//		8, GetColor(255, 0, 0), GetColor(255, 255, 255), false);

	//	aa++;
	//}
}

void AttackManager::NormalAttack_Create(const tnl::Vector3& spawn_pos, const tnl::Quaternion& dir_angle, const float& speed, const float& power, const int& Penetration,
	std::list<std::shared_ptr<AttackBase>>& attacks, const ATTACK& normalatk, const tnl::Vector3& atk_map_center, const float& atk_map_rad, const int& texturenum, const float& size_scale) {
	//複製メッシュ生成
	auto inst = normalatk.mesh_pool_->CreateInstMesh();

	//サイズ変更
	inst->setScale({ size_scale,size_scale,size_scale });

	//テクスチャ設定
	inst->setUseTextureIndex(texturenum);
	//パーティクルクローン作製
	Shared<dxe::Particle> clone_hit_ptcl = normalatk.hit_ptcl_->createClone();
	Shared<dxe::Particle> clone_move_ptcl = normalatk.move_ptcl_->createClone();

	//listに挿入
	attacks.emplace_back(std::make_shared<NormalAttack>(atk_map_center, atk_map_rad, spawn_pos, dir_angle, inst, normalatk.size_,
		clone_hit_ptcl, clone_move_ptcl, speed, power, Penetration));
}

void AttackManager::BombAttack_Create(const tnl::Vector3& spawn_pos, const tnl::Quaternion& dir_angle, const tnl::Vector3& target_pos,
	std::list<std::shared_ptr<AttackBase>>& attacks, const ATTACK& bombatk, const tnl::Vector3& atk_map_center, const float& atk_map_rad, const int& texturenum){
	//複製メッシュ生成
	auto inst = bombatk.mesh_pool_->CreateInstMesh();
	//テクスチャ設定
	inst->setUseTextureIndex(texturenum);
	//パーティクル
	Shared<dxe::Particle> clone_hit_ptcl = bombatk.hit_ptcl_->createClone();
	Shared<dxe::Particle> clone_move_ptcl = bombatk.move_ptcl_->createClone();

	//listに挿入
	attacks.emplace_back(std::make_shared<BombAttack>(atk_map_center, atk_map_rad, target_pos, spawn_pos, dir_angle, inst, bombatk.size_,
		clone_hit_ptcl, clone_move_ptcl, bombatk.hit_se_hdl_));
}
