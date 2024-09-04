#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../Object/Item/ItemBase.h"

class Camera;

//アイテム構造体
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
	int ItemDupe(const int& origine_hdl, const tnl::Vector3& pos);

	//アイテム実行
	//引数１：時間
	void ItemUpdate(const float& delta_time);
	//描画関数
	//引数１：カメラインスタンス
	void ItemDraw(const Shared<dxe::Camera>& camera);

	//アイテム生成
	//引数１：アイテムの種類、引数２：生成座標
	void CreateItem(const Item& type, const tnl::Vector3& pos);

	//アイテム抽選
	//引数１：noenの確率、引数２：赤の確率、引数３：青の確率、引数４：緑の確率、引数５：爆弾の確率
	Item Item_Lottery(const int& none, const int& probred, const int& probblue, const int& probgreen, const int& probbomb);

public:
	ItemSpawner();
	~ItemSpawner();

//ゲッター、セッター

	//リストゲッター
	std::list<std::shared_ptr<ItemBase>>& Getter_Items() { return items_; };
};