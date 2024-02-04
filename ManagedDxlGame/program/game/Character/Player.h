#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Object/Camera.h"
#include "CharacterBase.h"
#include "../Object/Attack/NormalAttack.h"
#include "../Manager/ResourceManager.h"

class Player : public CharacterBase{
private:
	
 	//攻撃方向の座標（マウス座標）
	int mposx = 0, mposy = 0;
	//攻撃の移動速度
	float attack_speed_ = 10.0f;
	//画面の端
	float up_edge_, down_edge_, right_edge_, left_edge_;
//----------------------------------------------------------------------------
	//アニメーション画像ハンドル
	Shared<dxe::Texture> texture_hdl_right_;
	Shared<dxe::Texture> texture_hdl_left_;
	//メッシュ配列の要素数
	static const int mesh_index_ = 3;
	//メッシュ
	Shared<dxe::Mesh> mesh_right_[mesh_index_];
	Shared<dxe::Mesh> mesh_left_[mesh_index_];
	//テクスタ分割数
	const int texture_dir = 3; 

public:
	Player(float up_edge, float down_edge, float right_edge, float left_edge);
	//実行関数
	void Update(float delta_time) override;
	//表示関数
	void Draw(float delta_time, std::shared_ptr<Camera> camera) override;
	//移動
	void Move(float delta_time, float up_edge, float down_edge, float right_edge, float left_edge);
	//攻撃
	//void Attack(float delta_time);
	//プレイヤーの座標のゲッター
	tnl::Vector3 GetterPos();

	//生成した標準攻撃を入れるリスト
	//std::list<std::shared_ptr<NormalAttack>> normal_attacks_;	
};

