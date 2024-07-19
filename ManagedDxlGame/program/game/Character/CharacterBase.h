#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../Object/Camera.h"

class AttackBase;

//通常攻撃
struct ATTACK {
	//複製元メッシュ
	Shared<dxe::Mesh> origine_mesh_ = nullptr;
	//インスタンシングメッシュプール
	Shared<dxe::InstMeshPool> mesh_pool_ = nullptr;
	//サイズ
	float size_ = 20.0f;
	//instmeshの複製最大数
	int instmax_ = 100;
	//攻撃ヒット時のパーティクル
	std::shared_ptr<dxe::Particle> hit_ptcl_;
	//移動時のパーティクル
	std::shared_ptr<dxe::Particle> move_ptcl_;
	//ヒット時のse
	int hit_se_hdl_ = 0;
};

class CharacterBase {
protected:
	
	//移動速度
	float speed_ = 0;
	//計算元移動速度
	float ori_speed_ = 0;
	//画像サイズ
	tnl::Vector3 size_{ 0,0,0 };
	//表示座標
	tnl::Vector3 pos_ { 0,0,0 };
	//移動前の座標
	tnl::Vector3 prev_pos_{ 0,0,0 };
	//左右反転フラグ
	bool isturn_ = false;
	//キャラクターの向き
	enum class DIRECTION {
		FRONT = 1,
		LEFT = 2,
		RIGHT = 3,
		BACK = 4
	};
	DIRECTION chara_dir_ = DIRECTION::RIGHT;
	//移動フラグ
	bool is_move_ = false;
	//アニメーション再生のカウント
	float anim_time_ = 0.0f;
	//再生するフレーム
	int anim_frame_ = 0;
	//アニメーションの再生速度
	float anim_speed_ = 0.1f;
	//表示するメッシュ配列インデックス
	int render_ = 1;
	//移動できるマップの中心
	tnl::Vector3 map_center_{ 0,0,0 };
	//移動できるマップの半径
	float map_rad_ = 0.0f;
	//マップの中央からの外周までの値の平方根
	float map_rad_root_ = 0.0f;

	//敵との当たり判定用のサイズ
	tnl::Vector3 colli_size_{ 0,0,0 };

	//攻撃関係--------------------------------------------------------------------------

	//通常攻撃
	ATTACK noratk_;
	//爆破攻撃
	ATTACK bomatk_;
	//テクスチャのvector
	std::vector<Shared<dxe::Texture>> atk_textures_;
	//テクスチャの配列番号
	enum class TEXTURENUM {
		normalattack,
		bombattack
	};

	//攻撃のlist
	std::list<std::shared_ptr<AttackBase>> attacks_;
	//計算元の通常攻撃の大きさ
	float ori_noratk_size_ = 0.0f;
	//通常攻撃の追加で出る数
	int attack_addnum_ = 0;
	//追加攻撃の出る角度
	const float addattack_rad_[5] = { 30,60,90,120,150 };
	//攻撃を有効にする範囲の中心の座標
	tnl::Vector3 attack_map_center_{ 0,0,0 };
	//攻撃を有効のする範囲の半径
	float attack_map_rad_ = 0.0f;
	//通常攻撃を出したときのse
	int attack_se_hdl_ = 0;
	//爆弾攻撃を出した時のse
	int bomattack_se_hdl_ = 0;
	//敵と当たった時のse
	int enemy_hit_se_hdl_ = 0;
	//敵と当たった時のパーティクル
	Shared<dxe::Particle> enemy_hit_ptcl_ = nullptr;
	//攻撃の移動速度
	float attack_speed_ = 10.0f;
	//攻撃インターバル
	float attack_interval_ = 0.5f;
	float attack_count_ = 0.0f;
	//計算用元のインターバル
	const float ori_attack_interval_ = attack_interval_;
	//計算用元の貫通力
	const int ori_attack_penetration_ = 0;
	//爆破攻撃のストック数
	int bombstock_ = 0;

public:


	//実行関数
	virtual void Update(float delat_time) {};
	//画像表示関数
	virtual void Draw(float delat_time, std::shared_ptr<Camera> camera) {};
	//アニメーション関数
	virtual void Anim_Play(std::shared_ptr<std::vector<int>> animhdl, float delta_time);
	//meshテクスチャ　アニメーション関数
	virtual void Texture_Anim_Play(int mesharray_index, float delta_time);
	//プレイヤーの座標のゲッター
	tnl::Vector3 GetterPos()const { return pos_; };
	//敵との当たり判定用のサイズのゲッター
	tnl::Vector3 Getter_colli_size_()const { return colli_size_; };

	//攻撃listのゲッター
	std::list<std::shared_ptr<AttackBase>>& Getter_Aattack_list() { return attacks_; };
	//爆弾ストックのゲッター
	const int& Getter_BombStock()const { return bombstock_; };
};