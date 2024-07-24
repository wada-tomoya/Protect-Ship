#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../Object/Item/ItemBase.h"

class Camera;

//�A�C�e���\����
struct Item {
	//���������f��
	int origine_mesh_ = 0;
	//�T�C�Y
	float size = 10.0f;
	//�A�C�e���̎��
	ITEMTYPE itemtype_ = ITEMTYPE::None;
};

class ItemSpawner {
protected:
	//�A�C�e���@����
	Item none_;
	//�A�C�e���@��
	Item itemred_;
	//�A�C�e���@��
	Item itemblue_;
	//�A�C�e���@��
	Item itemgreen_;
	//�A�C�e���@���e
	Item itembomb_;

	//�A�C�e�����X�g
	std::list<std::shared_ptr<ItemBase>> items_;
	
	//�A�C�e������
	//�����P���������f���A�����Q�������W
	int ItemDupe(const int& origine_hdl, const tnl::Vector3& pos);

	//�A�C�e�����s
	//�����P�F����
	void ItemUpdate(const float& delta_time);
	//�`��֐�
	//�����P�F�J�����C���X�^���X
	void ItemDraw(const Shared<dxe::Camera>& camera);

	//�A�C�e������
	//�����P�F�A�C�e���̎�ށA�����Q�F�������W
	void CreateItem(const Item& type, const tnl::Vector3& pos);

	//�A�C�e�����I
	//�����P�Fnoen�̊m���A�����Q�F�Ԃ̊m���A�����R�F�̊m���A�����S�F�΂̊m���A�����T�F���e�̊m��
	Item Item_Lottery(const int& none, const int& probred, const int& probblue, const int& probgreen, const int& probbomb);

public:
	ItemSpawner();
	~ItemSpawner();

//�Q�b�^�[�A�Z�b�^�[

	//���X�g�Q�b�^�[
	std::list<std::shared_ptr<ItemBase>>& Getter_Items() { return items_; };
};