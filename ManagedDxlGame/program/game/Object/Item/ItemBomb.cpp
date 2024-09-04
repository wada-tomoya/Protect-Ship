#include "ItemBomb.h"
#include "../../Object/Camera.h"

ItemBomb::ItemBomb(const int& mv1model) : ItemBase(mv1model){
	//É^ÉCÉvê›íË
	itemtype_ = ITEMTYPE::Bomb;
}

ItemBomb::~ItemBomb(){

}

void ItemBomb::Update(const float& delta_time){
	__super::Update(delta_time);
}
