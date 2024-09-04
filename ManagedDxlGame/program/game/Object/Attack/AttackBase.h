#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"

class Camera;
class EnemyBase;

class AttackBase {
protected:
	//�}�b�v�̒��S
	tnl::Vector3 map_center_{ 0,0,0 };
	//�}�b�v�̔��a
	float map_rad_ = 0.0f;
	//�}�b�v�̒��S����O���܂ł̃x�N�g��
	float map_vec_ = 0.0f;

	//�������ꂽ���b�V��
	std::shared_ptr<dxe::InstMesh> inst_mesh_ = nullptr;
	//�������W
	tnl::Vector3 spawn_pos_{ 0,0,0 };
	//�e�̔��a
	float bullet_rad_ = 0.0f;
	//�^�[�Q�b�g�̍��W�i�i�s�������W�j
	float target_posx_ = 0, target_posy_ = 0;
	//�i�s�����̊p�x
	tnl::Quaternion dir_rad_ = tnl::Quaternion();
	//�e�𔭎˂���p�x
	float angle_ = 0.0f;
	//�e�̑��x
	float speed_ = 0.0f;
	//�e�̐���
	bool is_alive_ = true;
	//�U����
	float attack_power_ = 1.0f;

	//�I���_�̍��W
	tnl::Vector3 end_pos_{ 0,0,0 };
	//�������W����I���_�܂Œ���;
	float length_ = 0.0f;
	//�R�Ȃ�ɓ����悤�̍���
	float heiget_ = 0.0f;
	//�R�Ȃ�ɓ����悤�i�񂾋���
	float traveled_ = 0.0f;
	//�R�Ȃ�ړ��̍ő卂
	float heiget_max_ = 0.0f;

	//�����蔻��̗L��
	bool is_collision_ = true;

	//�q�b�g��������se
	int hit_se_hdl_ = 0;

	//�G�Ɠ����������̃p�[�e�B�N��
	std::shared_ptr<dxe::Particle> hit_ptcl_ = nullptr;
	//�U���ړ����̃p�[�e�B�N��
	std::shared_ptr<dxe::Particle> move_ptcl_ = nullptr;
	//hit_ptcl_�����t���O
	bool is_hit_ptcl_ = false;
	//hit_ptcl_��������
	float hit_ptcl_time_ = 0.0f;
	//hit_ptcl_�����J�E���g
	float hit_ptcl_count_ = 0.0f;

	//�ђʗ�
	int penetration_ = 0;
	//���������G�̃A�h���X��list
	std::list<EnemyBase*> hiteneaddress_;

	//�m�b�N�o�b�N�l
	float knockback_value_ = 0.0f;

public:
	AttackBase() = default;

	//�����P�F�������ꂽ���b�V���A�Q�F�U���q�b�g���̃p�[�e�B�N���A�R�F�U���ړ����̃p�[�e�B�N��
	//�S�F�i�s�����p�x�A�T�F�}�b�v�̒��S�A�U�F�}�b�v�̔��a�A�V�A�U���̔��a�A�W�F�U���������W
	AttackBase(const std::shared_ptr<dxe::InstMesh>& inst_mesh, const std::shared_ptr<dxe::Particle>& hit_ptcl, const std::shared_ptr<dxe::Particle>& move_ptcl,
		const tnl::Quaternion& dir_angle, const tnl::Vector3& map_center, const float& map_rad, const float& bullet_rad, const tnl::Vector3& spawn_pos);
	~AttackBase();

	//���s�֐�
	//�����P�F����
	virtual void Update(const float& delta_time) {};
	//�����܂ł̎��s�֐�
	//�����P�F����
	virtual void DeathUpdate(const float& delta_time) {};
	//�p�[�e�B�N���`��
	//�����P�F�J�����C���X�^���X
	void Draw_Ptcl(const std::shared_ptr<Camera>& camera);
	//�G�ɓ����������̏���
	//�����P�F���������G�̃A�h���X
	virtual void Enemy_Hit(EnemyBase* hiteneaddress = 0) {};
	//���W����}�b�v�̒��S�̃x�N�g���v�Z
	float MapCenter_Vec();

//�Q�b�^�[�A�Z�b�^�[
	
	//is_alive_�̃Q�b�^�[
	bool Getter_is_alive()const { return is_alive_; };
	//is_alive_�̃Z�b�^�[;
	void Setter_is_alive(bool is_alive) { is_alive_ = is_alive; };
	//���W�̃Q�b�^�[
	tnl::Vector3 Getter_pos()const { 
		return inst_mesh_->getPosition(); };
	//�T�C�Y�̃Q�b�^�[
	tnl::Vector3 Getter_size()const { 
		return inst_mesh_->getScale(); };
	//���a�̃Q�b�^�[
	float Getter_bullet_rad()const { return bullet_rad_; };
	//�U���͂̃Q�b�^�[
	float Getter_attack_power()const { return attack_power_; };
	//�U���̏��� is_alive��false�ɂ���
	void Delete() { is_alive_ = false; };
	//�����蔻��L���̃Q�b�^�[
	bool Getter_is_collision()const { return is_collision_; };
	//���������G�̃A�h���Xlist�̃Q�b�^�[
	std::list<EnemyBase*>& Getter_hiteneaddress() { return hiteneaddress_; };
	//�m�b�N�o�b�N�l�̃Q�b�^�[
	float Getter_knockback_value_()const { return knockback_value_; };
};