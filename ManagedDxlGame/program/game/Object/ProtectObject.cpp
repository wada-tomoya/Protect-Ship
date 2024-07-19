#include "ProtectObject.h"
#include "../Manager/ResourceManager.h"
#include "Camera.h"

ProtectObject::ProtectObject() {
	//テクスチャ　ロード
	texture_ = ResourceManager::GetInstance_ResourceManager()->LoadTexture_("PROTECTOBJECT");
	//メッシュ生成
	mesh_ = dxe::Mesh::CreatePlaneMV(size_, 1, 1);
	mesh_->setTexture(texture_);
	mesh_->setBlendMode(DX_BLENDMODE_ALPHA);
	mesh_->setSampleFilterMode(DX_DRAWMODE_NEAREST);
	mesh_->pos_ = tnl::Vector3{ pos_.x,(pos_.y + (size_.y / 2)), pos_.z };

	//パーティクル読み込み
	smoke_ = ResourceManager::GetInstance_ResourceManager()->LoadPtcl_("ProtectOBJ_Smoke");
	smoke_->stop();
}

ProtectObject::~ProtectObject(){
	smoke_.reset();

}

void ProtectObject::Update(float delta_time){
	//hpの残り割合計算
	hp_ratio_ = hp_ / init_hp_;
	//hpが50％以下になればsmoke_を生成
	if (smoke_gene_hp_ >= hp_ratio_) {
		smoke_->start();
	}

}

void ProtectObject::Draw(std::shared_ptr<Camera> camera){
	//船描画
	mesh_->render(camera);

	dxe::DirectXRenderBegin();

	//パーティクル描画
	smoke_->render(camera);

	dxe::DirectXRenderEnd();
}
