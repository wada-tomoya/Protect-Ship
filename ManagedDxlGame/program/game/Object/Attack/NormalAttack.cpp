#include "NormalAttack.h"
#include "math.h"

NormalAttack::NormalAttack(const tnl::Vector3& map_center, const float& map_rad, const tnl::Vector3& spawn_pos,
	const tnl::Quaternion& dir_angle, const std::shared_ptr<dxe::InstMesh>& inst_mesh, const float& bullet_rad,
	const std::shared_ptr<dxe::Particle>& hit_ptcl, const std::shared_ptr<dxe::Particle>& move_ptcl,
	const float& speed, const float& power, const int& penetration) :
	AttackBase(inst_mesh, hit_ptcl, move_ptcl, dir_angle, map_center, map_rad, bullet_rad, spawn_pos) {
	
	//攻撃力設定
	attack_power_ = 10.0f + power;
	//攻撃力を1未満にしない
	if (attack_power_ <= 1.0f) {
		attack_power_ = 1.0f;
	}
	//弾の速度設定
	speed_ = 15.0f + speed;
	//貫通力セット
	penetration_ = penetration;

	//ノックバック値設定
	knockback_value_ = 1.0f;
}

NormalAttack::~NormalAttack(){

}

void NormalAttack::Update(const float& delta_time) {
	//シーケンス実行
	tnl_sequence_.update(delta_time);
}

void NormalAttack::Enemy_Hit(EnemyBase* hiteneaddress){
	//当たった敵のアドレスを保存
	hiteneaddress_.emplace_back(hiteneaddress);

	//ヒット時のパーティクル生成
	is_hit_ptcl_ = true;
	hit_ptcl_->setPosition(Getter_pos());
	hit_ptcl_->start();

	//貫通力減少
	penetration_--;
}

bool NormalAttack::SEQ_Move(const float delta_time){
	//弾移動
	inst_mesh_->setPosition(inst_mesh_->getPosition() + tnl::Vector3::TransformCoord({ 0,speed_,0 }, dir_rad_));

	//回転
	inst_mesh_->setRotation(inst_mesh_->getRotation() * tnl::Quaternion::RotationAxis({ 1,0,0 }, tnl::ToRadian(rotate_angle_)));
	inst_mesh_->setRotation(inst_mesh_->getRotation() * tnl::Quaternion::RotationAxis({ 0,1,0 }, tnl::ToRadian(rotate_angle_ / 2)));

	//弾からプレイエリアの中心のベクトル
	float vec = MapCenter_Vec();

	//移動パーティクルの座標設定
	move_ptcl_->setPosition(inst_mesh_->getPosition());

	//シーケンス移動条件
	//貫通力が0未満になれば
	if (penetration_ < 0) {
		//移動時のパーティクル終了
		move_ptcl_->stop();

		tnl_sequence_.change(&NormalAttack::SEQ_Hit);
	}
	//マップ外に出た時
	else if (vec >= map_vec_) {
		//移動時のパーティクル終了
		move_ptcl_->stop();

		tnl_sequence_.change(&NormalAttack::SEQ_Death);
	}

	TNL_SEQ_CO_END
}

bool NormalAttack::SEQ_Hit(const float delta_time){
	//当たり判定消去
	is_collision_ = false;

	//描画しないよう設定
	inst_mesh_->setDrawEnable(false);

	//パーティクル生成時間
	hit_ptcl_count_ += delta_time;
	//シーケンス移動条件
	//hit_ptcl_の生成時間経過したら弾消去
	if (hit_ptcl_count_ >= hit_ptcl_time_) {
		tnl_sequence_.change(&NormalAttack::SEQ_Death);
	}

	TNL_SEQ_CO_END
}

bool NormalAttack::SEQ_Death(const float delta_time){
	//攻撃消去
	Delete();

	TNL_SEQ_CO_END
}
