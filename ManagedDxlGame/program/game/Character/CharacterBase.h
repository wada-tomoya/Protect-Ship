#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../Object/Camera.h"

class AttackBase;

//�ʏ�U��
struct ATTACK {
	//���������b�V��
	Shared<dxe::Mesh> origine_mesh_ = nullptr;
	//�C���X�^���V���O���b�V���v�[��
	Shared<dxe::InstMeshPool> mesh_pool_ = nullptr;
	//�T�C�Y
	float size_ = 20.0f;
	//instmesh�̕����ő吔
	int instmax_ = 100;
	//�U���q�b�g���̃p�[�e�B�N��
	std::shared_ptr<dxe::Particle> hit_ptcl_;
	//�ړ����̃p�[�e�B�N��
	std::shared_ptr<dxe::Particle> move_ptcl_;
	//�q�b�g����se
	int hit_se_hdl_ = 0;
};

class CharacterBase {
protected:
	
	//�ړ����x
	float speed_ = 0;
	//�v�Z���ړ����x
	float ori_speed_ = 0;
	//�摜�T�C�Y
	tnl::Vector3 size_{ 0,0,0 };
	//�\�����W
	tnl::Vector3 pos_ { 0,0,0 };
	//�ړ��O�̍��W
	tnl::Vector3 prev_pos_{ 0,0,0 };
	//���E���]�t���O
	bool isturn_ = false;
	//�L�����N�^�[�̌���
	enum class DIRECTION {
		FRONT = 1,
		LEFT = 2,
		RIGHT = 3,
		BACK = 4
	};
	DIRECTION chara_dir_ = DIRECTION::RIGHT;
	//�ړ��t���O
	bool is_move_ = false;
	//�A�j���[�V�����Đ��̃J�E���g
	float anim_time_ = 0.0f;
	//�Đ�����t���[��
	int anim_frame_ = 0;
	//�A�j���[�V�����̍Đ����x
	float anim_speed_ = 0.1f;
	//�\�����郁�b�V���z��C���f�b�N�X
	int render_ = 1;
	//�ړ��ł���}�b�v�̒��S
	tnl::Vector3 map_center_{ 0,0,0 };
	//�ړ��ł���}�b�v�̔��a
	float map_rad_ = 0.0f;
	//�}�b�v�̒�������̊O���܂ł̒l�̕�����
	float map_rad_root_ = 0.0f;

	//�G�Ƃ̓����蔻��p�̃T�C�Y
	tnl::Vector3 colli_size_{ 0,0,0 };

	//�U���֌W--------------------------------------------------------------------------

	//�ʏ�U��
	ATTACK noratk_;
	//���j�U��
	ATTACK bomatk_;
	//�e�N�X�`����vector
	std::vector<Shared<dxe::Texture>> atk_textures_;
	//�e�N�X�`���̔z��ԍ�
	enum class TEXTURENUM {
		normalattack,
		bombattack
	};

	//�U����list
	std::list<std::shared_ptr<AttackBase>> attacks_;
	//�v�Z���̒ʏ�U���̑傫��
	float ori_noratk_size_ = 0.0f;
	//�ʏ�U���̒ǉ��ŏo�鐔
	int attack_addnum_ = 0;
	//�ǉ��U���̏o��p�x
	const float addattack_rad_[5] = { 30,60,90,120,150 };
	//�U����L���ɂ���͈͂̒��S�̍��W
	tnl::Vector3 attack_map_center_{ 0,0,0 };
	//�U����L���̂���͈͂̔��a
	float attack_map_rad_ = 0.0f;
	//�ʏ�U�����o�����Ƃ���se
	int attack_se_hdl_ = 0;
	//���e�U�����o��������se
	int bomattack_se_hdl_ = 0;
	//�G�Ɠ�����������se
	int enemy_hit_se_hdl_ = 0;
	//�G�Ɠ����������̃p�[�e�B�N��
	Shared<dxe::Particle> enemy_hit_ptcl_ = nullptr;
	//�U���̈ړ����x
	float attack_speed_ = 10.0f;
	//�U���C���^�[�o��
	float attack_interval_ = 0.5f;
	float attack_count_ = 0.0f;
	//�v�Z�p���̃C���^�[�o��
	const float ori_attack_interval_ = attack_interval_;
	//�v�Z�p���̊ђʗ�
	const int ori_attack_penetration_ = 0;
	//���j�U���̃X�g�b�N��
	int bombstock_ = 0;

public:


	//���s�֐�
	virtual void Update(float delat_time) {};
	//�摜�\���֐�
	virtual void Draw(float delat_time, std::shared_ptr<Camera> camera) {};
	//�A�j���[�V�����֐�
	virtual void Anim_Play(std::shared_ptr<std::vector<int>> animhdl, float delta_time);
	//mesh�e�N�X�`���@�A�j���[�V�����֐�
	virtual void Texture_Anim_Play(int mesharray_index, float delta_time);
	//�v���C���[�̍��W�̃Q�b�^�[
	tnl::Vector3 GetterPos()const { return pos_; };
	//�G�Ƃ̓����蔻��p�̃T�C�Y�̃Q�b�^�[
	tnl::Vector3 Getter_colli_size_()const { return colli_size_; };

	//�U��list�̃Q�b�^�[
	std::list<std::shared_ptr<AttackBase>>& Getter_Aattack_list() { return attacks_; };
	//���e�X�g�b�N�̃Q�b�^�[
	const int& Getter_BombStock()const { return bombstock_; };
};