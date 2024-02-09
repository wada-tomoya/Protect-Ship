#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../Manager/ResourceManager.h"
#include "../Camera.h"
#include "Block.h"

class Play_Map {
private:
	//マップチップ関係
	//ブロック表示場所のcsvデータ
	std::vector<std::vector<int>> mapchip_csv_;
	//ブロック画像ハンドル
	std::shared_ptr<std::vector<int>> mapchip_hdl_;

	//背景の画像ハンドル
	int background_hdl_ = 0;
	//背景の座標
	tnl::Vector3 bg_pos_ = { 0,0,0 };
	//マップの左上と右下の座標
	tnl::Vector3 map_upleft_ = { 0,0,0 }, map_lowright_ = {0,0,0};
	//地面の位置　y座標
	float ground_ = 0.0f;

public:
	static Play_Map* GetInstance_PlayMap();

	Play_Map();
	//背景表示
	void Background_Draw(std::shared_ptr<Camera> camera);
	//マップチップ表示
	void MapChip_Draw(std::shared_ptr<Camera> camera);

	//マップの左上座標と右下座標のGetter
	//引数 upleftなら左上の数値、lowrightなら右下の数値を返す 
	tnl::Vector3 MapEdge_Getter(std::string s);
	//地面の位置を返すGetter
	float Groundpos_Getter();

	//マップチップのlist
	std::list<std::shared_ptr<Block>> blocks_;
};
