#include "ItemBlue.h"
#include "../../Object/Camera.h"

ItemBlue::ItemBlue(int& mv1model) : ItemBase(mv1model){
	//タイプ設定
	itemtype_ = ITEMTYPE::Blue;
}

ItemBlue::~ItemBlue(){

}
