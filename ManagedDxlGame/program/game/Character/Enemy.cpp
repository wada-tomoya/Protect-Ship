#include "Enemy.h"

Enemy::Enemy(tnl::Vector3 target, tnl::Vector3 spawn_pos, Shared<dxe::InstMesh> inst_mesh){
	//メッシュ
	inst_mesh_ = inst_mesh;
	
	//生成座標設定
	pos_ = spawn_pos;
	target_pos_ = target;
	//移動速度設定
	speed_ = 1.0f;	
	//半径設定
	rad_ = 16.0f;
	//移動方向計算
	move_dir_ = tnl::Vector3::Normalize(target_pos_ - pos_) * speed_;
	//初期座標設定
	inst_mesh_->setPosition(pos_);
}

void Enemy::Update(float delta_time, tnl::Vector3 player_pos) {
	//行動シーケンス実行
	tnl_sequence_.update(delta_time);
}

bool Enemy::move(const float delta_time) {
	//移動
	inst_mesh_->setPosition(inst_mesh_->getPosition() + move_dir_);

	//attackフラグがtrueになれば攻撃シーケンスに移動
	if (is_attack_) {
		tnl_sequence_.change(&Enemy::attack);
	}

	TNL_SEQ_CO_END
}

bool Enemy::attack(const float delta_time) {

	TNL_SEQ_CO_END
}
