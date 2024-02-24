#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "math.h"
#include "AttackBase.h"

class NormalAttack : public AttackBase{
private:	
	//1フレームの回転角度
	float angle_ = 10.0f;
	
public:		 
	//引数（マップの左上、マップの右下、生成する座標、進行方向の座標、複製されたメッシュ）
	NormalAttack(const tnl::Vector3 map_upleft, const tnl::Vector3 map_lowright, 
		const tnl::Vector3& spawn_pos, const tnl::Vector3 target_pos, Shared<dxe::InstMesh> inst_mesh);
	//実行関数
	void Update(float delta_time) override;
	//攻撃の消去 is_aliveをfalseにする
	void Delete();
	//is_alive_のゲッター
	bool Getter_is_alive() override { return is_alive_; };
	//is_alive_のセッター
	void Setter_is_alive(bool is_alive) override { is_alive_ = (is_alive == true) ? true : false; };
	//座標のゲッター
	const tnl::Vector3& Getter_pos_() const override { return inst_mesh_->getPosition(); };
	//半径のゲッター
	const float& Getter_rad_() const override { return rad_; };
};
