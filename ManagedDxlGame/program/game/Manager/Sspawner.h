#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Manager/ResourceManager.h"
#include "../Object/Camera.h"
#include "../Character/Enemy.h"
#include "../Object/ProtectObject.h"

//敵１
struct ENEMY_1 {
	//ENEMY_1複製元メッシュ
	Shared<dxe::Mesh> origine_mesh_ = nullptr;
	//ENEMY_1インスタンシングメッシュプール
	Shared<dxe::InstMeshPool> mesh_pool_ = nullptr;
	//meshのサイズ
	tnl::Vector3 size_ = { 32,32,0 };
	//複製最大数
	int instmax_ = 500;
};

class Spawner {
private:
	//テクスチャのvector
	std::vector<Shared<dxe::Texture>> textures_;
	
	
	//敵１
	ENEMY_1 enemy1_;
	//マップの情報
	tnl::Vector3 map_upleft_{ 0,0,0 }, map_lowright_{ 0,0,0 };
	//マップのxの長さ
	unsigned int map_x_length_ = 0;
	//マップのyの長さ
	unsigned int map_y_length_ = 0;

	//ProtectObject敵の標的
	std::shared_ptr<ProtectObject> protectobject_ = nullptr;

	float time = 0;

public:
	//引数（マップの左上座標、右下座標）
	Spawner(tnl::Vector3 map_upleft, tnl::Vector3 map_lowright);
	~Spawner();
	void Destroy() { delete Instance_Spawner(); };
	static Spawner* Instance_Spawner(tnl::Vector3 map_upleft = { 0,0,0 }, tnl::Vector3 map_lowright = { 0,0,0 });
	//実行
	void Update(float delta_time);
	//表示
	inline void Draw(std::shared_ptr<Camera> camera) {
		//InstMeshPoolの描画
		dxe::DirectXRenderBegin();

		enemy1_.mesh_pool_->render(camera);
	
		dxe::DirectXRenderEnd();
	};
	//敵生成
	void Enemy_Spawn(tnl::Vector3 target_pos, float delta_time);
	
	//敵のlist
	std::list<std::shared_ptr<EnemyBase>> enemys_;
};