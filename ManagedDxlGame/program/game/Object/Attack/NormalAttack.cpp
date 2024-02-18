#include "NormalAttack.h"

NormalAttack::NormalAttack(const tnl::Vector3 map_upleft, const tnl::Vector3 map_lowright, 
	const tnl::Vector3& spwan_pos, const tnl::Vector3 target_pos, Shared<dxe::InstMesh> inst_mesh) {
	//引数の値を挿入
	//複製されたメッシュ
	inst_mesh_ = inst_mesh;
	//初期座標
	spawn_pos_.x = spwan_pos.x;
	spawn_pos_.y = -spwan_pos.y;
	//進行方向の座標x y
	target_posx_ = target_pos.x;
	target_posy_ = target_pos.y;
	//画面の端の座標
	upleft_ = map_upleft;
	lowright_ = map_lowright;
	//弾の速度設定
	speed_ = 15.0f;
	//当たり判定用半径設定
	rad_ = 8.0f;

	//角度計算
	int x = target_posx_ - 0;
	int y = target_posy_ - 0;
	angle_ = atan2(y,x);

	//初期座標設定
	inst_mesh_->setPosition({ spawn_pos_.x, spawn_pos_.y, spawn_pos_.z });
}

void NormalAttack::Update(float delta_time) {
	//移動量計算
	tnl::Vector3 move;
	move.x = cos(angle_) * speed_;
	move.y = sin(angle_) * speed_;
	//弾移動
	inst_mesh_->setPosition(inst_mesh_->getPosition() + move);
	//弾回転
	inst_mesh_->setRotation(inst_mesh_->getRotation() * tnl::Quaternion::RotationAxis({ 0,0,1 }, tnl::ToRadian(10)));
	
	//マップ外に行けば弾は消える
	tnl::Vector3 nowpos = inst_mesh_->getPosition();
	if (nowpos.x < upleft_.x || nowpos.y < upleft_.y || nowpos.x > lowright_.x || nowpos.y > lowright_.y) {
		Delete();
	}
}

void NormalAttack::Delete() {
	is_alive_ = false;

	//falseになると消える処理はAttackManagerに書いてある
}
