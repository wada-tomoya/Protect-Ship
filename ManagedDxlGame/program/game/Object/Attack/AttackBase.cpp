#include "AttackBase.h"

void AttackBase::Draw_Ptcl(std::shared_ptr<Camera> camera) {
	//�q�b�g���̃p�[�e�B�N���`��
	hit_ptcl_->render(camera);
	//�ړ����̃p�[�e�B�N���`��
	move_ptcl_->render(camera);
}

float AttackBase::MapCenter_Vec(){
	float vec = static_cast<float>(std::pow((inst_mesh_->getPosition().z - map_center_.z), 2))
		+ (std::pow((inst_mesh_->getPosition().x - map_center_.x), 2));

	return vec;
}
