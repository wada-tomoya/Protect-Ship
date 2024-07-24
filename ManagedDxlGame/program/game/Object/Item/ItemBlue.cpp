#include "ItemBlue.h"
#include "../../Object/Camera.h"

ItemBlue::ItemBlue(const int& mv1model) : ItemBase(mv1model){
	//É^ÉCÉvê›íË
	itemtype_ = ITEMTYPE::Blue;
}

ItemBlue::~ItemBlue(){

}

void ItemBlue::Update(const float& delta_time){
	__super::Update(delta_time);
}
