#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Object/Camera.h"
#include "CharacterBase.h"
#include "../Manager/ResourceManager.h"
#include "../Object/Attack/AttackManager.h"

class Player : public CharacterBase{
private:
	//マウスの座標
	tnl::Vector3 mouse_pos_ = {0,0,0};
	//攻撃の移動速度
	float attack_speed_ = 10.0f;
	//移動できる画面の端
	float up_edge_, down_edge_, right_edge_, left_edge_;

	//テクスチャ画像ハンドル
	Shared<dxe::Texture> texture_hdl_right_;
	Shared<dxe::Texture> texture_hdl_left_;
	//メッシュ配列の要素数
	static const int mesh_index_ = 3;
	//テクスチャ分割数
	const int texture_dir = 3; 
	//メッシュ
	Shared<dxe::Mesh> mesh_right_[mesh_index_];
	Shared<dxe::Mesh> mesh_left_[mesh_index_];

	//攻撃
	std::shared_ptr<AttackManager> attack_manager_ = nullptr;

public:
	//引数（マップの端の座標、地面の座標）
	Player(tnl::Vector3 upleft, tnl::Vector3 downright);
	//実行関数
	void Update(float delta_time) override;
	//表示関数
	void Draw(float delta_time, std::shared_ptr<Camera> camera) override;
	//移動　引数（delta_time, 移動出来るマップの左上、右下）
	void Move(float delta_time, float up_edge, float down_edge, float right_edge, float left_edge);
	//攻撃
	void Normal_Attack();
	//プレイヤーの座標のゲッター
	tnl::Vector3 GetterPos();
};

