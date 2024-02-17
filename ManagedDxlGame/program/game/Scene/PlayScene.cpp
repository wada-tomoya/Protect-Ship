#include "PlayScene.h"

PlayScene::PlayScene() {
	srand(time(0));

	//オブジェクトインスタンス
	map_ = std::make_shared<Play_Map>();
	camera_ = std::make_shared<Camera>();
	player_ = std::make_shared<Player>(map_->MapEdgePlsyer_Getter("upleft"), map_->MapEdgePlsyer_Getter("lowright"));
	protectobj_ = std::make_shared<ProtectObject>();
	spawner_ = std::make_shared<Spawner>(map_->MapEdge_Getter("upleft"), map_->MapEdge_Getter("lowright"));
}

void PlayScene::Update(float delta_time) {
	//カメラ実行						
	camera_->Update(player_->GetterPos());
	//敵のスポナー実行
	spawner_->Update(delta_time);
	//プレイヤー実行
	player_->Update(delta_time);
}

void PlayScene::Draw(float delta_time) {
	//プレイヤーの攻撃描画
	player_->AttackDraw(camera_);
	//敵表示
	spawner_->Draw(camera_);
	//背景
	map_->Background_Draw(camera_);
//InstMeshPool描画
//----------------------------------------------------------
//通常Mesh描画
	//守るオブジェクト
	protectobj_->Draw(camera_);
	//プレイヤー表示
	player_->Draw(delta_time, camera_);
	
}
