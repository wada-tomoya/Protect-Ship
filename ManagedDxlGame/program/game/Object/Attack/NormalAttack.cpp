#include "NormalAttack.h"

NormalAttack::NormalAttack(const tnl::Vector3& spawn_pos, const int& target_pos_x, const int& target_pos_y, 
	Shared<dxe::InstMesh> inst_mesh) {
	//引数の値を挿入
	inst_mesh_ = inst_mesh;
	spawn_pos_ = spawn_pos;
	target_posx_ = target_pos_x;
	target_posy_ = target_pos_y;

	//角度計算
	int x = target_posx_ - (int)spawn_pos_.x;
	int y = target_posy_ - (int)spawn_pos_.y;
	angle_ = atan2(y, x);

	//画面の端の座標取得
	upleft_ = Play_Map::GetInstance_PlayMap()->MapEdge_Getter("upleft");
	lowright_ = Play_Map::GetInstance_PlayMap()->MapEdge_Getter("lowright");

	tnl::DebugTrace("angle %f",angle_);
}

void NormalAttack::Update(float delta_time) {
	//弾移動
	inst_mesh_->setPosition(inst_mesh_->getPosition() + tnl::Vector3{ (float)cos(angle_) * speed_, (float)sin(angle_) * speed_, 0.0f });
	
	//マップ外に行けば弾は消える
	/*tnl::Vector3 nowpos = inst_mesh_->getPosition();
	if (nowpos.x < upleft_.x || nowpos.y < upleft_.y || nowpos.x > lowright_.x || nowpos.y > lowright_.y) {
		Delete();
	}*/
	
	DrawStringEx(10,70,-1,"bulletmesh %f %f",inst_mesh_->getPosition().x, inst_mesh_->getPosition().y);
}

void NormalAttack::Delete() {
	is_alive_ = false;

	//falseになると消える処理はAttackManagerに書いてある
}

bool NormalAttack::Getter_is_alive() {
	return is_alive_;
}
