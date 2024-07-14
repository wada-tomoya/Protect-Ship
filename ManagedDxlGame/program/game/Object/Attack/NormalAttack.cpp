#include "NormalAttack.h"

NormalAttack::NormalAttack(const tnl::Vector3 map_center, const float map_rad,const tnl::Vector3& spwan_pos,
	const tnl::Quaternion dir_angle, Shared<dxe::InstMesh> inst_mesh, float bullet_rad, 
	std::shared_ptr<dxe::Particle> hit_ptcl, std::shared_ptr<dxe::Particle> move_ptcl,
	float speed, float power, int penetration) {
	//�������ꂽ���b�V��
	inst_mesh_ = inst_mesh;
	//�i�s�����̊p�x
	dir_rad_ = dir_angle;
	//�v���C�G���A�̒��S
	map_center_ = map_center;
	//�v���C�G���A�̔��a
	map_rad_ = map_rad;	
	//�}�b�v�̒��S����O���܂ł̃x�N�g��
	map_vec_ = static_cast<float>(std::pow(map_rad, 2));
	//�e�̑��x�ݒ�
	speed_ = 15.0f + speed;
	//�e�̔��a�ݒ�
	bullet_rad_ = bullet_rad;
	//�������W�ݒ�
	inst_mesh_->setPosition(spwan_pos);
	//�U���͐ݒ�
	attack_power_ = 10.0f + power;
	//�ђʗ̓Z�b�g
	penetration_ += penetration;

	//�G�Ɠ����������̃p�[�e�B�N���ݒ�
	hit_ptcl_ = hit_ptcl;
	//�������Ԑݒ�
	hit_ptcl_time_ = hit_ptcl_->getTimeLimit();
	//�ړ����̃p�[�e�B�N��
	move_ptcl_ = move_ptcl;
	//�����͈͐ݒ�
	move_ptcl_->setOriginRange(bullet_rad_);


}

NormalAttack::~NormalAttack(){
	hit_ptcl_.reset();
	move_ptcl_.reset();
}

void NormalAttack::Update(float delta_time) {
	//�V�[�P���X���s
	tnl_sequence_.update(delta_time);
}

void NormalAttack::Enemy_Hit(){
	
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
	//�ђʗ͂��O�ɂȂ��
	if (penetration_ <= 0) {
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
