#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../Manager/ResourceManager.h"
#include "../Camera.h"

class Play_Map {
private:
	//背景の画像ハンドル
	std::vector<Shared<dxe::Texture>> texture_;
	//背景画像のメッシュ
	Shared<dxe::Mesh> mesh_ = nullptr;
	//インスタンシングメッシュプール
	Shared<dxe::InstMeshPool> mesh_pool_ = nullptr;
	//インスタンシングメッシュlist
	std::list<Shared<dxe::InstMesh>> inst_meshs_;

	//背景の座標
	tnl::Vector3 bg_pos_ = { 0,0,0 };
	//マップの左上と右下の座標
	tnl::Vector3 map_upleft_ = { 0,0,0 }, map_lowright_ = {0,0,0};
	//プレイヤーの移動限界の座標
	tnl::Vector3 player_upleft_ = { 0,0,0 }, player_lowright_ = { 0,0,0 };
	//マップの中心座標
	tnl::Vector3 map_center_ = { 0,0,0 };

public:
	Play_Map();
	~Play_Map();
	//背景表示
	inline void Background_Draw(std::shared_ptr<Camera> camera) {
		//InstMeshPoolの描画
		dxe::DirectXRenderBegin();
		//背景描画
		mesh_pool_->render(camera);

		dxe::DirectXRenderEnd();
	};
	//マップの左上座標と右下座標のGetter
	//引数 upleftなら左上の数値、lowrightなら右下の数値を返す 
	const tnl::Vector3& MapEdge_Getter(std::string s) const;
	//playerの移動限界座標
	const tnl::Vector3& MapEdgePlsyer_Getter(std::string s) const;
};
