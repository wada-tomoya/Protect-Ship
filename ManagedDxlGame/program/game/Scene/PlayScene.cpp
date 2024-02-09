#include "PlayScene.h"

PlayScene::PlayScene() {
	srand(time(0));

	//オブジェクトインスタンス
	map_ = std::make_shared<Play_Map>();
	camera_ = std::make_shared<Camera>();
	player_ = std::make_shared<Player>(map_->MapEdge_Getter("upleft"), map_->MapEdge_Getter("lowright"), map_->Groundpos_Getter());
	//protectobj_ = std::make_shared<ProtectObject>();
}

void PlayScene::Update(float delta_time) {
	//カメラ実行						
	camera_->Update(player_->GetterPos(),
		map_->MapEdge_Getter("upleft").y, map_->MapEdge_Getter("lowright").y, map_->MapEdge_Getter("lowright").x, map_->MapEdge_Getter("upleft").x);
	//プレイヤー実行
	player_->Update(delta_time);
}

void PlayScene::Draw(float delta_time) {
	//背景
	map_->Background_Draw(camera_);
	//足場ブロック
	map_->MapChip_Draw(camera_);
	//守るオブジェクト
	//protectobj_->Draw(delta_time, *camera_);
	//プレイヤー表示
	player_->Draw(delta_time, camera_);

	DrawStringEx(10, 30, -1, "camera %f, %f", camera_->pos_.x, camera_->pos_.y);
	DrawStringEx(10, 110, -1, "cameratarget %f, %f", camera_->target_.x, camera_->target_.y);
}
