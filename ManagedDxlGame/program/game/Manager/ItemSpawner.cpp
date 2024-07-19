#include "ItemSpawner.h"
#include "../Object/Item/ItemRed.h"
#include "../Object/Item/ItemBlue.h"
#include "../Object/Item/ItemGreen.h"
#include "../Object/Item/ItemBomb.h"
#include "random"
#include "../Object/Camera.h"
#include "../Manager/ResourceManager.h"

ItemSpawner::ItemSpawner(){
	//アイテム赤設定
	itemred_.origine_mesh_ = ResourceManager::GetInstance_ResourceManager()->LoadMV1Model_("ITEMRED");
	itemred_.itemtype_ = ITEMTYPE::Red;

	//アイテム青設定
	itemblue_.origine_mesh_ = ResourceManager::GetInstance_ResourceManager()->LoadMV1Model_("ITEMBLUE");
	itemblue_.itemtype_ = ITEMTYPE::Blue;

	//アイテム緑設定
	itemgreen_.origine_mesh_ = ResourceManager::GetInstance_ResourceManager()->LoadMV1Model_("ITEMGREEN");
	itemgreen_.itemtype_ = ITEMTYPE::Green;

	//アイテム爆弾設定
	itembomb_.origine_mesh_ = ResourceManager::GetInstance_ResourceManager()->LoadMV1Model_("ITEMBOMB");
	itembomb_.itemtype_ = ITEMTYPE::Bomb;
	
}

ItemSpawner::~ItemSpawner() {

}

void ItemSpawner::ItemUpdate(float delta_time){
	//アイテムの実行と消去
	auto it = items_.begin();
	while (it != items_.end()) {
		//実行
		(*it)->Update(delta_time);

		//is_alive_がfalseならば消去
		if (!(*it)->Getter_is_alive()) {
			it = items_.erase(it);
			continue;
		}

		it++;
	}

}

void ItemSpawner::ItemDraw(Shared<dxe::Camera> camera){
	//アイテム描画
	auto it = items_.begin();
	while (it != items_.end()) {
		(*it)->Draw(camera);

		it++;
	}
}

void ItemSpawner::CreateItem(Item type, tnl::Vector3 pos) {
	//引数の種類を取得
	int itemtype = static_cast<int>(type.itemtype_);

	int duplired = 0;
	int dupliblue = 0;
	int dupligreen = 0;
	int duplibomb = 0;

	switch (itemtype) {
		//種類がnoneだった場合
	case static_cast<int>(ITEMTYPE::None):
		return;
		break;

		//種類が赤だった場合
	case static_cast<int>(ITEMTYPE::Red):
		//モデル複製
		duplired = ItemDupe(itemred_.origine_mesh_, pos);
		//アイテム生成、listに挿入
		items_.emplace_back(std::make_shared<ItemRed>(duplired));
		break;

		//種類が青だった場合
	case static_cast<int>(ITEMTYPE::Blue):
		//モデル複製
		dupliblue = ItemDupe(itemblue_.origine_mesh_, pos);
		//アイテム生成、listに挿入
		items_.emplace_back(std::make_shared<ItemBlue>(dupliblue));
		break;

		//種類が緑だった場合
	case static_cast<int>(ITEMTYPE::Green):
		//モデル複製
		dupligreen = ItemDupe(itemgreen_.origine_mesh_, pos);
		//アイテム生成、listに挿入
		items_.emplace_back(std::make_shared<ItemGreen>(dupligreen));
		break;

		//種類が爆弾だった場合
	case static_cast<int>(ITEMTYPE::Bomb):
		//モデル複製
		duplibomb = ItemDupe(itembomb_.origine_mesh_, pos);
		//アイテム生成、listに挿入
		items_.emplace_back(std::make_shared<ItemBomb>(duplibomb));
		break;
	}
}

Item ItemSpawner::Item_Lottery(int none, int probred, int probblue, int probgreen, int probbomb){
	//確率の合計
	int num = none + probred + probblue + probgreen + probbomb;
	//ランダム値の器
	std::random_device rd;
	std::mt19937 gen(rd());
	//ランダム値の幅
	std::uniform_int_distribution<> dis(0, num);
	//ランダムな値
	int randnum = static_cast<int>(dis(gen));

	//各区切り
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
	//複製
	int dupli = MV1DuplicateModel(origine_hdl);
	//座標セット
	MV1SetPosition(dupli,VGet(pos.x,10.0f,pos.z));

	return dupli;
}
