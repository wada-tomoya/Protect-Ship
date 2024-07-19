#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../Object/Attack/NormalAttack.h"
#include "../Object/Attack/BombAttack.h"

struct ATTACK;
class Camera;

class AttackManager {
public:
	//各攻撃の実行関数
	void Attack_Update(float delta_time, std::list<std::shared_ptr<AttackBase>>& attacks);
	//各攻撃の表示関数
	void Attack_Draw(std::shared_ptr<Camera>& camera, std::list<std::shared_ptr<AttackBase>>& attacks, const ATTACK& normalatk);

	//攻撃生成関数 playerがこの関数を呼ぶことで攻撃が生成される
	//引数（攻撃の初期座標、進行方向の座標、移動速度上がり幅、攻撃上がり幅、貫通力上がり幅、
	// 攻撃のlist、通常攻撃の情報、
	// マップの中心、マップの半径、テクスチャの番号, 複製メッシュのサイズスケール）
	void NormalAttack_Create(tnl::Vector3 spwan_pos, tnl::Quaternion dir_angle, float speed, float power, int Penetration_,
		std::list<std::shared_ptr<AttackBase>>& attacks, const ATTACK& normalatk,
		const tnl::Vector3& atk_map_center, const float& atk_map_rad, int texturenum, float size_scale);

	//引数（攻撃の初期座標、進行方向の座標、生成時のマウスレイの座標、
	// 攻撃のlist、爆破攻撃の情報、マップの中心、マップの半径、テクスチャの番号）
	void BombAttack_Create(tnl::Vector3 spawn_pos, tnl::Quaternion dir_angle, tnl::Vector3 target_pos,
		std::list<std::shared_ptr<AttackBase>>& attacks, const ATTACK& bombatk, const tnl::Vector3& atk_map_center,
		const float& atk_map_rad, int texturenum);
};
