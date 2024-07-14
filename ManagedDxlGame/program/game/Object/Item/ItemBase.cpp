#include "ItemBase.h"

ItemBase::ItemBase(int mv1model){
	//���f��
	mv1model_ = mv1model;
	//�T�C�Y�ύX
	MV1SetScale(mv1model_,VGet(scale_,scale_,scale_));
	//���W�ύX
	MV1SetPosition(mv1model_, {MV1GetPosition(mv1model_).x,pos_y_,MV1GetPosition(mv1model_).z });
	//�����蔻��p���W�Z�b�g
	pos_ = tnl::Vector3{ MV1GetPosition(mv1model_).x,MV1GetPosition(mv1model_).y,MV1GetPosition(mv1model_).z };
}

ItemBase::~ItemBase() {
	MV1DeleteModel(mv1model_);
}

void ItemBase::Update(float delta_time){
	//���S�J�E���g
	death_count_ += delta_time;
	if (death_count_ >= death_time_) {
		Delete();
	}

	//��]
	MV1SetRotationXYZ(mv1model_, { 0,MV1GetRotationXYZ(mv1model_).y + rotateangle_,0 });	
}

void ItemBase::PlyarHit(){

	//����
	Delete();
}
