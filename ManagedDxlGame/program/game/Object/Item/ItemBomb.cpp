#include "ItemBomb.h"
#include "../../Object/Camera.h"

ItemBomb::ItemBomb(int& mv1model) : ItemBase(mv1model){
	//�^�C�v�ݒ�
	itemtype_ = ITEMTYPE::Bomb;
}

ItemBomb::~ItemBomb(){

}

void ItemBomb::Update(float delta_time){
	__super::Update(delta_time);
}
