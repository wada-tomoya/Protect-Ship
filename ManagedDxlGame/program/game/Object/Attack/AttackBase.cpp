#include "AttackBase.h"

void AttackBase::Draw_Ptcl(std::shared_ptr<Camera> camera) {
	//ヒット時のパーティクル描画
	hit_ptcl_->render(camera);
	//移動時のパーティクル描画
	move_ptcl_->render(camera);
}

float AttackBase::MapCenter_Vec(){
	float vec = static_cast<float>(std::pow((inst_mesh_->getPosition().z - map_center_.z), 2))
		+ (std::pow((inst_mesh_->getPosition().x - map_center_.x), 2));

	return vec;
}
