#include "ItemBase.h"

ItemBase::ItemBase(int mv1model){
	//モデル
	mv1model_ = mv1model;
	//サイズ変更
	MV1SetScale(mv1model_,VGet(scale_,scale_,scale_));
	//座標変更
	MV1SetPosition(mv1model_, {MV1GetPosition(mv1model_).x,pos_y_,MV1GetPosition(mv1model_).z });
	//当たり判定用座標セット
	pos_ = tnl::Vector3{ MV1GetPosition(mv1model_).x,MV1GetPosition(mv1model_).y,MV1GetPosition(mv1model_).z };
}

ItemBase::~ItemBase() {
	MV1DeleteModel(mv1model_);
}

void ItemBase::Update(float delta_time){
	//死亡カウント
	death_count_ += delta_time;
	if (death_count_ >= death_time_) {
		Delete();
	}

	//回転
	MV1SetRotationXYZ(mv1model_, { 0,MV1GetRotationXYZ(mv1model_).y + rotateangle_,0 });	
}

void ItemBase::PlyarHit(){

	//消去
	Delete();
}
