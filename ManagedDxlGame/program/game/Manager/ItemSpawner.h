#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../Object/Item/ItemBase.h"

class Camera;

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
	int ItemDupe(int origine_hdl, tnl::Vector3& pos);

public:
	ItemSpawner();
	~ItemSpawner();

	//�A�C�e�����s
	void ItemUpdate(float delta_time);
	//�`��֐�
	void ItemDraw(Shared<dxe::Camera> camera);

	//�A�C�e������
	//�����P�A�C�e���̎�ށA�����Q�������W
	void CreateItem(Item type, tnl::Vector3 pos);

	//�A�C�e�����I
	//�����Pnoen�̊m���A�����Q�Ԃ̊m���A�����R�̊m���A�����S�΂̊m���A�����T���e�̊m��
	Item Item_Lottery(int none, int probred, int probblue, int probgreen, int probbomb);

	//���X�g�Q�b�^�[
	std::list<std::shared_ptr<ItemBase>>& Getter_Items() { return items_; };
};