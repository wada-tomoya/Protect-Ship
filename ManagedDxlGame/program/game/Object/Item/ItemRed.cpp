#include "ItemRed.h"
#include "../../Object/Camera.h"

ItemRed::ItemRed(const int& mv1model) : ItemBase(mv1model){
	//�^�C�v�ݒ�
	itemtype_ = ITEMTYPE::Red;
}

ItemRed::~ItemRed(){

}

void ItemRed::Update(const float& delta_time){
	__super::Update(delta_time);
}
