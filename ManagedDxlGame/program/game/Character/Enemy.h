#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Object/Camera.h"
#include "EnemyBase.h"
#include "../Manager/ResourceManager.h"

//ProtectObjectに向かって進行する敵
//引数（ターゲットの座標、生成座標、移動スピード）
class Enemy : public EnemyBase {
private:
	//攻撃フラグ
	bool is_attack_ = false;

	//行動シーケンス
	TNL_CO_SEQUENCE(Enemy, &Enemy::move)
	//移動
	bool move(const float delta_time);
	//攻撃
	bool attack(const float delta_time);

public:
	//コンストラクタ
	//引数（ターゲットの座標、生成座標、移動スピード）
	Enemy(tnl::Vector3 target, tnl::Vector3 spawn_pos, Shared<dxe::InstMesh> inst_mesh);
	//消去
	void Delete() { is_alive_ = false; };
	//実行関数
	void Update(float delta_time, tnl::Vector3 player_pos = {0,0,0}) override;
	//is_alive_のゲッター　
	bool Getter_is_alive() override { return is_alive_; };
	//is_alive_のセッター
	void Setter_is_alive(bool is_alive) override { is_alive_ = (is_alive == true) ? true : false; };
	//座標のゲッター
	tnl::Vector3 Getter_pos_() override { return inst_mesh_->getPosition(); };
	//半径のゲッター
	float Getter_rad_() override { return rad_; };
};