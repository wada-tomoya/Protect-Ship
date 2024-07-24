#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

class Camera;

class EnemyBase {
protected:
	//複製されたモデル
	int duplication_model_ = 0;
	//影のメッシュ
	Shared<dxe::InstMesh> shadow_mesh_ = nullptr;
	//ターゲットの座標
	tnl::Vector3 target_pos_{ 0,0,0 };
	//敵の生死
	bool is_alive_ = true;
	//サイズ
	tnl::Vector3 size_{ 0,0,0 };
	//移動速度
	float speed_ = 0.0f;
	//移動方向
	tnl::Vector3 move_dir_{ 0,0,0 };
	//移動前座標
	DxLib::VECTOR prev_pos_{ 0,0,0 };	
	//ターゲットとの距離
	float distance_target_ = 0.0f;
	//生成位置のマップ中心からの角度
	float spawn_angle_ = 0.0f;
	//攻撃のインターバル
	float attack_interval_ = 0.0f, attack_count_ = 0.0f;
	//攻撃力
	float attack_power_ = 1.0f;
	//体力
	float hp_ = 10.0f;

	//弾との当たり判定用の半径
	float colli_rad_ = 0.0f;
	//当たり判定用の球の中心座標
	tnl::Vector3 colli_center_{ 0,0,0 };
	//プレイヤーとの当たり判定用サイズ
	tnl::Vector3 colli_size_{};

	//進行方向更新インターバル
	float movedir_update_interval_ = 0.5f;
	float movedir_update_count_ = 0.0f;

	//攻撃に移るターゲットとの距離
	float trans_attack_distance_ = 50.0f;

	//プレイヤーの攻撃がヒット時のフラグ
	bool is_HitRecieve_ = false;

	//攻撃のse
	int attack_se_hdl_ = 0;
	//死亡した時のse
	int death_se_hdl_ = 0;
	//プレイヤーの攻撃がヒットした時のse
	int hit_se_hdl_ = 0;

	//死亡時のパーティクル
	std::shared_ptr<dxe::Particle> death_ptcl_ = nullptr;

	//アニメーションフラグ
	bool is_anim_ = true;
	//アニメーションが一周したフラグ
	bool is_anim_end_ = false;
	//アニメーション再生速度
	float anim_speed_ = 15.0f;
	//モデルのアニメーション総数
	int anim_num_ = 0;
	//アタッチ（再生）するアニメーション
	int anim_attachi_index_ = 0;
	//アタッチされているアニメーションの再生時間、アニメーションの再生カウント
	float anim_totaltime_ = 0.0f, anim_count_ = 0.0f;

	//アイテム生成フラグ
	bool is_itemspawn_ = true;
	
public:
	//コンストラクタ
	EnemyBase();
	~EnemyBase();

	//実行関数
	//引数１：時間
	virtual void Update(const float& delat_time);
	//描画関数
	//引数１：カメラインスタンス
	virtual void Draw(const std::shared_ptr<Camera>& camera);

	//死亡（消去）
	void Delete() { is_alive_ = false; };
	//進行方向の角度計算
	float Rotate_front();
	//ターゲットとの距離を計算
	float Distance_target();
	//移動方向更新
	//引数１：時間、移動方向更新間隔
	void Movedir_update(const float& delta_time, const float& movedir_update_interval = 0.0f);
	//プレイヤーの攻撃が当たった時
	//引数１：受けるダメージ
	virtual void PlyaerAttack_Recieve(const float& damage);
	//アニメーションの変更
	//引数１：アニメーションのタイプ
	void Anim_Change(const int& animtype);
	//アニメーション再生
	//引数１：時間
	void AnimPlay(const float& delta_time);

//ゲッター、セッター

	//is_alive_のゲッター　
	bool Getter_is_alive()const { return is_alive_; };
	//is_alive_のセッター
	void Setter_is_alive(bool is_alive) { is_alive_ = (is_alive = true) ? true : false; };
	//座標のゲッター
	tnl::Vector3 Getter_pos()const { 
		tnl::Vector3 pos = {0,0,0};
		pos.x = MV1GetPosition(duplication_model_).x;
		pos.y = MV1GetPosition(duplication_model_).y;
		pos.z = MV1GetPosition(duplication_model_).z;
		return pos; 
	};
	//hpのセッター
	void Setter_hp(const float& damage) { hp_ += damage; };
	//hpのゲッター
	float Getter_hp()const { return hp_; };
	//複製されたモデルハンドルのゲッター
	int Getter_dup_model()const { return duplication_model_; };
	//当たり判定用の半径のゲッター
	float Getter_colli_rad()const { return colli_rad_; };
	//弾との当たり判定用の球の中心座標のゲッター
	tnl::Vector3 Getter_colli_center()const { return colli_center_; };
	//プレイヤーとの当たり判定用サイズゲッター
	tnl::Vector3 Getter_colli_size()const { return colli_size_; };
	//攻撃力のゲッター
	float Getter_attack_power()const { return attack_power_; };
	//アイテム生成フラグのゲッター
	bool Getter_is_itemspawn()const { return is_itemspawn_; };
};
