#include "NormalAttack.h"
#include "math.h"

NormalAttack::NormalAttack(const tnl::Vector3& map_center, const float& map_rad, const tnl::Vector3& spawn_pos,
	const tnl::Quaternion& dir_angle, const std::shared_ptr<dxe::InstMesh>& inst_mesh, const float& bullet_rad,
	const std::shared_ptr<dxe::Particle>& hit_ptcl, const std::shared_ptr<dxe::Particle>& move_ptcl,
	const float& speed, const float& power, const int& penetration) :
	AttackBase(inst_mesh, hit_ptcl, move_ptcl, dir_angle, map_center, map_rad, bullet_rad, spawn_pos) {
	
	//�U���͐ݒ�
	attack_power_ = 10.0f + power;
	//�U���͂�1�����ɂ��Ȃ�
	if (attack_power_ <= 1.0f) {
		attack_power_ = 1.0f;
	}
	//�e�̑��x�ݒ�
	speed_ = 15.0f + speed;
	//�ђʗ̓Z�b�g
	penetration_ = penetration;

	//�m�b�N�o�b�N�l�ݒ�
	knockback_value_ = 1.0f;
}

NormalAttack::~NormalAttack(){

}

void NormalAttack::Update(const float& delta_time) {
	//�V�[�P���X���s
	tnl_sequence_.update(delta_time);
}

void NormalAttack::Enemy_Hit(EnemyBase* hiteneaddress){
	//���������G�̃A�h���X��ۑ�
	hiteneaddress_.emplace_back(hiteneaddress);

	//�q�b�g���̃p�[�e�B�N������
	is_hit_ptcl_ = true;
	hit_ptcl_->setPosition(Getter_pos());
	hit_ptcl_->start();

	//�ђʗ͌���
	penetration_--;
}

bool NormalAttack::SEQ_Move(const float delta_time){
	//�e�ړ�
	inst_mesh_->setPosition(inst_mesh_->getPosition() + tnl::Vector3::TransformCoord({ 0,speed_,0 }, dir_rad_));

	//��]
	inst_mesh_->setRotation(inst_mesh_->getRotation() * tnl::Quaternion::RotationAxis({ 1,0,0 }, tnl::ToRadian(rotate_angle_)));
	inst_mesh_->setRotation(inst_mesh_->getRotation() * tnl::Quaternion::RotationAxis({ 0,1,0 }, tnl::ToRadian(rotate_angle_ / 2)));

	//�e����v���C�G���A�̒��S�̃x�N�g��
	float vec = MapCenter_Vec();

	//�ړ��p�[�e�B�N���̍��W�ݒ�
	move_ptcl_->setPosition(inst_mesh_->getPosition());

	//�V�[�P���X�ړ�����
	//�ђʗ͂�0�����ɂȂ��
	if (penetration_ < 0) {
		//�ړ����̃p�[�e�B�N���I��
		move_ptcl_->stop();

		tnl_sequence_.change(&NormalAttack::SEQ_Hit);
	}
	//�}�b�v�O�ɏo����
	else if (vec >= map_vec_) {
		//�ړ����̃p�[�e�B�N���I��
		move_ptcl_->stop();

		tnl_sequence_.change(&NormalAttack::SEQ_Death);
	}

	TNL_SEQ_CO_END
}

bool NormalAttack::SEQ_Hit(const float delta_time){
	//�����蔻�����
	is_collision_ = false;

	//�`�悵�Ȃ��悤�ݒ�
	inst_mesh_->setDrawEnable(false);

	//�p�[�e�B�N����������
	hit_ptcl_count_ += delta_time;
	//�V�[�P���X�ړ�����
	//hit_ptcl_�̐������Ԍo�߂�����e����
	if (hit_ptcl_count_ >= hit_ptcl_time_) {
		tnl_sequence_.change(&NormalAttack::SEQ_Death);
	}

	TNL_SEQ_CO_END
}

bool NormalAttack::SEQ_Death(const float delta_time){
	//�U������
	Delete();

	TNL_SEQ_CO_END
}
