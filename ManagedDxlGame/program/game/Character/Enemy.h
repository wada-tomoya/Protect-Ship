#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../Object/Camera.h"
#include "EnemyBase.h"
#include "../Manager/ResourceManager.h"
#include "../Object/ProtectObject.h"

//ProtectObject�Ɍ������Đi�s����G
//�����i�^�[�Q�b�g�A�������b�V���A�e���b�V���A�ړ����x�A�̗́A���܂Ƃ̓����蔻��p�̔��a�A�v���C���[�Ƃ̓����蔻��p�̃T�C�Y�j
class Enemy : public EnemyBase {
private:
	//�^�[�Q�b�g�i�D�j
	std::weak_ptr<ProtectObject> target_;

	//�����V�[�P���X�ݒ�
	TNL_CO_SEQUENCE(Enemy, &Enemy::SEQ_Move)
	//�ړ��V�[�P���X
	bool SEQ_Move(const float delta_time) ;
	//�U���V�[�P���X
	bool SEQ_Attack(const float delta_time) ;
	//�U�����󂯂����V�[�P���X
	bool SEQ_HitRecieve(const float delta_time);
	//���S�V�[�P���X
	bool SEQ_Death(const float delta_time) ;

	//�A�j���[�V�����̎��
	enum ANIMTYPE {
		Attack_1,
		Attack_2,
		Dance,
		Death,
		HitRecieve,
		Jump,
		No,
		Walk,
		Yes,
		Idle,
		Max
	};
	ANIMTYPE animtype_ = Idle;		

public:
	//�R���X�g���N�^
	Enemy(std::weak_ptr<ProtectObject> protectobject, int duplication_mesh, Shared<dxe::InstMesh> shadow_mesh,
		float speed, float hp, float colli_rad, tnl::Vector3 colli_size);
	~Enemy();
	
	//���s�֐�
	void Update(float delta_time) override;
	//�`��֐�
	void Draw(std::shared_ptr<Camera> camera) override;
};