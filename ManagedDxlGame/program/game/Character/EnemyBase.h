#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Object/Camera.h"

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

	//複製されたメッシュ
	Shared<dxe::InstMesh> inst_mesh_;

public:
	//実行関数
	virtual void Update(float delat_time) {};
	//消去
	virtual void Delete() { is_alive_ = false; };
	//is_alive_のゲッター
	virtual bool Getter_is_alive() { return is_alive_; };
};
