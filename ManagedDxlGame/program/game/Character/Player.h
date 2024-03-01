#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Object/Camera.h"
#include "CharacterBase.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/AttackManager.h"

//引数（マップの移動限界の中心、移動限界の半径）
class Player : public CharacterBase{
private:
	//マウスの座標
	tnl::Vector3 mouse_pos_ = {0,0,0};
	//攻撃の移動速度
	float attack_speed_ = 10.0f;
	//テクスチャ画像ハンドル
	Shared<dxe::Texture> texture_hdl_ = nullptr;
	//メッシュ配列の要素数
	static const int player_mesh_index_ = 3;
	//テクスチャ横分割数
	const int texture_div_ = 3; 
	//テクスチャ縦分割数
	const int texture_height_div_ = 4;
	//メッシュ
	Shared<dxe::Mesh> mesh_front_[player_mesh_index_];
	Shared<dxe::Mesh> mesh_left_[player_mesh_index_];
	Shared<dxe::Mesh> mesh_right_[player_mesh_index_];
	Shared<dxe::Mesh> mesh_back_[player_mesh_index_];
	
	//影のメッシュ
	Shared<dxe::Mesh> shadow_mesh_ = nullptr;
	//影のテクスチャ
	Shared<dxe::Texture> shadow_texture_ = nullptr;
	//90度倒す
	tnl::Quaternion shadow_down_ = tnl::Quaternion::RotationAxis({1,0,0}, tnl::ToRadian(90));
	//影のy座標
	const float shadow_pos_y_ = 0.0;
	

//-----------------------------------------------------------------

	//通常攻撃の発射方向を示すカーソルのMesh
	Shared<dxe::Mesh> cursor_mesh_ = nullptr;
	//カーソルのテクスチャ
	Shared<dxe::Texture> cursor_texture_;
	//カーソルとプレイヤーの距離
	float distance_cursor_player_ = 20.0f;
	//カーソルの角度
	tnl::Quaternion cursor_rad_ = tnl::Quaternion();
	//カーソルの座標
	tnl::Vector3 cursor_pos_{ 0,0,0 };
	//カーソルを90度傾けるよう
	tnl::Quaternion cursor_down_ = tnl::Quaternion::RotationAxis({ 0,0,1 }, tnl::ToRadian(90));

public:
	//引数（マップの移動限界の中心、半径）
	Player(tnl::Vector3 map_center = { 0,0,0 }, float map_rad = 500.0f);
	//実行関数
	void Update(float delta_time) override;
	//表示関数
	void Draw(float delta_time, std::shared_ptr<Camera> camera) override;
	//移動　
	//引数（delta_time, 移動出来るマップの中心、半径）
	void Move(float delta_time, tnl::Vector3 map_center);
	//画面の中心からマウスカーソルの方向へのベクトルを正規化した値
	tnl::Vector3 Cursor_Move_Norm_();
	//画面中心からマウスカーソルへの角度（度数法）
	float Angle_Center_Mouse();
	//攻撃
	void Normal_Attack();
	//プレイヤーの座標のゲッター
	tnl::Vector3 GetterPos();
};

