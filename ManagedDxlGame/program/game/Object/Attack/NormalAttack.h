#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "math.h"
#include "AttackBase.h"
#include "../Map/Play_Map.h"

class NormalAttack : public AttackBase{
private:	
	//初期座標
	tnl::Vector3 spawn_pos_{0,0,0};
	//ターゲットの座標（進行方向座標）
	int target_posx_ = 0, target_posy_ = 0;
	//弾の速度
	float speed_ = 5;
	//弾を発射する角度
	float angle_ = 0.0f;
	//弾の生死
	bool is_alive_ = true;

	//mapの端
	tnl::Vector3 upleft_{ 0,0,0 }, lowright_{0,0,0};

	//複製されたメッシュ
	Shared<dxe::InstMesh> inst_mesh_;

public:		
	NormalAttack(const tnl::Vector3& spawn_pos, const int& target_pos_x, const int& target_pos_y,
		Shared<dxe::InstMesh> inst_mesh);
	//実行関数
	void Update(float delta_time);
	//攻撃の消去 is_aliveをfalseにする
	void Delete();
	//is_alive_のゲッター
	bool Getter_is_alive();
};
