#include "NormalAttack.h"

NormalAttack::NormalAttack(const tnl::Vector3& spawn_pos, const int& mouse_pos_x, const int& mouse_pos_y, const float& speed) {
	//画像ロード
	graph_hdl_ = LoadGraph("graphics/Attack/bullet.bmp");

	//引数で受け取った値を変数に入れる
	spawn_pos_ = spawn_pos;
	target_pos_x_ = mouse_pos_x;
	target_pos_y_ = mouse_pos_y;
	speed_ = speed;

	//角度計算
	int x = target_pos_x_ - spawn_pos_.x;
	int y = target_pos_y_ - spawn_pos_.y;
	angle_ = atan2(y,x);
}

void NormalAttack::Update(float delta_time) {
	//弾移動
	spawn_pos_.x += cos(angle_) * speed_;
	spawn_pos_.y += sin(angle_) * speed_;
}

void NormalAttack::Delete() {
	is_alive_ = false;
}

void NormalAttack::Draw(float delta_time) {
	DrawGraph(spawn_pos_.x, spawn_pos_.y, graph_hdl_, true);
}
