#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../Manager/ResourceManager.h"
#include "Camera.h"

class ProtectObject {
private:
	//サイズ
	tnl::Vector3 size_{ 64,64,0 };
	//表示座標
	tnl::Vector3 pos_{0,0,0};
	//テクスチャ
	Shared<dxe::Texture> texture_;
	//メッシュ
	Shared<dxe::Mesh> mesh_ = nullptr;

	//パーティクル
	Shared<dxe::Particle> smoke_ = nullptr;

	//耐久値（体力）
	float hp_ = 100.0f;
	//初期耐久値
	float init_hp_ = hp_;
	//残りhpの割合
	float hp_ratio_ = 0.0f;
	//生死フラグ
	bool is_alive_ = true;
public:
	ProtectObject();
	~ProtectObject();
	//実行関数
	void Update(float delta_time);
	//表示関数
	void Draw(std::shared_ptr<Camera> camera);
	//座標ゲッター
	tnl::Vector3 GetterPos()const { return pos_; };
	//hpのゲッター
	float Getter_Hp()const { return hp_; };
	//hpの参照ゲッター
	const float& Geter_address_hp()const { return hp_; };
	//hpのセッター
	void Setter_Hp(float damage) { hp_ += damage; };
	//座標セッター
	void Setter_pos(tnl::Vector3 pos) { pos_ += pos; };
};