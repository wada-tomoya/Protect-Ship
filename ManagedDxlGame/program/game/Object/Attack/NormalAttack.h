#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "math.h"
#include "../../Manager/ResourceManager.h"

class NormalAttack {
private:	
	//画像ハンドル
	int graph_hdl_ = 0;
	//画像のサイズ
	tnl::Vector3 attack_size_ = {0,0,0};
	//初期座標
	tnl::Vector3 spawn_pos_{0,0,0};
	//攻撃の進行方向（クリックした座標）
	int target_pos_x_ = 0, target_pos_y_ = 0;
	//弾の速度
	float speed_ = 0;
	//弾を発射する角度
	float angle_ = 0.0f;
	//弾の生死
	bool is_alive_ = true;

public:	
	NormalAttack(const tnl::Vector3& spawn_pos, const int& mouse_pos_x, const int& mouse_pos_y, const float& speed);
	//攻撃関数
	void Update(float delta_time);
	//攻撃の消去
	void Delete();
	//弾の表示
	void Draw(float delta_time);

};
