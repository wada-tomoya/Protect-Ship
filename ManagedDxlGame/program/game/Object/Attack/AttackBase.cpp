#include "AttackBase.h"
#include "../../Object/Camera.h"

AttackBase::AttackBase(const std::shared_ptr<dxe::InstMesh>& inst_mesh, const std::shared_ptr<dxe::Particle>& hit_ptcl, 
	const std::shared_ptr<dxe::Particle>& move_ptcl, const tnl::Quaternion& dir_angle, const tnl::Vector3& map_center,
	const float& map_rad, const float& bullet_rad, const tnl::Vector3& spawn_pos) {
	//�������ꂽ���b�V��
	inst_mesh_ = inst_mesh;
	//���j���̃p�[�e�B�N��
	hit_ptcl_ = hit_ptcl;
	//�ړ����̃p�[�e�B�N��
	move_ptcl_ = move_ptcl;
	
	//�i�s�����̊p�x
	dir_rad_ = dir_angle;
	//�v���C�G���A�̒��S
	map_center_ = map_center;
	//�v���C�G���A�̔��a
	map_rad_ = map_rad;
	//�}�b�v�̒��S����O���܂ł̃x�N�g��
	map_vec_ = static_cast<float>(std::pow(map_rad, 2));
	//�e�̔��a�ݒ�
	bullet_rad_ = bullet_rad;
	//�������W�ݒ�
	inst_mesh_->setPosition(spawn_pos);
	//�������Ԑݒ�
	hit_ptcl_time_ = hit_ptcl_->getTimeLimit();
	//�����͈͐ݒ�
	move_ptcl_->setOriginRange(bullet_rad_);
}

AttackBase::~AttackBase() {
	hit_ptcl_.reset();
	move_ptcl_.reset();
}

void AttackBase::Draw_Ptcl(const std::shared_ptr<Camera>& camera) {
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
