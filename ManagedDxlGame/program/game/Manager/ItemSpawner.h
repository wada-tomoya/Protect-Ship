#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../Object/Item/ItemBase.h"

class Camera;

struct Item {
	//複製元モデル
	int origine_mesh_ = 0;
	//サイズ
	float size = 10.0f;
	//アイテムの種類
	ITEMTYPE itemtype_ = ITEMTYPE::None;
};

class ItemSpawner {
protected:
	//アイテム　無し
	Item none_;
	//アイテム　赤
	Item itemred_;
	//アイテム　青
	Item itemblue_;
	//アイテム　緑
	Item itemgreen_;
	//アイテム　爆弾
	Item itembomb_;

	//アイテムリスト
	std::list<std::shared_ptr<ItemBase>> items_;
	
	//アイテム複製
	//引数１複製元モデル、引数２生成座標
	int ItemDupe(int origine_hdl, tnl::Vector3& pos);

public:
	ItemSpawner();
	~ItemSpawner();

	//アイテム実行
	void ItemUpdate(float delta_time);
	//描画関数
	void ItemDraw(Shared<dxe::Camera> camera);

	//アイテム生成
	//引数１アイテムの種類、引数２生成座標
	void CreateItem(Item type, tnl::Vector3 pos);

	//アイテム抽選
	//引数１noenの確率、引数２赤の確率、引数３青の確率、引数４緑の確率、引数５爆弾の確率
	Item Item_Lottery(int none, int probred, int probblue, int probgreen, int probbomb);

	//リストゲッター
	std::list<std::shared_ptr<ItemBase>>& Getter_Items() { return items_; };
};