#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../Manager/ResourceManager.h"
#include "../Camera.h"

class Play_Map {
private:
	//地面の画像ハンドル
	Shared<dxe::Texture> ground_texture_;
	//地面画像のメッシュ
	Shared<dxe::Mesh> ground_mesh_ = nullptr;
	//地面の中心
	tnl::Vector3 ground_center_ = { 0,0,0 };
	//地面画像のサイズ
	tnl::Vector3 ground_size_{3000,3000,0};

//---------------------------------------------------------------------------

	//木のmv1モデル 複製元
	int tree_mhdl_ = 0;
	//複製する木の最大数
	static const int tree_duplicate_max_ = 2000;
	//木複製モデルの配列
	std::vector<int> tree_duplicate_hdl_;
	//木のy座標
	float tree_pos_y_ = 150.0;
	//木のサイズ
	const DxLib::VECTOR tree_size_ = { 0.3f,0.3f,0.3f };
	//木の生成間隔
	float tree_spwan_distance_ = 90.0f;

//---------------------------------------------------------------------------

	//プレイヤーの移動限界の座標の中心、円状
	tnl::Vector3 player_move_center = { 0,0,0 };
	//プレイヤーの移動限界の座標の半径
	float player_move_rad_ = 1000.0f;
	//プレイヤーの移動限界の中心からの長さ　ベクトル
	float player_move_vec_ = player_move_rad_ * player_move_rad_;

	//プレイエリアを可視化する円
	Shared<dxe::Mesh> player_map = nullptr;
	Shared<dxe::Texture> player_map_tex = nullptr;

public:
	Play_Map();
	~Play_Map();
	//マップ表示
	void Map_Draw(std::shared_ptr<Camera> camera);
	//プレイヤーの移動限界の中心座標のゲッター
	tnl::Vector3 Getter_Playmap_Center() {
		return player_move_center;
	};
	//プレイヤーの移動限界の半径のゲッター
	float Getter_Playmap_Rad() {
		return player_move_rad_;
	}
};
