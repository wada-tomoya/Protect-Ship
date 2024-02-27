#include "PlayScene.h"

PlayScene::PlayScene() {
	srand(time(0));

	//オブジェクトインスタンス
	camera_ = std::make_shared<Camera>();
	map_ = std::make_shared<Play_Map>();
	player_ = std::make_shared<Player>();
//	protectobj_ = std::make_shared<ProtectObject>();
//	spawner_ = std::make_shared<Spawner>(map_->MapEdge_Getter("upleft"), map_->MapEdge_Getter("lowright"));
//	collision_ = std::make_shared<Collision>();

	//音楽ロード
	bgm_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("PlayScene_BGM");
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(255, bgm_);
}

PlayScene::~PlayScene() {
	//攻撃マネージャーのインスタンスを開放
	AttackManager::Instance_AttackManager()->Destroy();
}

void PlayScene::Update(float delta_time) {
	//カメラ実行						
	camera_->Update(player_->GetterPos());
	//敵のスポナー実行
//	Spawner::Instance_Spawner()->Update(delta_time);
	//プレイヤー実行
	player_->Update(delta_time);
}

void PlayScene::Draw(float delta_time) {
	DrawGridGround(camera_, 50, 20);

	//プレイシーンのマップ描画
	map_->Map_Draw(camera_);

	//プレイヤー表示
	player_->Draw(delta_time, camera_);
	
	DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);
}
