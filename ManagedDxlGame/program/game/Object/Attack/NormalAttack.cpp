#include "NormalAttack.h"

NormalAttack::NormalAttack(const tnl::Vector3 map_center, const float map_rad,const tnl::Vector3& spwan_pos,
	const tnl::Quaternion dir_angle, Shared<dxe::InstMesh> inst_mesh, float bullet_rad, 
	std::shared_ptr<dxe::Particle> hit_ptcl, std::shared_ptr<dxe::Particle> move_ptcl,
	float speed, float power, int penetration) {
	//複製されたメッシュ
	inst_mesh_ = inst_mesh;
	//進行方向の角度
	dir_rad_ = dir_angle;
	//プレイエリアの中心
	map_center_ = map_center;
	//プレイエリアの半径
	map_rad_ = map_rad;	
	//マップの中心から外周までのベクトル
	map_vec_ = static_cast<float>(std::pow(map_rad, 2));
	//弾の速度設定
	speed_ = 15.0f + speed;
	//弾の半径設定
	bullet_rad_ = bullet_rad;
	//初期座標設定
	inst_mesh_->setPosition(spwan_pos);
	//攻撃力設定
	attack_power_ = 10.0f + power;
	//貫通力セット
	penetration_ += penetration;

	//敵と当たった時のパーティクル設定
	hit_ptcl_ = hit_ptcl;
	//生成時間設定
	hit_ptcl_time_ = hit_ptcl_->getTimeLimit();
	//移動時のパーティクル
	move_ptcl_ = move_ptcl;
	//生成範囲設定
	move_ptcl_->setOriginRange(bullet_rad_);


}

NormalAttack::~NormalAttack(){
	hit_ptcl_.reset();
	move_ptcl_.reset();
}

void NormalAttack::Update(float delta_time) {
	//シーケンス実行
	tnl_sequence_.update(delta_time);
}

void NormalAttack::Enemy_Hit(){
	
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
	//貫通力が０になれば
	if (penetration_ <= 0) {
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
