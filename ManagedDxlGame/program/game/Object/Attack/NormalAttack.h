#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include "AttackBase.h"

//�����i�}�b�v�̒��S�A�}�b�v�̔��a�A����������W�A�i�s�����̊p�x�A�������ꂽ���b�V��, 
// �e�̔��a�A�G�ɓ����������̃p�[�e�B�N���A�ړ����̃p�[�e�B�N���A
//�ړ����x�オ�蕝�A�U���オ�蕝�A�ђʗ͏オ�蕝�j
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
	NormalAttack(const tnl::Vector3 map_center, const float map_rad,const tnl::Vector3& spawn_pos,
		const tnl::Quaternion dir_angle, std::shared_ptr<dxe::InstMesh>& inst_mesh, float bullet_rad,
		std::shared_ptr<dxe::Particle>& hit_ptcl, std::shared_ptr<dxe::Particle>& move_ptcl,
		float speed, float power, int Penetration_);
	~NormalAttack();

	//���s�֐�
	void Update(float delta_time) override;
	//�G�ɓ����������̏���
	void Enemy_Hit() override;
};
