#include "ProtectObject.h"

ProtectObject::ProtectObject() {
	//�e�N�X�`���@���[�h
	texture_ = ResourceManager::GetInstance_ResourceManager()->LoadTexture_("PROTECTOBJECT");
	//���b�V������
	mesh_ = dxe::Mesh::CreatePlaneMV(size_, 1, 1);
	mesh_->setTexture(texture_);
	mesh_->setBlendMode(DX_BLENDMODE_ALPHA);
	mesh_->setSampleFilterMode(DX_DRAWMODE_NEAREST);
	mesh_->pos_ = tnl::Vector3{ pos_.x,(pos_.y + (size_.y / 2)), pos_.z };

	//�p�[�e�B�N���ǂݍ���
	smoke_ = ResourceManager::GetInstance_ResourceManager()->LoadPtcl_("ProtectOBJ_Smoke");
	smoke_->stop();
}

ProtectObject::~ProtectObject(){
	smoke_.reset();

}

void ProtectObject::Update(float delta_time){
	//hp�̎c�芄���v�Z
	hp_ratio_ = hp_ / init_hp_;
	//hp��50���ȉ��ɂȂ��smoke_�𐶐�
	if (hp_ratio_ <= 0.5f) {
		smoke_->start();
	}

}

void ProtectObject::Draw(std::shared_ptr<Camera> camera){
	//�D�`��
	mesh_->render(camera);

	dxe::DirectXRenderBegin();

	//�p�[�e�B�N���`��
	smoke_->render(camera);

	dxe::DirectXRenderEnd();
}
