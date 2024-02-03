#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Manager/ResourceManager.h"
#include "Camera.h"

class ProtectObject {
private:
	//表示座標
	tnl::Vector3 pos_{940,600,0};
	//画像ハンドル
	std::shared_ptr<std::vector<int>> anim_hdl_;

	//アニメーション再生のカウント
	float anim_time_ = 0.0f;
	//再生するフレーム
	int anim_frame_ = 0;
	//アニメーションの再生速度
	float anim_speed_ = 0.1f;
public:
	ProtectObject();
	//表示関数
	void Draw(float delta_time, const Camera& camera);
	//座標ゲッター
	tnl::Vector3 GetterPos();
};