#pragma once
#include "../../../dxlib_ext/dxlib_ext.h"

class Camera;

class Play_Map {
private:
	//地面関係

	//地面の画像ハンドル
	Shared<dxe::Texture> ground_texture_;
	//地面画像のメッシュ
	Shared<dxe::Mesh> ground_mesh_ = nullptr;
	//地面の中心
	const tnl::Vector3 ground_center_ = { 0,0,0 };
	//地面画像のサイズ
	const tnl::Vector3 ground_scale_{ 5000.0f,5.0f,5000.0f };

//---------------------------------------------------------------------------
	//木関係

	//木のmv1モデル 複製元
	int tree_mhdl_ = 0;
	//複製する木の最大数
	static const int tree_duplicate_max_ = 2000;
	//木複製モデルの配列
	std::vector<int> tree_duplicate_hdl_;
	//木のy座標
	const float tree_pos_y_ = 150.0;
	//木のサイズ
	const DxLib::VECTOR tree_size_ = { 0.3f,0.3f,0.3f };
	//木の生成間隔
	const float tree_spawn_distance_ = 90.0f;
	//生成位置を少しずらす値
	//-shift_から+shiftまで
	const int shift_x_ = 30;
	const int shift_z_ = 30;

//---------------------------------------------------------------------------
	//プレイヤー移動範囲円関係

	//プレイヤーの移動限界の座標の中心、円状
	tnl::Vector3 player_move_center = { 0,0,0 };
	//プレイヤーの移動限界の座標の半径
	const float player_move_rad_ = 1000.0f;
	//プレイヤーの移動限界の中心からの長さ　ベクトル
	const float player_move_vec_ = static_cast<float>(pow(player_move_rad_, 2));

	//プレイエリアを可視化する円関係
	Shared<dxe::Mesh> player_map = nullptr;
	Shared<dxe::Texture> player_map_tex = nullptr;
	//円と地面との距離
	const float circle_pos_y_ = 10.0f;

//---------------------------------------------------------------------------

	//マウスカーソルのレイとの当たり判定用のbox
	//ボックスサイズ
	const float ray_box_size_ = 1.0f;

public:
	Play_Map();
	~Play_Map();
	//マップ表示
	//引数１：カメラインスタンス
	void Map_Draw(const std::shared_ptr<Camera>& camera);

//ゲッター、セッター

	//プレイヤーの移動限界の中心座標のゲッター
	tnl::Vector3 Getter_Playmap_Center()const {
		return player_move_center;
	};
	//プレイヤーの移動限界の半径のゲッター
	float Getter_Playmap_Rad()const {
		return player_move_rad_;
	}
	//地面のメッシュのゲッター
	Shared<dxe::Mesh> Getter_Ground()const {return ground_mesh_; };
};
