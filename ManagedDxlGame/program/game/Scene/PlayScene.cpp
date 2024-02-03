#include "PlayScene.h"

PlayScene::PlayScene() {
	srand(time(0));

	//背景画像読み込み
	background_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("PlayScene_BackGround");


	//オブジェクトインスタンス
	//block_ = std::make_shared<Block>();
	camera_ = std::make_shared<Camera>();
	player_ = std::make_shared<Player>(bg_pos_.y, map_endpos_.y, map_endpos_.x, bg_pos_.x);
	//protectobj_ = std::make_shared<ProtectObject>();
	//enemy_ = std::make_shared<Enemy>(protectobj_->GetterPos(), enemy_spon_pos, 5.0f);
}

void PlayScene::Update(float delta_time) {
	//カメラ、プレイヤー追尾									  ↓マップチップ分
	camera_->Update(player_->GetterPos(), bg_pos_.y, map_endpos_.y + 48.0f, map_endpos_.x, bg_pos_.x);
	//プレイヤー実行
	player_->Update(delta_time);
	//敵
	//enemy_->Update(delta_time);
}

void PlayScene::Draw(float delta_time) {
	//背景
	//DrawExtendGraph(0, 0, 50, 50, background_hdl_, false);

	//足場ブロック
	//block_->Draw(*camera_);
	//敵のターゲット、プレイヤーが守るやつ
	//protectobj_->Draw(delta_time, *camera_);
	//敵
	//enemy_->Draw(delta_time, *camera_);
	//プレイヤー表示
	player_->Draw(delta_time, camera_);

}
