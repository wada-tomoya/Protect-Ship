#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "ItemSpawner.h"

class Camera;
class EnemyBase;
class Player;
class ProtectObject;

//敵
struct ENEMY {
	//敵の複製元モデル
	int model_hdl_ = 0;
	//敵のサイズ
	DxLib::VECTOR scale_ = { 0.3f,0.3f,0.3f };
	//移動速度
	float speed_ = 0.0f;
	//体力
	float hp_ = 0.0f;
	//モデルの元のサイズ
	const tnl::Vector3 size_{ 100,310,100 };
	//弾との当たり判定用半径
	float colli_rad_ = 0.0f;
	//プレイヤーとの当たり判定用サイズ
	tnl::Vector3 colli_size_{35,50,35};

	//スポンする間隔
	float spawn_count_ = 0.0f, spawn_interval_ = 0.0f;
	//最低スポン間隔
	float spawn_interval_low_ = 0.1f;
};

//敵の種類
enum class ENEMYTYPE {
	normal,
	chase,
	big,
	max
};

class Spawner : public ItemSpawner {
private:
	//敵のターゲット
	std::weak_ptr<ProtectObject> target_protectobj_;
	std::weak_ptr<Player> target_player_;

	//通常敵
	ENEMY normal_enemy_;
	//プレイヤーを追いかける敵
	ENEMY enemy_chase_;
	//大きい敵
	ENEMY big_enemy_;

	//複製する最大数
	const int duplicate_max_ = 1000;
	//複製カウント
	int duplicate_count_ = 0;

	//複製元影のメッシュ
	Shared<dxe::Mesh> shadow_mesh_ = nullptr;
	//インスタンシングメッシュプール
	Shared<dxe::InstMeshPool> shadow_mesh_pool_ = nullptr;
	//影のテクスチャ配列
	std::vector<Shared<dxe::Texture>> shadow_textures_;
	//90度倒す
	tnl::Quaternion shadow_down_ = tnl::Quaternion::RotationAxis({ 1,0,0 }, tnl::ToRadian(90));
	//影のy座標
	const float shadow_pos_y_ = 3.0f;

	//テクスチャのvector
	std::vector<Shared<dxe::Texture>> enemy1_textures_;

	//敵のlist
	std::list<std::shared_ptr<EnemyBase>> enemys_;

	//マップの中心座標
	tnl::Vector3 map_center_{ 0,0,0 };
	//マップの半径
	float map_rad_ = 0.0f;

	//ランダムな角度（生成方向）
	float rad_ = 0.0f;

	//アイテムの生成確立
	//要素 0.none 1.itemred 2.itemblue 3.itemgreen 4.itembomb
	int itemprob_[5]{50,10,10,10,20};

public:
	Spawner() = default;

	//引数１：プレイエリアの中心、２：プレイエリアの半径、３：ターゲット（船）、４：ターゲット（プレイヤー））
	Spawner(const tnl::Vector3& map_center, const float& map_rad, const std::shared_ptr<ProtectObject>& target_protectobj, const std::shared_ptr<Player>& target_player);
	~Spawner();
	
	//実行
	//引数１：時間
	void Update(const float& delta_time);
	//表示
	//引数１：カメラインスタンス
	void Draw(const std::shared_ptr<Camera>& camera);
	
	//敵生成
	//引数：１船インスタンス、２：プレイヤーインスタンス、３：時間
	void Enemy_Spawn(std::weak_ptr<ProtectObject> protectobject, std::weak_ptr<Player> player, const float& delta_time);
	
	//通常敵スポン間隔、スポン時のステータス変更
	//引数１：敵の種類、　引数２：減算値スポンインターバル、　引数３：加算値hp、　引数４：加算値スピード
	void Enemy_SpawnStatusChange(const ENEMYTYPE& enemytype, const float& sub_spawn_interval, const float& add_hp, const float& add_speed);
	
	//敵複製、初期位置に移動、サイズ変更
	//引数１：複製元モデル、２：サイズスケール
	int EnemyDupe(const int& model_hdl, const DxLib::VECTOR& scale);	
	
	//影複製
	//引数１：複製元影モデル
	Shared<dxe::InstMesh> ShadowDupe(const int& enedupe);
	 
//ゲッター、セッター

	//listのゲッター
	std::list< std::shared_ptr<EnemyBase>>& Getter_enemy_list() { return enemys_; };
};