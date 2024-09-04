#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include "AttackBase.h"

class BombAttack : public AttackBase {
private:
	//�V�[�P���X
	TNL_CO_SEQUENCE(BombAttack, &BombAttack::SEQ_Move)
	//�ړ��V�[�P���X
	bool SEQ_Move(const float delta_time);
	//�q�b�g�i���j�j�V�[�P���X
	bool SEQ_Hit(const float delta_time);
	//�����V�[�P���X
	bool SEQ_Death(const float delta_time);

	//���j���̃_���[�W
	float explosion_damage_ = 1000.0f;
	//���j�����蔻��T�C�Y�̃p�[�e�B�N���Ƃ̔䗦
	float explosion_size_ = 0.8f;

public:
	BombAttack() = default;

	//�����P�F�}�b�v�̒��S�A�Q�F�}�b�v�̔��a�A�R�F�^�[�Q�b�g�i�i�s�����j�̍��W�A�S�F�������W�A
	//�T�F�i�s�����̊p�x�A�U�F�������ꂽ���b�V���A�V�F�U���̔��a�A
	//�W�F�U���q�b�g���̃p�[�e�B�N���A�X�F�U���ړ����̃p�[�e�B�N���A�P�O�F�U���q�b�g���̉�
	BombAttack(const tnl::Vector3& map_center, const float& map_rad, const tnl::Vector3& target_pos, const tnl::Vector3& spawn_pos,
		const tnl::Quaternion& dir_angle, const std::shared_ptr<dxe::InstMesh>& inst_mesh, const float& bullet_rad,
		const std::shared_ptr<dxe::Particle>& hit_ptcl, const std::shared_ptr<dxe::Particle>& move_ptcl, const int& hit_se);
	~BombAttack();

	//���s�֐�
	//�����P�F����
	void Update(const float& delta_time) override;
	//�G�ɓ����������̏���
	//�����P�F���������G�̃A�h���X
	void Enemy_Hit(EnemyBase* hiteneaddress = 0) override;
};