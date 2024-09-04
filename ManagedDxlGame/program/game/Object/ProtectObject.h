#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

class Camera;

class ProtectObject {
private:
	//�T�C�Y
	const tnl::Vector3 size_{ 64,64,0 };
	//�\�����W
	tnl::Vector3 pos_{0,0,0};
	//�e�N�X�`��
	Shared<dxe::Texture> texture_;
	//���b�V��
	Shared<dxe::Mesh> mesh_ = nullptr;

	//�p�[�e�B�N��
	Shared<dxe::Particle> smoke_ = nullptr;

	//�ϋv�l�i�̗́j
	float hp_ = 100.0f;
	//�����ϋv�l
	float init_hp_ = hp_;
	//�c��hp�̊���
	float hp_ratio_ = 0.0f;
	//���p�[�e�B�N�����o��̗͂̊���
	const float smoke_gene_hp_ = 0.5f;
	//�����t���O
	bool is_alive_ = true;
public:
	ProtectObject();
	~ProtectObject();
	//���s�֐�
	//�����P�F����
	void Update(const float& delta_time);
	//�\���֐�
	//�����P�F�J�����C���X�^���X
	void Draw(const std::shared_ptr<Camera>& camera);

//�Q�b�^�[�A�Z�b�^�[

	//���W�Q�b�^�[
	tnl::Vector3 GetterPos()const { return pos_; };
	//hp�̃Q�b�^�[
	float Getter_Hp()const { return hp_; };
	//hp�̎Q�ƃQ�b�^�[
	const float& Geter_address_hp()const { return hp_; };
	//hp�̃Z�b�^�[
	void Setter_Hp(float damage) { hp_ += damage; };
	//���W�Z�b�^�[
	void Setter_pos(tnl::Vector3 pos) { pos_ += pos; };
};