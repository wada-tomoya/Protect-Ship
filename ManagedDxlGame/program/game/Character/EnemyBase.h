#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

class Camera;

class EnemyBase {
protected:
	//�������ꂽ���f��
	int duplication_model_ = 0;
	//�e�̃��b�V��
	Shared<dxe::InstMesh> shadow_mesh_ = nullptr;
	//�^�[�Q�b�g�̍��W
	tnl::Vector3 target_pos_{ 0,0,0 };
	//�G�̐���
	bool is_alive_ = true;
	//�T�C�Y
	tnl::Vector3 size_{ 0,0,0 };
	//�ړ����x
	float speed_ = 0.0f;
	//�ړ�����
	tnl::Vector3 move_dir_{ 0,0,0 };
	//�ړ��O���W
	DxLib::VECTOR prev_pos_{ 0,0,0 };	
	//�^�[�Q�b�g�Ƃ̋���
	float distance_target_ = 0.0f;
	//�����ʒu�̃}�b�v���S����̊p�x
	float spawn_angle_ = 0.0f;
	//�U���̃C���^�[�o��
	float attack_interval_ = 0.0f, attack_count_ = 0.0f;
	//�U����
	float attack_power_ = 1.0f;
	//�̗�
	float hp_ = 10.0f;

	//�e�Ƃ̓����蔻��p�̔��a
	float colli_rad_ = 0.0f;
	//�����蔻��p�̋��̒��S���W
	tnl::Vector3 colli_center_{ 0,0,0 };
	//�v���C���[�Ƃ̓����蔻��p�T�C�Y
	tnl::Vector3 colli_size_{};

	//�i�s�����X�V�C���^�[�o��
	float movedir_update_interval_ = 0.5f;
	float movedir_update_count_ = 0.0f;

	//�U���Ɉڂ�^�[�Q�b�g�Ƃ̋���
	float trans_attack_distance_ = 50.0f;

	//�v���C���[�̍U�����q�b�g���̃t���O
	bool is_HitRecieve_ = false;

	//�U����se
	int attack_se_hdl_ = 0;
	//���S��������se
	int death_se_hdl_ = 0;
	//�v���C���[�̍U�����q�b�g��������se
	int hit_se_hdl_ = 0;

	//���S���̃p�[�e�B�N��
	std::shared_ptr<dxe::Particle> death_ptcl_ = nullptr;

	//�A�j���[�V�����t���O
	bool is_anim_ = true;
	//�A�j���[�V��������������t���O
	bool is_anim_end_ = false;
	//�A�j���[�V�����Đ����x
	float anim_speed_ = 15.0f;
	//���f���̃A�j���[�V��������
	int anim_num_ = 0;
	//�A�^�b�`�i�Đ��j����A�j���[�V����
	int anim_attachi_index_ = 0;
	//�A�^�b�`����Ă���A�j���[�V�����̍Đ����ԁA�A�j���[�V�����̍Đ��J�E���g
	float anim_totaltime_ = 0.0f, anim_count_ = 0.0f;

	//�A�C�e�������t���O
	bool is_itemspawn_ = true;
	
public:
	//�R���X�g���N�^
	EnemyBase();
	~EnemyBase();

	//���s�֐�
	//�����P�F����
	virtual void Update(const float& delat_time);
	//�`��֐�
	//�����P�F�J�����C���X�^���X
	virtual void Draw(const std::shared_ptr<Camera>& camera);

	//���S�i�����j
	void Delete() { is_alive_ = false; };
	//�i�s�����̊p�x�v�Z
	float Rotate_front();
	//�^�[�Q�b�g�Ƃ̋������v�Z
	float Distance_target();
	//�ړ������X�V
	//�����P�F���ԁA�ړ������X�V�Ԋu
	void Movedir_update(const float& delta_time, const float& movedir_update_interval = 0.0f);
	//�v���C���[�̍U��������������
	//�����P�F�󂯂�_���[�W
	virtual void PlyaerAttack_Recieve(const float& damage);
	//�A�j���[�V�����̕ύX
	//�����P�F�A�j���[�V�����̃^�C�v
	void Anim_Change(const int& animtype);
	//�A�j���[�V�����Đ�
	//�����P�F����
	void AnimPlay(const float& delta_time);

//�Q�b�^�[�A�Z�b�^�[

	//is_alive_�̃Q�b�^�[�@
	bool Getter_is_alive()const { return is_alive_; };
	//is_alive_�̃Z�b�^�[
	void Setter_is_alive(bool is_alive) { is_alive_ = (is_alive = true) ? true : false; };
	//���W�̃Q�b�^�[
	tnl::Vector3 Getter_pos()const { 
		tnl::Vector3 pos = {0,0,0};
		pos.x = MV1GetPosition(duplication_model_).x;
		pos.y = MV1GetPosition(duplication_model_).y;
		pos.z = MV1GetPosition(duplication_model_).z;
		return pos; 
	};
	//hp�̃Z�b�^�[
	void Setter_hp(const float& damage) { hp_ += damage; };
	//hp�̃Q�b�^�[
	float Getter_hp()const { return hp_; };
	//�������ꂽ���f���n���h���̃Q�b�^�[
	int Getter_dup_model()const { return duplication_model_; };
	//�����蔻��p�̔��a�̃Q�b�^�[
	float Getter_colli_rad()const { return colli_rad_; };
	//�e�Ƃ̓����蔻��p�̋��̒��S���W�̃Q�b�^�[
	tnl::Vector3 Getter_colli_center()const { return colli_center_; };
	//�v���C���[�Ƃ̓����蔻��p�T�C�Y�Q�b�^�[
	tnl::Vector3 Getter_colli_size()const { return colli_size_; };
	//�U���͂̃Q�b�^�[
	float Getter_attack_power()const { return attack_power_; };
	//�A�C�e�������t���O�̃Q�b�^�[
	bool Getter_is_itemspawn()const { return is_itemspawn_; };
};
