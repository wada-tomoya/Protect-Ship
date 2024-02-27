#include "PlayScene.h"

PlayScene::PlayScene() {
	srand(time(0));

	//オブジェクトインスタンス
	camera_ = std::make_shared<Camera>();
//	map_ = std::make_shared<Play_Map>();
	player_ = std::make_shared<Player>();
//	protectobj_ = std::make_shared<ProtectObject>();
//	Spawner::Instance_Spawner(map_->MapEdge_Getter("upleft"), map_->MapEdge_Getter("lowright"));
//	collision_ = std::make_shared<Collision>();

	//音楽ロード
	bgm_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("PlayScene_BGM");
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(255, bgm_);
}

PlayScene::~PlayScene() {
	//スポナーのインスタンスを開放
	Spawner::Instance_Spawner()->Destroy();
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
	//当たり判定
//	collision_->Attack_Enemy_HitCheck(AttackManager::Instance_AttackManager()->attacks_,
//		Spawner::Instance_Spawner()->enemys_);
}

void PlayScene::Draw(float delta_time) {
	DrawGridGround(camera_, 50, 20);
//	//各攻撃描画
//	player_->Attack_Draw(camera_);
//	//敵描画
//	Spawner::Instance_Spawner()->Draw(camera_);
//	//背景
//	map_->Background_Draw(camera_);
//	
//InstMeshPool描画
//----------------------------------------------------------
//通常Mesh描画
//	//守るオブジェクト
//	protectobj_->Draw(camera_);
//	//プレイヤー表示
	player_->Draw(delta_time, camera_);
	

	DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);
}
