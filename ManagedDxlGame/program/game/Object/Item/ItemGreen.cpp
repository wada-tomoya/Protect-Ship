#include "ItemGreen.h"
#include "../../Object/Camera.h"

ItemGreen::ItemGreen(const int& mv1model) : ItemBase(mv1model){
	//�^�C�v�ݒ�
	itemtype_ = ITEMTYPE::Green;
}

ItemGreen::~ItemGreen(){

}

void ItemGreen::Update(const float& delta_time){
	__super::Update(delta_time);
}

