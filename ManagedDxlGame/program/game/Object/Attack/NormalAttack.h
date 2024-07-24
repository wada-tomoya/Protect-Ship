#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include "AttackBase.h"

class NormalAttack : public AttackBase{
private:	
	//回転角度
	const float rotate_angle_ = 10.0f;

	//シーケンス
	TNL_CO_SEQUENCE(NormalAttack, &NormalAttack::SEQ_Move)
	//移動シーケンス
	bool SEQ_Move(const float delta_time);
	//ヒットシーケンス
	bool SEQ_Hit(const float delta_time);
	//消去シーケンス
	bool SEQ_Death(const float delta_time);
	
public:		 
	NormalAttack() = default;

	//引数１：マップの中心、２：マップの半径、４：生成座標、５：進行方向の角度、
	//６：複製されたメッシュ、７：攻撃の半径、８：攻撃ヒット時のパーティクル、
	//９：攻撃移動時のパーティクル、１０：移動速度、１１：攻撃力、１２：貫通力
	NormalAttack(const tnl::Vector3& map_center, const float& map_rad, const tnl::Vector3& spawn_pos, const tnl::Quaternion& dir_angle,
		const std::shared_ptr<dxe::InstMesh>& inst_mesh, const float& bullet_rad, const std::shared_ptr<dxe::Particle>& hit_ptcl, 
		const std::shared_ptr<dxe::Particle>& move_ptcl, const float& speed, const float& power, const int& Penetration_);
	~NormalAttack();

	//実行関数
	//引数１：時間
	void Update(const float& delta_time) override;
	//敵に当たった時の処理
	//引数１：当たった敵のアドレス
	void Enemy_Hit(EnemyBase* hiteneaddress = 0) override;
};
