#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"

class Camera;

enum class ITEMTYPE {
	Red,
	Blue,
	Green,
	Bomb,
	None
};

class ItemBase {
protected:
	//当たり判定用座標
	tnl::Vector3 pos_{ 0,0,0 };
	//当たり判定用サイズ
	const tnl::Vector3 size_ = {30,30,30};
	//回転角度
	float rotateangle_ = 0.05f;
	//ｙ座標
	const float pos_y_ = 20.0f;
	//スケール
	const float  scale_ = 0.7f;

	//生死フラグ
	bool is_alive_ = true;

	//死亡までの時間
	float death_time_ = 8.0f, death_count_ = 0.0f;

	float heiget = 0.0f;
	float max = 10.0f;

	//複製されたモデル
	int mv1model_ = 0;
	//アイテムの種類
	ITEMTYPE itemtype_ = ITEMTYPE::None;

public:
	ItemBase() = default;

	//引数１：複製モデル
	ItemBase(const int& mv1model);
	~ItemBase();

	//実行関数
	//引数１：時間
	virtual void Update(const float& delta_time);
	//描画関数
	//引数１：カメラインスタンス
	virtual void Draw(const Shared<dxe::Camera>& camera) {
		MV1DrawModel(mv1model_);
	};

	//死亡
	void Delete() { is_alive_ = false; };
	//プレイヤーと当たった時
	void PlyarHit();

//ゲッター、セッター

	//座標のゲッター
	tnl::Vector3 Getter_pos()const { return pos_; };
	//サイズのゲッター
	tnl::Vector3 Getter_size()const { return size_; };
	//生死フラグのゲッター
	bool Getter_is_alive()const { return is_alive_; };
	//アイテム種類のゲッター
	ITEMTYPE Getter_itemtype()const { return itemtype_; };
};