#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../Object/Camera.h"

class CharacterBase {
protected:
	
	//移動速度
	float speed_ = 0;
	//画像サイズ
	tnl::Vector3 size_{ 0,0,0 };
	//表示座標
	tnl::Vector3 pos_ { 0,0,0 };
	//左右反転フラグ
	bool isturn_ = false;
	//キャラクターの向き
	enum class DIRECTION {
		RIGHT,
		LEFT
	};
	DIRECTION chara_dir_ = DIRECTION::RIGHT;
	//アニメーション再生のカウント
	float anim_time_ = 0.0f;
	//再生するフレーム
	int anim_frame_ = 0;
	//アニメーションの再生速度
	float anim_speed_ = 0.1f;

	//表示するメッシュ配列インデックス
	int render_ = 0;

public:
	//実行関数
	virtual void Update(float delat_time) {};
	//画像表示関数
	virtual void Draw(float delat_time, std::shared_ptr<Camera> camera) {};
	//アニメーション再生関数
	virtual void Anim_Play(std::shared_ptr<std::vector<int>> animhdl, float delta_time);
	//meshテクスチャ　アニメーション
	virtual void Texture_Anim_Play(int texture_dir, float delta_time);
};