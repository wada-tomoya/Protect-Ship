#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include "AttackBase.h"

class NormalAttack : public AttackBase{
private:	
	//��]�p�x
	const float rotate_angle_ = 10.0f;

	//�V�[�P���X
	TNL_CO_SEQUENCE(NormalAttack, &NormalAttack::SEQ_Move)
	//�ړ��V�[�P���X
	bool SEQ_Move(const float delta_time);
	//�q�b�g�V�[�P���X
	bool SEQ_Hit(const float delta_time);
	//�����V�[�P���X
	bool SEQ_Death(const float delta_time);
	
public:		 
	NormalAttack() = default;

	//�����P�F�}�b�v�̒��S�A�Q�F�}�b�v�̔��a�A�S�F�������W�A�T�F�i�s�����̊p�x�A
	//�U�F�������ꂽ���b�V���A�V�F�U���̔��a�A�W�F�U���q�b�g���̃p�[�e�B�N���A
	//�X�F�U���ړ����̃p�[�e�B�N���A�P�O�F�ړ����x�A�P�P�F�U���́A�P�Q�F�ђʗ�
	NormalAttack(const tnl::Vector3& map_center, const float& map_rad, const tnl::Vector3& spawn_pos, const tnl::Quaternion& dir_angle,
		const std::shared_ptr<dxe::InstMesh>& inst_mesh, const float& bullet_rad, const std::shared_ptr<dxe::Particle>& hit_ptcl, 
		const std::shared_ptr<dxe::Particle>& move_ptcl, const float& speed, const float& power, const int& Penetration_);
	~NormalAttack();

	//���s�֐�
	//�����P�F����
	void Update(const float& delta_time) override;
	//�G�ɓ����������̏���
	//�����P�F���������G�̃A�h���X
	void Enemy_Hit(EnemyBase* hiteneaddress = 0) override;
};
