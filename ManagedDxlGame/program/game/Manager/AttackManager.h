#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../Object/Attack/NormalAttack.h"
#include "../Object/Attack/BombAttack.h"

struct ATTACK;
class Camera;

class AttackManager {
public:
	//各攻撃の実行関数
	//引数１：時間、２：攻撃のリスト
	void Attack_Update(const float& delta_time, std::list<std::shared_ptr<AttackBase>>& attacks);
	//各攻撃の表示関数
	//引数１：カメラインスタンス、２：攻撃のリスト、３：攻撃の構造体
	void Attack_Draw(const std::shared_ptr<Camera>& camera, const std::list<std::shared_ptr<AttackBase>>& attacks, const ATTACK& normalatk);

	//攻撃生成関数 playerがこの関数を呼ぶことで攻撃が生成される
	//引数１：攻撃の初期座標、２：進行方向の座標、３：移動速度上がり幅、４：攻撃上がり幅、５：貫通力上がり幅、
	// ６：攻撃のlist、７：通常攻撃の情報、
	// ８：マップの中心、９：マップの半径、１０：テクスチャの番号、１１：複製メッシュのサイズスケール
	void NormalAttack_Create(const tnl::Vector3& spwan_pos, const tnl::Quaternion& dir_angle, const float& speed, const float& power, const int& Penetration_,
		std::list<std::shared_ptr<AttackBase>>& attacks, const ATTACK& normalatk,
		const tnl::Vector3& atk_map_center, const float& atk_map_rad, const int& texturenum, const float& size_scale);

	//引数１：攻撃の初期座標、２：進行方向の座標、３：生成時のマウスレイの座標、
	// ４：攻撃のlist、５：爆破攻撃の情報、６：マップの中心、７：マップの半径、８：テクスチャの番号
	void BombAttack_Create(const tnl::Vector3& spawn_pos, const tnl::Quaternion& dir_angle, const tnl::Vector3& target_pos,
		std::list<std::shared_ptr<AttackBase>>& attacks, const ATTACK& bombatk, const tnl::Vector3& atk_map_center,
		const float& atk_map_rad, const int& texturenum);
};
