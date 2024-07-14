#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include "math.h"
#include "AttackBase.h"

//引数（マップの中心、マップの半径、生成する座標、進行方向の角度、複製されたメッシュ, 弾の半径、敵に当たった時のパーティクル）
class BombAttack : public AttackBase {
private:
	//シーケンス
	TNL_CO_SEQUENCE(BombAttack, &BombAttack::SEQ_Move)
	//移動シーケンス
	bool SEQ_Move(const float delta_time);
	//ヒット（爆破）シーケンス
	bool SEQ_Hit(const float delta_time);
	//消去シーケンス
	bool SEQ_Death(const float delta_time);

	//爆破時のダメージ
	float explosion_damage_ = 30.0f;
	//爆破当たり判定サイズのパーティクルとの比率
	float explosion_size_ = 0.8f;

public:
	BombAttack(const tnl::Vector3 map_center, const float map_rad, tnl::Vector3 target_pos, const tnl::Vector3& spawn_pos,
		const tnl::Quaternion dir_angle, Shared<dxe::InstMesh> inst_mesh, float bullet_rad, 
		std::shared_ptr<dxe::Particle> hit_ptcl, std::shared_ptr<dxe::Particle> move_ptcl, int hit_se);
	~BombAttack();

	//実行関数
	void Update(float delta_time) override;
	//敵に当たった時の処理
	void Enemy_Hit() override;
};