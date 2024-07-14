#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include "../../Object/Camera.h"
#include "../../Manager/ResourceManager.h"

enum class ITEMTYPE {
	Red,
	Blue,
	Green,
	Bomb,
	None
};

class ItemBase {
protected:
	//�����蔻��p���W
	tnl::Vector3 pos_{ 0,0,0 };
	//�����蔻��p�T�C�Y
	tnl::Vector3 size_ = {30,30,30};
	//��]�p�x
	float rotateangle_ = 0.05f;
	//�����W
	const float pos_y_ = 20.0f;
	//�X�P�[��
	const float  scale_ = 0.7f;

	//�����t���O
	bool is_alive_ = true;

	//���S�܂ł̎���
	float death_time_ = 8.0f, death_count_ = 0.0f;

	float heiget = 0.0f;
	float max = 10.0f;

	//�������ꂽ���f��
	int mv1model_ = 0;
	//�A�C�e���̎��
	ITEMTYPE itemtype_ = ITEMTYPE::None;

public:
	ItemBase(int mv1model);
	~ItemBase();

	//���s�֐�
	virtual void Update(float delta_time);
	//�`��֐�
	virtual void Draw(Shared<dxe::Camera> camera) {
		MV1DrawModel(mv1model_);
	};

	//���S
	void Delete() { is_alive_ = false; };
	//�v���C���[�Ɠ���������
	void PlyarHit();

	//���W�̃Q�b�^�[
	tnl::Vector3 Getter_pos()const { return pos_; };
	//�T�C�Y�̃Q�b�^�[
	tnl::Vector3 Getter_size()const { return size_; };
	//�����t���O�̃Q�b�^�[
	bool Getter_is_alive()const { return is_alive_; };
	//�A�C�e����ނ̃Q�b�^�[
	ITEMTYPE Getter_itemtype()const { return itemtype_; };
};