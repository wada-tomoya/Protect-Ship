#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "CharacterBase.h"
#include "../Manager/AttackManager.h"
#include "../Object/Item/ItemBase.h"

class Camera;

//引数（マップの移動限界の中心、移動限界の半径）
class Player : public CharacterBase, public AttackManager{
private:
//プレイヤー関係-------------------------------------------------------------------------------------

	//当たり判定用暑さ
	const float colli_thickness_ = 8.0f;
	//当たり判定の状態フラグ（true当たり判定有効、 false当たり判定無効）
	bool is_colli_ = true;
	//0以上なら無敵
	float invincible_ = 0.0f;
	//0以下なら攻撃できる
	float can_attack_ = 0.0f;
	//攻撃インターバルでの攻撃可能タイミング
	bool is_normalattack_ = true;
	//trueならプレイヤー表示
	bool is_flash_ = true;
	//無敵時間
	float invincible_time_ = 3.0f;
	//点滅間隔、点滅カウント
	float flash_interval_ = 0.25f, flash_count_ = 0.0f;
	//ダメージ時攻撃不能時間
	const float cooldown_time_ = 2.0f;

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
	
//影関係-------------------------------------------------------------------------------------

	//影のメッシュ
	Shared<dxe::Mesh> shadow_mesh_ = nullptr;
	//影のテクスチャ
	Shared<dxe::Texture> shadow_texture_ = nullptr;
	//90度倒す
	tnl::Quaternion shadow_down_ = tnl::Quaternion::RotationAxis({1,0,0}, tnl::ToRadian(90));
	//影のy座標
	const float shadow_pos_y_ = 0.1f;

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
	tnl::Quaternion cursor_down_ = tnl::Quaternion::RotationAxis({ 1,0,0 }, tnl::ToRadian(90));
	//マウスカーソルのレイと地面の当たった座標
	tnl::Vector3 ground_hit_pos_{ 0,0,0 };
	//ground_hit_pos_のパーティクル
	//Shared<dxe::Particle> attackcursor_ptcl_ = nullptr;

	//ステータスupのアイテムlist
	std::vector<ITEMTYPE> statusup_itemlist_;
	//アイテムlistの最大要素数
	const int itemmax_ = 5;
	//アイテムで変化するステータス
	struct ATTACKSTATUS {
		//攻撃移動速度
		float speed_attack_ = 0.0f;
		//生成間隔
		float interval_ = 0.0f;
		//攻撃力
		float power_ = 0.0f;
		//貫通力
		int Penetration_ = 0;
		//大きさ
		float size_scale_ = 1.0f;
		//プレイヤー移動速度
		float speed_player_ = 0.0f;
		//上がり幅
		float speed_attack_up_ = 5.0f;
		float interval_down_ = 0.07f;
		float power_up_ = 10.0f;
		int penetration_up_ = 1;
		float size_scale_up_ = 0.25f;
		float speed_player_up_ = 1.5f;
		//緑を取得している場合の攻撃力の減り幅
		float power_down_ = 1.7f;
	};
	ATTACKSTATUS itemupstatus_;
	const float little_up_ = 0.2f;

//-------------------------------------------------------------------------------------

	//マップの地面のメッシュ
	std::weak_ptr<dxe::Mesh> ground_;
	//カメラ
	std::weak_ptr<Camera> camera_;

public:
	Player() = default;

	//引数１：マップの中心座標、２：マップの半径、３：地面のメッシュ、４：カメラインスタンス
	Player(const tnl::Vector3& map_center, const float& map_rad, std::weak_ptr<dxe::Mesh> ground, std::weak_ptr<Camera> camera);
	~Player();
	//実行関数
	//引数１：時間
	void Update(const float& delta_time) override;
	//プレイヤーの描画関数
	//引数１：時間、２：カメラインスタンス
	void Draw(const float& delta_time, const std::shared_ptr<Camera>& camera) override;
	//攻撃の描画
	//引数１：カメラインスタンス
	void AttackDraw(const std::shared_ptr<Camera>& camera);

	//プレイヤー点滅
	//引数１：時間、２：点滅間隔
	void Flashing(const float& delta_tim, const float& flash_interval);
	//移動　
	//引数１：時間
	void Move(const float& delta_time);
	//画面の中心からマウスカーソルの方向へのベクトルを正規化した値
	tnl::Vector3 Cursor_Move_Norm_();
	//画面中心からマウスカーソルへの角度（度数法）
	float Angle_Center_Mouse();
	//攻撃
	//引数１：時間
	void Attack_Create(const float& delta_time);
	//敵と接触した時の処理
	void Enemy_Hit();
	//アイテムと接触した時の処理
	//引数１：アイテムの種類
	void Item_Hit(const ITEMTYPE& itemtype);
	//list内のアイテムを元に攻撃ステータス設定
	void AttackStatus_Set();

//ゲッター、セッター

	//ステータスupアイテムのセッター
	void Setter_Item(const ITEMTYPE& itemtype);
	//無敵状態フラグのゲッター
	bool Getter_is_colli()const { return is_colli_; };
	//描画フラグのゲッター
	bool Getter_is_flash_()const { return is_flash_; };
	//ステータスupのアイテムlistのゲッター
	std::vector<ITEMTYPE >& Getter_statusup_itemlist_() { return statusup_itemlist_; };
};

