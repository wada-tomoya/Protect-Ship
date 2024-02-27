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
	tnl::Vector3 ground_size_{2000,2000,0};

	//プレイヤーの移動限界の座標の中心、円状
	tnl::Vector3 player_move_center = { 0,0,0 };
	//プレイヤーの移動限界の座標の半径
	float player_move_rad_ = 500.0f;

public:
	Play_Map();
	~Play_Map();
	//マップ表示
	void Map_Draw(std::shared_ptr<Camera> camera);
	//プレイヤーの移動限界の中心座標のゲッター
	tnl::Vector3 Getter_Player_Center() {
		return player_move_center;
	};
	//プレイヤーの移動限界の半径のゲッター
	float Getter_Player_Rad() {
		return player_move_rad_;
	}
};
