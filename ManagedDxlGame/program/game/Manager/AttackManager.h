#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../Object/Attack/NormalAttack.h"
#include "../Object/Attack/BombAttack.h"

struct ATTACK;
class Camera;

class AttackManager {
public:
	//�e�U���̎��s�֐�
	//�����P�F���ԁA�Q�F�U���̃��X�g
	void Attack_Update(const float& delta_time, std::list<std::shared_ptr<AttackBase>>& attacks);
	//�e�U���̕\���֐�
	//�����P�F�J�����C���X�^���X�A�Q�F�U���̃��X�g�A�R�F�U���̍\����
	void Attack_Draw(const std::shared_ptr<Camera>& camera, const std::list<std::shared_ptr<AttackBase>>& attacks, const ATTACK& normalatk);

	//�U�������֐� player�����̊֐����ĂԂ��ƂōU�������������
	//�����P�F�U���̏������W�A�Q�F�i�s�����̍��W�A�R�F�ړ����x�オ�蕝�A�S�F�U���オ�蕝�A�T�F�ђʗ͏オ�蕝�A
	// �U�F�U����list�A�V�F�ʏ�U���̏��A
	// �W�F�}�b�v�̒��S�A�X�F�}�b�v�̔��a�A�P�O�F�e�N�X�`���̔ԍ��A�P�P�F�������b�V���̃T�C�Y�X�P�[��
	void NormalAttack_Create(const tnl::Vector3& spwan_pos, const tnl::Quaternion& dir_angle, const float& speed, const float& power, const int& Penetration_,
		std::list<std::shared_ptr<AttackBase>>& attacks, const ATTACK& normalatk,
		const tnl::Vector3& atk_map_center, const float& atk_map_rad, const int& texturenum, const float& size_scale);

	//�����P�F�U���̏������W�A�Q�F�i�s�����̍��W�A�R�F�������̃}�E�X���C�̍��W�A
	// �S�F�U����list�A�T�F���j�U���̏��A�U�F�}�b�v�̒��S�A�V�F�}�b�v�̔��a�A�W�F�e�N�X�`���̔ԍ�
	void BombAttack_Create(const tnl::Vector3& spawn_pos, const tnl::Quaternion& dir_angle, const tnl::Vector3& target_pos,
		std::list<std::shared_ptr<AttackBase>>& attacks, const ATTACK& bombatk, const tnl::Vector3& atk_map_center,
		const float& atk_map_rad, const int& texturenum);
};
