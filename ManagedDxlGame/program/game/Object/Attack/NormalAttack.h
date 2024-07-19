#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"
#include "AttackBase.h"

//引数（マップの中心、マップの半径、生成する座標、進行方向の角度、複製されたメッシュ, 
// 弾の半径、敵に当たった時のパーティクル、移動時のパーティクル、
//移動速度上がり幅、攻撃上がり幅、貫通力上がり幅）
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
	NormalAttack(const tnl::Vector3 map_center, const float map_rad,const tnl::Vector3& spawn_pos,
		const tnl::Quaternion dir_angle, std::shared_ptr<dxe::InstMesh>& inst_mesh, float bullet_rad,
		std::shared_ptr<dxe::Particle>& hit_ptcl, std::shared_ptr<dxe::Particle>& move_ptcl,
		float speed, float power, int Penetration_);
	~NormalAttack();

	//実行関数
	void Update(float delta_time) override;
	//敵に当たった時の処理
	void Enemy_Hit() override;
};
