#include "ItemRed.h"
#include "../../Object/Camera.h"

ItemRed::ItemRed(const int& mv1model) : ItemBase(mv1model){
	//タイプ設定
	itemtype_ = ITEMTYPE::Red;
}

ItemRed::~ItemRed(){

}

void ItemRed::Update(const float& delta_time){
	__super::Update(delta_time);
}
