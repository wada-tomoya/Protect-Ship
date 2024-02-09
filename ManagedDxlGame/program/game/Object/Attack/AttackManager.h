#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Camera.h"
#include "NormalAttack.h"

struct NORMALATTACK {
	 //NormalAttackの複製元メッシュ
	 Shared<dxe::Mesh> origine_mesh_ = nullptr;
	 //NormalAttackのインスタンシングメッシュプール
	 Shared<dxe::InstMeshPool> mesh_pool_ = nullptr;
	 //テクスチャのvector
	 std::vector<Shared<dxe::Texture>> textures_;
	 //NormalAttackのlist
	 std::list<std::shared_ptr<NormalAttack>> normalattacks_;
	 //NormalAttackのサイズ
	 tnl::Vector3 size_ = { 16,16,0 };
	 //instmeshの複製最大数
	 int instmax_ = 100;
};

class AttackManager {
private:
	//通常攻撃
	NORMALATTACK noratk;

public:
	AttackManager();
	~AttackManager();
	//各攻撃の実行関数
	void Update(float delta_time);
	//各攻撃の表示関数
	void Draw(float delta_time, std::shared_ptr<Camera> camera);
	//NormalAttack生成関数 playerがこの関数を呼ぶことで攻撃が生成される
	//引数（攻撃の初期座標spown_pos、ターゲットのｘ y座標target_pos_x target_pos_y、）
	void NormalAttack_Create(tnl::Vector3 spwan_pos, int target_pos_x, int target_pos_y);
};
