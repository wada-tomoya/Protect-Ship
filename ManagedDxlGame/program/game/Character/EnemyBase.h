#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class EnemyBase {
protected:
	//敵の生死
	bool is_alive_ = true;
	//座標
	tnl::Vector3 pos_{ 0,0,0 };
	tnl::Vector3 target_pos_{ 0,0,0 };
	//移動速度
	float speed_ = 0.0f;
	//移動方向
	tnl::Vector3 move_dir_{ 0,0,0 };
	//当たり判定用の半径
	float rad_ = 0.0f;

	//複製されたメッシュ
	Shared<dxe::InstMesh> inst_mesh_;

public:
	//実行関数
	virtual void Update(float delat_time) {};
	
	//is_alive_のゲッター　
	virtual bool Getter_is_alive() { return is_alive_; };
	//is_alive_のセッター
	virtual void Setter_is_alive(bool is_alive) { is_alive_ = (is_alive = true) ? true : false; };
	//座標のゲッター
	virtual tnl::Vector3 Getter_pos_() { return inst_mesh_->getPosition(); };
	//半径のゲッター
	virtual float Getter_rad_() { return rad_; };
};
