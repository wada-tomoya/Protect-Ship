#include "PlayScene.h"

PlayScene::PlayScene() {
	srand(time(0));

	//オブジェクトインスタンス
	map_ = std::make_shared<Play_Map>();
	camera_ = std::make_shared<Camera>();
	player_ = std::make_shared<Player>(map_->MapEdgePlsyer_Getter("upleft"), map_->MapEdgePlsyer_Getter("lowright"));
	//protectobj_ = std::make_shared<ProtectObject>();
}

void PlayScene::Update(float delta_time) {
	//カメラ実行						
	camera_->Update(player_->GetterPos());
	//プレイヤー実行
	player_->Update(delta_time);
}

void PlayScene::Draw(float delta_time) {
	//背景
	map_->Background_Draw(camera_);

	//守るオブジェクト
	//protectobj_->Draw(delta_time, *camera_);
	//プレイヤー表示
	player_->Draw(delta_time, camera_);
}
