#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Manager/ResourceManager.h"
#include "../Object/Camera.h"
#include "../Object/Map/Play_Map.h"
#include "../Character/Enemy.h"

//敵１
struct ENEMY_1 {
	//ENEMY_1複製元メッシュ
	Shared<dxe::Mesh> origine_mesh_ = nullptr;
	//ENEMY_1インスタンシングメッシュプール
	Shared<dxe::InstMeshPool> mesh_pool_ = nullptr;
	
};

class Spawner {
private:
	//テクスチャのvector
	std::vector<Shared<dxe::Texture>> texture_;
	//敵のlist
	std::list<std::shared_ptr<CharacterBase>> enemys_;
	//複製最大数
	int instmax_ = 1000;
	//敵１
	ENEMY_1 enemy1_;
	//マップの情報
	tnl::Vector3 map_upleft_{ 0,0,0 }, map_lowright_{ 0,0,0 };

public:
	Spawner(tnl::Vector3 map_upleft, tnl::Vector3 map_lowright);
	~Spawner();
};