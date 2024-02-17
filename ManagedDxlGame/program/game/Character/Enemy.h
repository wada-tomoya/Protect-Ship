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
	//実行関数
	void Update(float delta_time) override;
};