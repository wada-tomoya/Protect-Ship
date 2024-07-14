#include "BombAttack.h"

BombAttack::BombAttack(const tnl::Vector3 map_center, const float map_rad, tnl::Vector3 target_pos, const tnl::Vector3& spawn_pos,
	const tnl::Quaternion dir_angle, Shared<dxe::InstMesh> inst_mesh, float bullet_rad, 
	std::shared_ptr<dxe::Particle> hit_ptcl, std::shared_ptr<dxe::Particle> move_ptcl, int hit_se){
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
	speed_ = 15.0f;
	//�e�̔��a�ݒ�
	bullet_rad_ = bullet_rad;
	//�������W�ݒ�
	inst_mesh_->setPosition(spawn_pos);
	//�U���͐ݒ�A�n�߂�0
	attack_power_ = 0.0f;
	//�I���_�̍��W
	end_pos_ = target_pos;
	//�������W����I���_�̒���
	length_ = (end_pos_ - spawn_pos).length();
	//�R�Ȃ�ړ��̍ő卂��
	heiget_max_ = 150.0f;

	//���j���̃p�[�e�B�N��
	hit_ptcl_ = hit_ptcl;
	//�������Ԑݒ�
	hit_ptcl_time_ = hit_ptcl_->getTimeLimit();
	//�ړ����̃p�[�e�B�N��
	move_ptcl_ = move_ptcl;
	//�����͈͐ݒ�
	move_ptcl_->setOriginRange(bullet_rad_);

	//�q�b�g����se�ǂݍ���
	hit_se_hdl_ = hit_se;

	heiget_ = 100.0f;
}

BombAttack::~BombAttack(){
	DeleteSoundMem(hit_se_hdl_);
	hit_ptcl_.reset();
	move_ptcl_.reset();
}

void BombAttack::Update(float delta_time){
	//�V�[�P���X���s
	tnl_sequence_.update(delta_time);
}

void BombAttack::Enemy_Hit(){
	//���e��`�悵�Ȃ�
	inst_mesh_->setDrawEnable(false);

	//�q�b�g���̃p�[�e�B�N������
	is_hit_ptcl_ = true;
	hit_ptcl_->setPosition(Getter_pos());
	hit_ptcl_->start();
}

bool BombAttack::SEQ_Move(const float delta_time){
	//�ړ�
	inst_mesh_->setPosition(inst_mesh_->getPosition() + tnl::Vector3::TransformCoord({ 0,speed_, 0 }, dir_rad_));

	//�������̍����v�Z
	traveled_ += speed_;
	heiget_ = sin((traveled_ / length_) * DX_PI) * heiget_max_;
	//��������`��
	inst_mesh_->setPosition({ inst_mesh_->getPosition().x,heiget_,inst_mesh_->getPosition().z });

	//�p�[�e�B�N���̍��W�Z�b�g
	move_ptcl_->setPosition(inst_mesh_->getPosition());

	//�e����v���C�G���A�̒��S�̃x�N�g���̌v�Z
	float vec = MapCenter_Vec();

	//�V�[�P���X�ړ�����
	//�q�b�g���̃p�[�e�B�N�����������ꂽ�Ƃ�
	if (is_hit_ptcl_) {
		//�ړ��p�[�e�B�N����~
		move_ptcl_->stop();

		tnl_sequence_.change(&BombAttack::SEQ_Hit);
	}
	//�}�b�v�O�ɏo����
	else if (vec >= map_vec_) {
		move_ptcl_->stop();

		//�G�ɓ����������̏���
		Enemy_Hit();

		tnl_sequence_.change(&BombAttack::SEQ_Hit);
	}
	//�n�ʂ�艺�ɍs����
	else if (inst_mesh_->getPosition().y <= 0.0f) {
		move_ptcl_->stop();

		//�G�ɓ����������̏���
		Enemy_Hit();

		tnl_sequence_.change(&BombAttack::SEQ_Hit);
	}

	TNL_SEQ_CO_END
}

bool BombAttack::SEQ_Hit(const float delta_time){
	//�����蔻�薳��
	is_collision_ = false;

	//�n�߂�1�t���[������
	if (tnl_sequence_.isStart()) {
		//�����蔻��L��
		is_collision_ = true;
		//���j���̍U���̓Z�b�g
		attack_power_ = explosion_damage_;
		//�����蔻��𔚔j�T�C�Y * explosion_size_��
		bullet_rad_ = hit_ptcl_->getOriginRange() * explosion_size_;
		//se�Đ�
		PlaySoundMem(hit_se_hdl_, DX_PLAYTYPE_BACK);
	}

	//�p�[�e�B�N����������
	hit_ptcl_count_ += delta_time;
	//�V�[�P���X�ړ�����
	//hit_ptcl_�̐������Ԍo�߂�����e����
	if (hit_ptcl_count_ >= hit_ptcl_time_) {
		tnl_sequence_.change(&BombAttack::SEQ_Death);
	}

	TNL_SEQ_CO_END
}

bool BombAttack::SEQ_Death(const float delta_time){
	//�U������
	Delete();

	TNL_SEQ_CO_END
}

