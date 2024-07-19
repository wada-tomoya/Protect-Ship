#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "CharacterBase.h"
#include "../Manager/AttackManager.h"
#include "../Object/Item/ItemBase.h"

class Camera;

//�����i�}�b�v�̈ړ����E�̒��S�A�ړ����E�̔��a�j
class Player : public CharacterBase, public AttackManager{
private:
	//�����蔻��p����
	const float colli_thickness_ = 8.0f;
	//�����蔻��̏�ԃt���O�itrue�����蔻��L���A false�����蔻�薳���j
	bool is_colli_ = true;
	//0�ȏ�Ȃ疳�G
	float invincible_ = 0.0f;
	//0�ȉ��Ȃ�U���ł���
	float can_attack_ = 0.0f;
	//�U���C���^�[�o���ł̍U���\�^�C�~���O
	bool is_normalattack_ = true;
	//true�Ȃ�v���C���[�\��
	bool is_flash_ = true;
	//���G����
	float invincible_time_ = 3.0f;
	//�_�ŊԊu�A�_�ŃJ�E���g
	float flash_interval_ = 0.25f, flash_count_ = 0.0f;
	//�_���[�W���U���s�\����
	const float cooldown_time_ = 2.0f;

	//�e�N�X�`���摜�n���h��
	Shared<dxe::Texture> texture_hdl_ = nullptr;
	//���b�V���z��̗v�f��
	static const int player_mesh_index_ = 3;
	//�e�N�X�`����������
	const int texture_div_ = 3; 
	//�e�N�X�`���c������
	const int texture_height_div_ = 4;
	//���b�V��
	Shared<dxe::Mesh> mesh_front_[player_mesh_index_];
	Shared<dxe::Mesh> mesh_left_[player_mesh_index_];
	Shared<dxe::Mesh> mesh_right_[player_mesh_index_];
	Shared<dxe::Mesh> mesh_back_[player_mesh_index_];
	
	//�e�̃��b�V��
	Shared<dxe::Mesh> shadow_mesh_ = nullptr;
	//�e�̃e�N�X�`��
	Shared<dxe::Texture> shadow_texture_ = nullptr;
	//90�x�|��
	tnl::Quaternion shadow_down_ = tnl::Quaternion::RotationAxis({1,0,0}, tnl::ToRadian(90));
	//�e��y���W
	const float shadow_pos_y_ = 0.1f;

	//�ʏ�U���̔��˕����������J�[�\����Mesh
	Shared<dxe::Mesh> cursor_mesh_ = nullptr;
	//�J�[�\���̃e�N�X�`��
	Shared<dxe::Texture> cursor_texture_;
	//�J�[�\���ƃv���C���[�̋���
	float distance_cursor_player_ = 20.0f;
	//�J�[�\���̊p�x
	tnl::Quaternion cursor_rad_ = tnl::Quaternion();
	//�J�[�\���̍��W
	tnl::Vector3 cursor_pos_{ 0,0,0 };
	//�J�[�\����90�x�X����悤
	tnl::Quaternion cursor_down_ = tnl::Quaternion::RotationAxis({ 1,0,0 }, tnl::ToRadian(90));

	//�}�E�X�J�[�\���̃��C�ƒn�ʂ̓����������W
	tnl::Vector3 ground_hit_pos_{ 0,0,0 };
	//ground_hit_pos_�̃p�[�e�B�N��
	//Shared<dxe::Particle> attackcursor_ptcl_ = nullptr;

	//�X�e�[�^�Xup�̃A�C�e��list
	std::vector<ITEMTYPE> statusup_itemlist_;
	//�A�C�e��list�̍ő�v�f��
	const int itemmax_ = 5;
	//�A�C�e���ŕω�����X�e�[�^�X
	struct ATTACKSTATUS {
		//�U���ړ����x
		float speed_attack_ = 0.0f;
		//�����Ԋu
		float interval_ = 0.0f;
		//�U����
		float power_ = 0.0f;
		//�ђʗ�
		int Penetration_ = 0;
		//�傫��
		float size_scale_ = 1.0f;
		//�v���C���[�ړ����x
		float speed_player_ = 0.0f;
		//�オ�蕝
		float speed_attack_up_ = 5.0f;
		float interval_down_ = 0.07f;
		float power_up_ = 8.0f;
		int penetration_up_ = 1;
		float size_scale_up_ = 0.25f;
		float speed_player_up_ = 1.5f;
		//�΂��擾���Ă���ꍇ�̍U���͂̌��蕝
		float power_down_ = 1.5f;
	};
	ATTACKSTATUS itemupstatus_;
	const float little_up_ = 0.2f;

	//�}�b�v�̒n�ʂ̃��b�V��
	std::weak_ptr<dxe::Mesh> ground_;
	//�J����
	std::weak_ptr<Camera> camera_;

public:
	Player(tnl::Vector3 map_center, float map_rad, std::weak_ptr<dxe::Mesh> ground, std::weak_ptr<Camera> camera);
	~Player();
	//���s�֐�
	void Update(float delta_time) override;
	//�v���C���[�̕`��֐�
	void Draw(float delta_time, std::shared_ptr<Camera> camera) override;
	//�U���̕`��
	void AttackDraw(std::shared_ptr<Camera> camera);

	//�v���C���[�_��
	void Flashing(float delta_tim, float flash_interval);
	//�ړ��@
	//�����idelta_time, �ړ��o����}�b�v�̒��S�A���a�j
	void Move(float delta_time);
	//��ʂ̒��S����}�E�X�J�[�\���̕����ւ̃x�N�g���𐳋K�������l
	tnl::Vector3 Cursor_Move_Norm_();
	//��ʒ��S����}�E�X�J�[�\���ւ̊p�x�i�x���@�j
	float Angle_Center_Mouse();
	//�U��
	void Attack_Create(float delta_time);
	//�G�ƐڐG�������̏���
	void Enemy_Hit();
	//�A�C�e���ƐڐG�������̏���
	void Item_Hit(ITEMTYPE itemtype);
	//list���̃A�C�e�������ɍU���X�e�[�^�X�ݒ�
	void AttackStatus_Set();

	//�X�e�[�^�Xup�A�C�e���̃Z�b�^�[
	void Setter_Item(ITEMTYPE& itemtype);
	//���G��ԃt���O�̃Q�b�^�[
	bool Getter_is_colli()const { return is_colli_; };
	//�`��t���O�̃Q�b�^�[
	bool Getter_is_flash_()const { return is_flash_; };
	//�X�e�[�^�Xup�̃A�C�e��list�̃Q�b�^�[
	std::vector<ITEMTYPE >& Getter_statusup_itemlist_() { return statusup_itemlist_; };
};

