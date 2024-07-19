#include "ItemSpawner.h"
#include "../Object/Item/ItemRed.h"
#include "../Object/Item/ItemBlue.h"
#include "../Object/Item/ItemGreen.h"
#include "../Object/Item/ItemBomb.h"
#include "random"
#include "../Object/Camera.h"
#include "../Manager/ResourceManager.h"

ItemSpawner::ItemSpawner(){
	//�A�C�e���Ԑݒ�
	itemred_.origine_mesh_ = ResourceManager::GetInstance_ResourceManager()->LoadMV1Model_("ITEMRED");
	itemred_.itemtype_ = ITEMTYPE::Red;

	//�A�C�e���ݒ�
	itemblue_.origine_mesh_ = ResourceManager::GetInstance_ResourceManager()->LoadMV1Model_("ITEMBLUE");
	itemblue_.itemtype_ = ITEMTYPE::Blue;

	//�A�C�e���ΐݒ�
	itemgreen_.origine_mesh_ = ResourceManager::GetInstance_ResourceManager()->LoadMV1Model_("ITEMGREEN");
	itemgreen_.itemtype_ = ITEMTYPE::Green;

	//�A�C�e�����e�ݒ�
	itembomb_.origine_mesh_ = ResourceManager::GetInstance_ResourceManager()->LoadMV1Model_("ITEMBOMB");
	itembomb_.itemtype_ = ITEMTYPE::Bomb;
	
}

ItemSpawner::~ItemSpawner() {

}

void ItemSpawner::ItemUpdate(float delta_time){
	//�A�C�e���̎��s�Ə���
	auto it = items_.begin();
	while (it != items_.end()) {
		//���s
		(*it)->Update(delta_time);

		//is_alive_��false�Ȃ�Ώ���
		if (!(*it)->Getter_is_alive()) {
			it = items_.erase(it);
			continue;
		}

		it++;
	}

}

void ItemSpawner::ItemDraw(Shared<dxe::Camera> camera){
	//�A�C�e���`��
	auto it = items_.begin();
	while (it != items_.end()) {
		(*it)->Draw(camera);

		it++;
	}
}

void ItemSpawner::CreateItem(Item type, tnl::Vector3 pos) {
	//�����̎�ނ��擾
	int itemtype = static_cast<int>(type.itemtype_);

	int duplired = 0;
	int dupliblue = 0;
	int dupligreen = 0;
	int duplibomb = 0;

	switch (itemtype) {
		//��ނ�none�������ꍇ
	case static_cast<int>(ITEMTYPE::None):
		return;
		break;

		//��ނ��Ԃ������ꍇ
	case static_cast<int>(ITEMTYPE::Red):
		//���f������
		duplired = ItemDupe(itemred_.origine_mesh_, pos);
		//�A�C�e�������Alist�ɑ}��
		items_.emplace_back(std::make_shared<ItemRed>(duplired));
		break;

		//��ނ��������ꍇ
	case static_cast<int>(ITEMTYPE::Blue):
		//���f������
		dupliblue = ItemDupe(itemblue_.origine_mesh_, pos);
		//�A�C�e�������Alist�ɑ}��
		items_.emplace_back(std::make_shared<ItemBlue>(dupliblue));
		break;

		//��ނ��΂������ꍇ
	case static_cast<int>(ITEMTYPE::Green):
		//���f������
		dupligreen = ItemDupe(itemgreen_.origine_mesh_, pos);
		//�A�C�e�������Alist�ɑ}��
		items_.emplace_back(std::make_shared<ItemGreen>(dupligreen));
		break;

		//��ނ����e�������ꍇ
	case static_cast<int>(ITEMTYPE::Bomb):
		//���f������
		duplibomb = ItemDupe(itembomb_.origine_mesh_, pos);
		//�A�C�e�������Alist�ɑ}��
		items_.emplace_back(std::make_shared<ItemBomb>(duplibomb));
		break;
	}
}

Item ItemSpawner::Item_Lottery(int none, int probred, int probblue, int probgreen, int probbomb){
	//�m���̍��v
	int num = none + probred + probblue + probgreen + probbomb;
	//�����_���l�̊�
	std::random_device rd;
	std::mt19937 gen(rd());
	//�����_���l�̕�
	std::uniform_int_distribution<> dis(0, num);
	//�����_���Ȓl
	int randnum = static_cast<int>(dis(gen));

	//�e��؂�
	int nonered = none + probred, noneredblue = nonered + probblue, noneredbluegree = noneredblue + probgreen;

	if (randnum <= none) {
		return none_;
	}
	else if (randnum > none && randnum <= nonered) {
		return itemred_;
	}
	else if (randnum > nonered && randnum <= noneredblue) {
		return itemblue_;
	}
	else if (randnum > noneredblue && randnum <= noneredbluegree) {
		return itemgreen_;
	}
	else if (randnum > noneredbluegree <= num) {
		return itembomb_;
	}
	else {
		return none_;
	}
}

int ItemSpawner::ItemDupe(int origine_hdl, tnl::Vector3& pos){
	//����
	int dupli = MV1DuplicateModel(origine_hdl);
	//���W�Z�b�g
	MV1SetPosition(dupli,VGet(pos.x,10.0f,pos.z));

	return dupli;
}
