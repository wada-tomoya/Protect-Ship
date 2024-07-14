#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include "math.h"
#include "AttackBase.h"

//�����i�}�b�v�̒��S�A�}�b�v�̔��a�A����������W�A�i�s�����̊p�x�A�������ꂽ���b�V��, �e�̔��a�A�G�ɓ����������̃p�[�e�B�N���j
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
	float explosion_damage_ = 30.0f;
	//���j�����蔻��T�C�Y�̃p�[�e�B�N���Ƃ̔䗦
	float explosion_size_ = 0.8f;

public:
	BombAttack(const tnl::Vector3 map_center, const float map_rad, tnl::Vector3 target_pos, const tnl::Vector3& spawn_pos,
		const tnl::Quaternion dir_angle, Shared<dxe::InstMesh> inst_mesh, float bullet_rad, 
		std::shared_ptr<dxe::Particle> hit_ptcl, std::shared_ptr<dxe::Particle> move_ptcl, int hit_se);
	~BombAttack();

	//���s�֐�
	void Update(float delta_time) override;
	//�G�ɓ����������̏���
	void Enemy_Hit() override;
};