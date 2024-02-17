#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../../Manager/ResourceManager.h"
#include "../Camera.h"
#include "NormalAttack.h"
#include "../Map/Play_Map.h"

//通常攻撃
struct NORMALATTACK {
	 //NormalAttackの複製元メッシュ
	 Shared<dxe::Mesh> origine_mesh_ = nullptr;
	 //NormalAttackのインスタンシングメッシュプール
	 Shared<dxe::InstMeshPool> mesh_pool_ = nullptr;
	//NormalAttackのlist
	 std::list<std::shared_ptr<NormalAttack>> normalattacks_;
	 //NormalAttackの画像サイズ
	 tnl::Vector3 size_ = { 16,16,0 };
	 //instmeshの複製最大数
	 int instmax_ = 100;
};

class AttackManager {
private:
	//通常攻撃
	NORMALATTACK noratk;
	//マップ
	std::shared_ptr<Play_Map> map_ = nullptr;
	//テクスチャのvector
	std::vector<Shared<dxe::Texture>> textures_;

public:
	AttackManager();
	~AttackManager();
	//各攻撃の実行関数
	void Update(float delta_time);
	//各攻撃の表示関数
	inline void Draw(std::shared_ptr<Camera> camera) {
		//NormalAttackの表示
		noratk.mesh_pool_->render(camera);
	};
	//NormalAttack生成関数 playerがこの関数を呼ぶことで攻撃が生成される
	//引数（攻撃の初期座標、ターゲット座標）
	void NormalAttack_Create(tnl::Vector3 spwan_pos, tnl::Vector3 target_pos);
};
