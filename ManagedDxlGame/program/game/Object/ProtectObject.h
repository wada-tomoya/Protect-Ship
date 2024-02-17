#pragma once
#include "../dxlib_ext/dxlib_ext.h"
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

public:
	ProtectObject();
	//表示関数
	inline void Draw(std::shared_ptr<Camera> camera) {
		mesh_->render(camera);
	};
	//座標ゲッター
	tnl::Vector3 GetterPos();
};