#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class AttackBase {
protected:
	//複製されたメッシュ
	Shared<dxe::InstMesh> inst_mesh_;
	//mapの端
	tnl::Vector3 upleft_{ 0,0,0 }, lowright_{ 0,0,0 };
	//初期座標
	tnl::Vector3 spawn_pos_{ 0,0,0 };
	//ターゲットの座標（進行方向座標）
	float target_posx_ = 0, target_posy_ = 0;
	//弾を発射する角度
	float angle_ = 0.0f;
	//弾の速度
	float speed_ = 0;
	//弾の生死
	bool is_alive_ = true;
	//当たり判定用の半径
	float rad_ = 0.0f;

public:
	//実行関数
	virtual void Update(float delta_time) {};
	//is_alive_のゲッター
	virtual bool Getter_is_alive() { return is_alive_; };
	//is_alive_のセッター
	virtual void Setter_is_alive(bool is_alive) { is_alive_ = (is_alive = true) ? true : false; };
	//座標のゲッター
	virtual const tnl::Vector3& Getter_pos_() const { return inst_mesh_->getPosition(); };
	//半径のゲッター
	virtual const float& Getter_rad_() const{ return rad_; };
};
