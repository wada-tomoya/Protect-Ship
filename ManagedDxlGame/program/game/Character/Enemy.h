#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Object/Camera.h"
#include "CharacterBase.h"
#include "../Manager/ResourceManager.h"

class Enemy : public CharacterBase {
private:
	//アニメーション画像ハンドル
	std::shared_ptr<std::vector<int>> anim_hdl_;
	//ターゲットの座標
	tnl::Vector3 target_pos_ {0,0,0};
	//移動角度
	float angle_ = 0.0f;

public:
	//コンストラクタ
	//引数（ターゲットの座標、生成座標、移動スピード）
	Enemy(tnl::Vector3 target, tnl::Vector3 spon_pos, float speed);
	//実行関数
	void Update(float delta_time) override;
	//表示関数
	void Draw(float delta_time, std::shared_ptr<Camera> camera) override;
	//移動
	void Move(float delta_time);
};