#include "PlayScene.h"
#include "../Manager/ResourceManager.h"
#include "../Object/Map/Play_Map.h"
#include "../Object/Camera.h"
#include "../Character/Player.h"
#include "../Object/ProtectObject.h"
#include "../Manager/Collision.h"
#include "../Manager/UIManager.h"
#include "TitleScene.h"

PlayScene::PlayScene(const FINALCLASS_NAME& class_name) : SceneBace(class_name) {
	srand(time(0));

	//オブジェクトインスタンス
	camera_ = std::make_shared<Camera>();
	// Zファイト軽減措置
	camera_->far_ = 3000;
	camera_->near_ = 10;
	map_ = std::make_shared<Play_Map>();
	player_ = std::make_shared<Player>(map_->Getter_Playmap_Center(), map_->Getter_Playmap_Rad(), map_->Getter_Ground(), camera_);
	protectobject_ = std::make_shared<ProtectObject>();
	spawner_ = std::make_shared<Spawner>(map_->Getter_Playmap_Center(), map_->Getter_Playmap_Rad(), protectobject_, player_);
	collision_ = std::make_shared<Collision>();
	ui_ = std::make_shared<UIManager>();

	//音楽ロード
	bgm_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("PlayScene_BGM");
	gameclear_bgm_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("GameClear");
	gameover_bgm_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("GameOver");
	//bgm再生
	PlaySoundMem(bgm_hdl_, DX_PLAYTYPE_LOOP);

	//マウス画像読み込み
	mouse_graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("Mouse_Play");

	//プレイシーンUI初期値設定
	ui_->UI_init_PlayScene(protectobject_->Getter_Hp(), player_->Getter_statusup_itemlist_());

	//敵のステータス変更タイミング
	const float changetiming_easy_[]{ 15.0f,30.0f,45.0f };
	const float changetiming_normal_[]{ 30.0f,60.0f,75.0f,90.0f,105.0f };
	const float changetiming_hard_[]{30.0f,60.0f,75.0f,90.0f,105.0f,120.0f,135.0f,150.0f,165.0f};
	//ゲームレベルごとのステータス変更
	switch (scenename_) {
	case FINALCLASS_NAME::play_easy:
		//敵の初期値設定
		enemy_spawninterval_[static_cast<int>(ENEMYTYPE::normal)] = 1.0f;
		enemy_hp_[static_cast<int>(ENEMYTYPE::normal)] = 20.0f;
		enemy_speed_[static_cast<int>(ENEMYTYPE::normal)] = 1.0f;
		enemy_spawninterval_[static_cast<int>(ENEMYTYPE::chase)] = 8.0f;
		enemy_hp_[static_cast<int>(ENEMYTYPE::chase)] = 30.0f;
		enemy_speed_[static_cast<int>(ENEMYTYPE::chase)] = 2.0f;
		enemy_spawninterval_[static_cast<int>(ENEMYTYPE::big)] = 20.0f;
		enemy_hp_[static_cast<int>(ENEMYTYPE::big)] = 200.0f;
		enemy_speed_[static_cast<int>(ENEMYTYPE::big)] = 0.5f;
		//タイミングでの変化値設定
		change_spawninterval_[static_cast<int>(ENEMYTYPE::normal)] = 0.2f;
		change_hp_[static_cast<int>(ENEMYTYPE::normal)] = 15.0f;
		change_speed_[static_cast<int>(ENEMYTYPE::normal)] = 0.3f;
		change_spawninterval_[static_cast<int>(ENEMYTYPE::chase)] = 1.5f;
		change_hp_[static_cast<int>(ENEMYTYPE::chase)] = 10.0f;
		change_speed_[static_cast<int>(ENEMYTYPE::chase)] = 0.2f;
		change_spawninterval_[static_cast<int>(ENEMYTYPE::big)] = 2.0f;
		change_hp_[static_cast<int>(ENEMYTYPE::big)] = 50.0f;
		change_speed_[static_cast<int>(ENEMYTYPE::big)] = 0.1f;
		//敵のステータス変更タイミング
		status_change_timing_.insert(status_change_timing_.end(), std::begin(changetiming_easy_),std::end(changetiming_easy_));
		//変更回数上限設定
		status_change_max_ = status_change_timing_.size();
		//ゲーム制限時間変更
		gametime_ = 61.0f;
		break;
	case FINALCLASS_NAME::play_normal:
		//敵の初期値設定
		enemy_spawninterval_[static_cast<int>(ENEMYTYPE::normal)] = 1.0f;
		enemy_hp_[static_cast<int>(ENEMYTYPE::normal)] = 25.0f;
		enemy_speed_[static_cast<int>(ENEMYTYPE::normal)] = 1.0f;
		enemy_spawninterval_[static_cast<int>(ENEMYTYPE::chase)] = 7.0f;
		enemy_hp_[static_cast<int>(ENEMYTYPE::chase)] = 30.0f;
		enemy_speed_[static_cast<int>(ENEMYTYPE::chase)] = 2.0f;
		enemy_spawninterval_[static_cast<int>(ENEMYTYPE::big)] = 20.0f;
		enemy_hp_[static_cast<int>(ENEMYTYPE::big)] = 200.0f;
		enemy_speed_[static_cast<int>(ENEMYTYPE::big)] = 0.5f;
		//タイミングでの変化値設定
		change_spawninterval_[static_cast<int>(ENEMYTYPE::normal)] = 0.15f;
		change_hp_[static_cast<int>(ENEMYTYPE::normal)] = 15.0f;
		change_speed_[static_cast<int>(ENEMYTYPE::normal)] = 0.3f;
		change_spawninterval_[static_cast<int>(ENEMYTYPE::chase)] = 1.2f;
		change_hp_[static_cast<int>(ENEMYTYPE::chase)] = 15.0f;
		change_speed_[static_cast<int>(ENEMYTYPE::chase)] = 0.5f;
		change_spawninterval_[static_cast<int>(ENEMYTYPE::big)] = 3.0f;
		change_hp_[static_cast<int>(ENEMYTYPE::big)] = 70.0f;
		change_speed_[static_cast<int>(ENEMYTYPE::big)] = 0.2f;
		//敵のステータス変更タイミング
		status_change_timing_.insert(status_change_timing_.end(), std::begin(changetiming_normal_), std::end(changetiming_normal_));
		//変更回数上限設定
		status_change_max_ = status_change_timing_.size();
		//ゲーム制限時間変更
		gametime_ = 121.0f;
		break;
	case FINALCLASS_NAME::play_hard:
		//敵の初期値設定
		enemy_spawninterval_[static_cast<int>(ENEMYTYPE::normal)] = 1.0f;
		enemy_hp_[static_cast<int>(ENEMYTYPE::normal)] = 25.0f;
		enemy_speed_[static_cast<int>(ENEMYTYPE::normal)] = 1.5f;
		enemy_spawninterval_[static_cast<int>(ENEMYTYPE::chase)] = 7.0f;
		enemy_hp_[static_cast<int>(ENEMYTYPE::chase)] = 30.0f;
		enemy_speed_[static_cast<int>(ENEMYTYPE::chase)] = 2.0f;
		enemy_spawninterval_[static_cast<int>(ENEMYTYPE::big)] = 15.0f;
		enemy_hp_[static_cast<int>(ENEMYTYPE::big)] = 300.0f;
		enemy_speed_[static_cast<int>(ENEMYTYPE::big)] = 0.5f;
		//タイミングでの変化値設定
		change_spawninterval_[static_cast<int>(ENEMYTYPE::normal)] = 0.09f;
		change_hp_[static_cast<int>(ENEMYTYPE::normal)] = 12.0f;
		change_speed_[static_cast<int>(ENEMYTYPE::normal)] = 0.2f;
		change_spawninterval_[static_cast<int>(ENEMYTYPE::chase)] = 0.5f;
		change_hp_[static_cast<int>(ENEMYTYPE::chase)] = 20.0f;
		change_speed_[static_cast<int>(ENEMYTYPE::chase)] = 0.6f;
		change_spawninterval_[static_cast<int>(ENEMYTYPE::big)] = 1.0f;
		change_hp_[static_cast<int>(ENEMYTYPE::big)] = 80.0f;
		change_speed_[static_cast<int>(ENEMYTYPE::big)] = 0.5f;
		//敵のステータス変更タイミング
		status_change_timing_.insert(status_change_timing_.end(), std::begin(changetiming_hard_), std::end(changetiming_hard_));
		//変更回数上限設定
		status_change_max_ = status_change_timing_.size();
		//ゲーム制限時間変更
		gametime_ = 181.0f;
		break;
	default:
		break;
	}
	//敵の初期値設定
	spawner_->Enemy_SpawnStatusChange(ENEMYTYPE::normal, -enemy_spawninterval_[static_cast<int>(ENEMYTYPE::normal)], enemy_hp_[static_cast<int>(ENEMYTYPE::normal)], enemy_speed_[static_cast<int>(ENEMYTYPE::normal)]);
	spawner_->Enemy_SpawnStatusChange(ENEMYTYPE::chase, -enemy_spawninterval_[static_cast<int>(ENEMYTYPE::chase)], enemy_hp_[static_cast<int>(ENEMYTYPE::chase)], enemy_speed_[static_cast<int>(ENEMYTYPE::chase)]);
	spawner_->Enemy_SpawnStatusChange(ENEMYTYPE::big, -enemy_spawninterval_[static_cast<int>(ENEMYTYPE::big)], enemy_hp_[static_cast<int>(ENEMYTYPE::big)], enemy_speed_[static_cast<int>(ENEMYTYPE::big)]);

	tnl::DebugTrace("%d", scenename_);
}

PlayScene::~PlayScene() {
	DeleteSoundMem(bgm_hdl_);
	DeleteSoundMem(gameclear_bgm_);
	DeleteSoundMem(gameover_bgm_);
}

void PlayScene::Update(const float& delta_time) {
	//カメラ実行						
	camera_->Update(player_->GetterPos());

	//シーケンス実行
	play_sequence_.update(delta_time);

	//UI更新
	ui_->UI_Update_PlayScene(delta_time, protectobject_->Getter_Hp());
}

void PlayScene::Draw(const float& delta_time) {
	//プレイシーンのマップ描画
	map_->Map_Draw(camera_);
	//攻撃の描画
	player_->AttackDraw(camera_);
	//敵描画
	spawner_->Draw(camera_);
	//プレイヤー表示
	player_->Draw(delta_time, camera_);
	//敵の目標オブジェクト描画
	protectobject_->Draw(camera_);

	//シーケンスに合わせてuiを表示
	switch (nowsequence_) {
	case NOWSEQUENCE::explanation:
		ui_->Draw_PlayGuid();
		break;
	case NOWSEQUENCE::play:
		//船のhp低下時の画面effect表示
		ui_->Draw_ScreenEffect();
		//制限時間表示
		ui_->Draw_timer(gametime_);
		//hpバー表示
		ui_->Draw_hpbar();
		//プレイヤー所持アイテム表示
		ui_->Draw_PlayerItem(player_->Getter_statusup_itemlist_());
		//プレイヤー所持爆破攻撃表示
		ui_->Draw_Bombstock(player_->Getter_BombStock());
		//escメニュー案内
		DrawStringEx(esc_guid_pos_.x, esc_guid_pos_.y, -1, "ESC : メニュー画面");
		break;
	case NOWSEQUENCE::gameover:
		ui_->Draw_gameend((int)NOWSEQUENCE::gameover);
		break;
	case NOWSEQUENCE::gameclear:
		ui_->Draw_gameend((int)NOWSEQUENCE::gameclear);
		break;
	case NOWSEQUENCE::menu:
		ui_->Draw_PlayMenu();
		break;
	}

	//DrawFpsIndicator({ 10, DXE_WINDOW_HEIGHT - 10, 0 }, delta_time);

	//プレイヤーと一緒に点滅
	if (player_->Getter_is_flash_()) {
		//マウス描画
		MouseDraw();
	}
}

bool PlayScene::Seq_Explanation(float delat_time) {
	nowsequence_ = NOWSEQUENCE::explanation;

	ui_->Update_PlayGuid();

	//シーケンス移動条件
	//ゲーム実行シーケンスに移動
	if (ui_->IsCursor_Button(static_cast<int>(BUTTONNAME::close_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		play_sequence_.change(&PlayScene::Seq_Update);
	}

	return true;
}

bool PlayScene::Seq_Update(float delta_time) {
	nowsequence_ = NOWSEQUENCE::play;
	//制限時間のカウント
	gametime_ -= delta_time;

	//敵ステータス変更
	//ステータス変更回数上限以下ならば実行
	if (status_change_num_ < status_change_max_) {
		//変更タイミングになればis_status_change_をtrueにし、変更
		if (play_sequence_.getProgressTime() >= status_change_timing_[status_change_num_]) {
			is_status_change_ = true;
		}
		if (is_status_change_) {		
			is_status_change_ = false;
			//変更タイミングを次に進める
			status_change_num_++;

			tnl::DebugTrace("敵ステータス変更 ");
			tnl::DebugTrace("%d回目\n", status_change_num_);

			//敵のステータス変更
			spawner_->Enemy_SpawnStatusChange(ENEMYTYPE::normal, change_spawninterval_[static_cast<int>(ENEMYTYPE::normal)], change_hp_[static_cast<int>(ENEMYTYPE::normal)], change_speed_[static_cast<int>(ENEMYTYPE::normal)]);
			spawner_->Enemy_SpawnStatusChange(ENEMYTYPE::chase, change_spawninterval_[static_cast<int>(ENEMYTYPE::chase)], change_hp_[static_cast<int>(ENEMYTYPE::chase)], change_speed_[static_cast<int>(ENEMYTYPE::chase)]);
			spawner_->Enemy_SpawnStatusChange(ENEMYTYPE::big, change_spawninterval_[static_cast<int>(ENEMYTYPE::big)], change_hp_[static_cast<int>(ENEMYTYPE::big)], change_speed_[static_cast<int>(ENEMYTYPE::big)]);
		}
	}
	
	//敵のスポナー実行
	spawner_->Update(delta_time);
	//プレイヤー実行
	player_->Update(delta_time);
	//船実行
	protectobject_->Update(delta_time);

	//弾と敵の当たり判定
	collision_->Attack_Enemy_HitCheck(player_->Getter_Aattack_list(), spawner_->Getter_enemy_list());
	//プレイヤーと敵の当たり判定
	collision_->Player_Enemy_HitChack(player_, spawner_->Getter_enemy_list());
	//プレイヤーとアイテムの当たり判定
	collision_->Player_Item_HitChack(player_, spawner_->Getter_Items());

	//シーケンス移動条件
	//船の体力が0以下になったらゲームオーバー
	if (protectobject_->Getter_Hp() <= 0) {
		play_sequence_.change(&PlayScene::Seq_Gameover);

		//bgm停止
		int sound_check = CheckSoundMem(bgm_hdl_);
		if (sound_check == 1) {
			StopSoundMem(bgm_hdl_);
		}
	}
	//制限時間が0になればクリア
	else if (gametime_ <= 0.0f) {
		play_sequence_.change(&PlayScene::Seq_GameClear);

		//bgm停止
		int sound_check = CheckSoundMem(bgm_hdl_);
		if (sound_check == 1) {
			StopSoundMem(bgm_hdl_);
		}
	}
	//escキーでメニュー画面
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		play_sequence_.change(&PlayScene::Seq_Menu);
	}

	return true;
}

bool PlayScene::Seq_Gameover(float delta_time) {
	nowsequence_ = NOWSEQUENCE::gameover;

	//bgm再生
	if (play_sequence_.isStart()) {
		PlaySoundMem(gameover_bgm_, DX_PLAYTYPE_LOOP);
	}

	//シーン移動
	if (!is_scene_change_ && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		//bgm停止
		StopSoundMem(gameover_bgm_);

		/*GameManager* mgr = GameManager::GetInstance_GameManager();
		mgr->ChangeScene(new (TitleScene)(ENDCLASS_NAME::title));*/

		//シーン遷移
		GameManager::GetInstance_GameManager()->ChangeScene(new(TitleScene)(FINALCLASS_NAME::title));

		is_scene_change_ = true;
	}

	return true;
}

bool PlayScene::Seq_GameClear(float delta_time) {
	nowsequence_ = NOWSEQUENCE::gameclear;

	//bgm再生
	if (play_sequence_.isStart()) {
		PlaySoundMem(gameclear_bgm_, DX_PLAYTYPE_LOOP);
	}

	//シーン移動
	if (!is_scene_change_ && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		//bgm停止
		StopSoundMem(gameclear_bgm_);

		/*GameManager* mgr = GameManager::GetInstance_GameManager();
		mgr->ChangeScene(new (TitleScene)(ENDCLASS_NAME::title));*/

		//シーン遷移
		GameManager::GetInstance_GameManager()->ChangeScene(new(TitleScene)(FINALCLASS_NAME::title));

		is_scene_change_ = true;
	}

	return true;
}

bool PlayScene::Seq_Menu(float delta_time) {
	nowsequence_ = NOWSEQUENCE::menu;

	//プレイシーンメニューui実行
	ui_->Update_PlayMenu(delta_time);

	if (!ui_->Getter_is_menu_()) {
		play_sequence_.change(&PlayScene::Seq_Update);
	}
	else if (ui_->Getter_is_amemidend_()) {
		play_sequence_.change(&PlayScene::Seq_Gameover);

		//bgm停止
		int sound_check = CheckSoundMem(bgm_hdl_);
		if (sound_check == 1) {
			StopSoundMem(bgm_hdl_);
		}
	}

	return true;
}
