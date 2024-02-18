#include "ProtectObject.h"

ProtectObject::ProtectObject() {
	//テクスチャ　ロード
	texture_ = ResourceManager::GetInstance_ResourceManager()->LoadTexture_("PROTECTOBJECT");
	//メッシュ生成
	mesh_ = dxe::Mesh::CreatePlaneMV(size_, 1, 1);
	mesh_->setTexture(texture_);
	mesh_->setBlendMode(DX_BLENDMODE_ALPHA);
	mesh_->setSampleFilterMode(DX_DRAWMODE_NEAREST);
}

const tnl::Vector3& ProtectObject::GetterPos() const {
	return pos_;
}