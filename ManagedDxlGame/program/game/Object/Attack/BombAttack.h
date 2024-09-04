#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include "AttackBase.h"

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
	float explosion_damage_ = 1000.0f;
	//爆破当たり判定サイズのパーティクルとの比率
	float explosion_size_ = 0.8f;

public:
	BombAttack() = default;

	//引数１：マップの中心、２：マップの半径、３：ターゲット（進行方向）の座標、４：生成座標、
	//５：進行方向の角度、６：複製されたメッシュ、７：攻撃の半径、
	//８：攻撃ヒット時のパーティクル、９：攻撃移動時のパーティクル、１０：攻撃ヒット時の音
	BombAttack(const tnl::Vector3& map_center, const float& map_rad, const tnl::Vector3& target_pos, const tnl::Vector3& spawn_pos,
		const tnl::Quaternion& dir_angle, const std::shared_ptr<dxe::InstMesh>& inst_mesh, const float& bullet_rad,
		const std::shared_ptr<dxe::Particle>& hit_ptcl, const std::shared_ptr<dxe::Particle>& move_ptcl, const int& hit_se);
	~BombAttack();

	//実行関数
	//引数１：時間
	void Update(const float& delta_time) override;
	//敵に当たった時の処理
	//引数１：当たった敵のアドレス
	void Enemy_Hit(EnemyBase* hiteneaddress = 0) override;
};