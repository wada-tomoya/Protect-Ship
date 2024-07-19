#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../Object/Attack/NormalAttack.h"
#include "../Object/Attack/BombAttack.h"

struct ATTACK;
class Camera;

class AttackManager {
public:
	//�e�U���̎��s�֐�
	void Attack_Update(float delta_time, std::list<std::shared_ptr<AttackBase>>& attacks);
	//�e�U���̕\���֐�
	void Attack_Draw(std::shared_ptr<Camera>& camera, std::list<std::shared_ptr<AttackBase>>& attacks, const ATTACK& normalatk);

	//�U�������֐� player�����̊֐����ĂԂ��ƂōU�������������
	//�����i�U���̏������W�A�i�s�����̍��W�A�ړ����x�オ�蕝�A�U���オ�蕝�A�ђʗ͏オ�蕝�A
	// �U����list�A�ʏ�U���̏��A
	// �}�b�v�̒��S�A�}�b�v�̔��a�A�e�N�X�`���̔ԍ�, �������b�V���̃T�C�Y�X�P�[���j
	void NormalAttack_Create(tnl::Vector3 spwan_pos, tnl::Quaternion dir_angle, float speed, float power, int Penetration_,
		std::list<std::shared_ptr<AttackBase>>& attacks, const ATTACK& normalatk,
		const tnl::Vector3& atk_map_center, const float& atk_map_rad, int texturenum, float size_scale);

	//�����i�U���̏������W�A�i�s�����̍��W�A�������̃}�E�X���C�̍��W�A
	// �U����list�A���j�U���̏��A�}�b�v�̒��S�A�}�b�v�̔��a�A�e�N�X�`���̔ԍ��j
	void BombAttack_Create(tnl::Vector3 spawn_pos, tnl::Quaternion dir_angle, tnl::Vector3 target_pos,
		std::list<std::shared_ptr<AttackBase>>& attacks, const ATTACK& bombatk, const tnl::Vector3& atk_map_center,
		const float& atk_map_rad, int texturenum);
};
