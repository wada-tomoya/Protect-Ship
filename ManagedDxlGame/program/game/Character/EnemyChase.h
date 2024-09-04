#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "EnemyBase.h"

class Camera;
class CharacterBase;

//�v���C���[��ǂ�������G
//�����i�^�[�Q�b�g�A�������b�V���A�ړ����x�A�̗́A���܂Ƃ̓����蔻��p�̔��a�A�v���C���[�Ƃ̓����蔻��p�̃T�C�Y�j
class EnemyChase : public EnemyBase {
private:
	//�^�[�Q�b�g�i�v���C���[�j
	std::weak_ptr<CharacterBase> target_;

	//�V�[�P���X
	TNL_CO_SEQUENCE(EnemyChase, &EnemyChase::SEQ_Move)
	//�ړ��V�[�P���X
	bool SEQ_Move(const float delta_time);
	//�U���V�[�P���X
	bool SEQ_Attack(const float delta_time);
	//�U�����󂯂����V�[�P���X
	bool SEQ_HitRecieve(const float dleta_time);
	//���S�V�[�P���X
	bool SEQ_Death(const float delta_time);

	//�A�j���[�V�����̎��
	enum ANIMTYPE {
		Attack_1,
		Attack_2,
		Danse,
		Death,
		HitRecieve, 
		Idle,
		Jump,
		No,
		Walk,
		Yes,
		Max
	};
	ANIMTYPE animtype_ = Idle;

public:
	EnemyChase() = default;

	//�����P�F�^�[�Q�b�g�A�Q�F�������b�V���A�R�F�e���b�V���A
	// �S�F�ړ����x�A�T�F�̗́A�U�F���܂Ƃ̓����蔻��p�̔��a�A�V�F�v���C���[�Ƃ̓����蔻��p�̃T�C�Y
	EnemyChase(std::weak_ptr<CharacterBase> player, const int& duplication_mesh, const Shared<dxe::InstMesh>& shadow_mesh,
		const float& speed, const float& hp, const float& colli_rad, const tnl::Vector3& colli_size);
	~EnemyChase();

	//���s�֐�
	//�����P�F����
	void Update(const float& delta_time) override;
	//�`��֐�
	//�����P�F�J�����C���X�^���X
	void Draw(const std::shared_ptr<Camera>& camera) override;
};
