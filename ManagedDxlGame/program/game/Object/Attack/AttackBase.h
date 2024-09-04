#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"

class Camera;
class EnemyBase;

class AttackBase {
protected:
	//マップの中心
	tnl::Vector3 map_center_{ 0,0,0 };
	//マップの半径
	float map_rad_ = 0.0f;
	//マップの中心から外周までのベクトル
	float map_vec_ = 0.0f;

	//複製されたメッシュ
	std::shared_ptr<dxe::InstMesh> inst_mesh_ = nullptr;
	//初期座標
	tnl::Vector3 spawn_pos_{ 0,0,0 };
	//弾の半径
	float bullet_rad_ = 0.0f;
	//ターゲットの座標（進行方向座標）
	float target_posx_ = 0, target_posy_ = 0;
	//進行方向の角度
	tnl::Quaternion dir_rad_ = tnl::Quaternion();
	//弾を発射する角度
	float angle_ = 0.0f;
	//弾の速度
	float speed_ = 0.0f;
	//弾の生死
	bool is_alive_ = true;
	//攻撃力
	float attack_power_ = 1.0f;

	//終着点の座標
	tnl::Vector3 end_pos_{ 0,0,0 };
	//初期座標から終着点まで長さ;
	float length_ = 0.0f;
	//山なりに動くようの高さ
	float heiget_ = 0.0f;
	//山なりに動くよう進んだ距離
	float traveled_ = 0.0f;
	//山なり移動の最大高
	float heiget_max_ = 0.0f;

	//当たり判定の有無
	bool is_collision_ = true;

	//ヒットした時のse
	int hit_se_hdl_ = 0;

	//敵と当たった時のパーティクル
	std::shared_ptr<dxe::Particle> hit_ptcl_ = nullptr;
	//攻撃移動時のパーティクル
	std::shared_ptr<dxe::Particle> move_ptcl_ = nullptr;
	//hit_ptcl_生成フラグ
	bool is_hit_ptcl_ = false;
	//hit_ptcl_生成時間
	float hit_ptcl_time_ = 0.0f;
	//hit_ptcl_生成カウント
	float hit_ptcl_count_ = 0.0f;

	//貫通力
	int penetration_ = 0;
	//当たった敵のアドレスのlist
	std::list<EnemyBase*> hiteneaddress_;

	//ノックバック値
	float knockback_value_ = 0.0f;

public:
	AttackBase() = default;

	//引数１：複製されたメッシュ、２：攻撃ヒット時のパーティクル、３：攻撃移動時のパーティクル
	//４：進行方向角度、５：マップの中心、６：マップの半径、７、攻撃の半径、８：攻撃生成座標
	AttackBase(const std::shared_ptr<dxe::InstMesh>& inst_mesh, const std::shared_ptr<dxe::Particle>& hit_ptcl, const std::shared_ptr<dxe::Particle>& move_ptcl,
		const tnl::Quaternion& dir_angle, const tnl::Vector3& map_center, const float& map_rad, const float& bullet_rad, const tnl::Vector3& spawn_pos);
	~AttackBase();

	//実行関数
	//引数１：時間
	virtual void Update(const float& delta_time) {};
	//消去までの実行関数
	//引数１：時間
	virtual void DeathUpdate(const float& delta_time) {};
	//パーティクル描画
	//引数１：カメラインスタンス
	void Draw_Ptcl(const std::shared_ptr<Camera>& camera);
	//敵に当たった時の処理
	//引数１：当たった敵のアドレス
	virtual void Enemy_Hit(EnemyBase* hiteneaddress = 0) {};
	//座標からマップの中心のベクトル計算
	float MapCenter_Vec();

//ゲッター、セッター
	
	//is_alive_のゲッター
	bool Getter_is_alive()const { return is_alive_; };
	//is_alive_のセッター;
	void Setter_is_alive(bool is_alive) { is_alive_ = is_alive; };
	//座標のゲッター
	tnl::Vector3 Getter_pos()const { 
		return inst_mesh_->getPosition(); };
	//サイズのゲッター
	tnl::Vector3 Getter_size()const { 
		return inst_mesh_->getScale(); };
	//半径のゲッター
	float Getter_bullet_rad()const { return bullet_rad_; };
	//攻撃力のゲッター
	float Getter_attack_power()const { return attack_power_; };
	//攻撃の消去 is_aliveをfalseにする
	void Delete() { is_alive_ = false; };
	//当たり判定有無のゲッター
	bool Getter_is_collision()const { return is_collision_; };
	//当たった敵のアドレスlistのゲッター
	std::list<EnemyBase*>& Getter_hiteneaddress() { return hiteneaddress_; };
	//ノックバック値のゲッター
	float Getter_knockback_value_()const { return knockback_value_; };
};