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

	//�I�u�W�F�N�g�C���X�^���X
	camera_ = std::make_shared<Camera>();
	// Z�t�@�C�g�y���[�u
	camera_->far_ = 3000;
	camera_->near_ = 10;
	map_ = std::make_shared<Play_Map>();
	player_ = std::make_shared<Player>(map_->Getter_Playmap_Center(), map_->Getter_Playmap_Rad(), map_->Getter_Ground(), camera_);
	protectobject_ = std::make_shared<ProtectObject>();
	spawner_ = std::make_shared<Spawner>(map_->Getter_Playmap_Center(), map_->Getter_Playmap_Rad(), protectobject_, player_);
	collision_ = std::make_shared<Collision>();
	ui_ = std::make_shared<UIManager>();

	//���y���[�h
	bgm_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("PlayScene_BGM");
	gameclear_bgm_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("GameClear");
	gameover_bgm_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("GameOver");
	//bgm�Đ�
	PlaySoundMem(bgm_hdl_, DX_PLAYTYPE_LOOP);

	//�}�E�X�摜�ǂݍ���
	mouse_graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("Mouse_Play");

	//�v���C�V�[��UI�����l�ݒ�
	ui_->UI_init_PlayScene(protectobject_->Getter_Hp(), player_->Getter_statusup_itemlist_());

	//�G�̃X�e�[�^�X�ύX�^�C�~���O
	const float changetiming_easy_[]{ 15.0f,30.0f,45.0f };
	const float changetiming_normal_[]{ 30.0f,60.0f,75.0f,90.0f,105.0f };
	const float changetiming_hard_[]{30.0f,60.0f,75.0f,90.0f,105.0f,120.0f,135.0f,150.0f,165.0f};
	//�Q�[�����x�����Ƃ̃X�e�[�^�X�ύX
	switch (scenename_) {
	case FINALCLASS_NAME::play_easy:
		//�G�̏����l�ݒ�
		enemy_spawninterval_[static_cast<int>(ENEMYTYPE::normal)] = 1.0f;
		enemy_hp_[static_cast<int>(ENEMYTYPE::normal)] = 20.0f;
		enemy_speed_[static_cast<int>(ENEMYTYPE::normal)] = 1.0f;
		enemy_spawninterval_[static_cast<int>(ENEMYTYPE::chase)] = 8.0f;
		enemy_hp_[static_cast<int>(ENEMYTYPE::chase)] = 30.0f;
		enemy_speed_[static_cast<int>(ENEMYTYPE::chase)] = 2.0f;
		enemy_spawninterval_[static_cast<int>(ENEMYTYPE::big)] = 20.0f;
		enemy_hp_[static_cast<int>(ENEMYTYPE::big)] = 200.0f;
		enemy_speed_[static_cast<int>(ENEMYTYPE::big)] = 0.5f;
		//�^�C�~���O�ł̕ω��l�ݒ�
		change_spawninterval_[static_cast<int>(ENEMYTYPE::normal)] = 0.2f;
		change_hp_[static_cast<int>(ENEMYTYPE::normal)] = 15.0f;
		change_speed_[static_cast<int>(ENEMYTYPE::normal)] = 0.3f;
		change_spawninterval_[static_cast<int>(ENEMYTYPE::chase)] = 1.5f;
		change_hp_[static_cast<int>(ENEMYTYPE::chase)] = 10.0f;
		change_speed_[static_cast<int>(ENEMYTYPE::chase)] = 0.2f;
		change_spawninterval_[static_cast<int>(ENEMYTYPE::big)] = 2.0f;
		change_hp_[static_cast<int>(ENEMYTYPE::big)] = 50.0f;
		change_speed_[static_cast<int>(ENEMYTYPE::big)] = 0.1f;
		//�G�̃X�e�[�^�X�ύX�^�C�~���O
		status_change_timing_.insert(status_change_timing_.end(), std::begin(changetiming_easy_),std::end(changetiming_easy_));
		//�ύX�񐔏���ݒ�
		status_change_max_ = status_change_timing_.size();
		//�Q�[���������ԕύX
		gametime_ = 61.0f;
		break;
	case FINALCLASS_NAME::play_normal:
		//�G�̏����l�ݒ�
		enemy_spawninterval_[static_cast<int>(ENEMYTYPE::normal)] = 1.0f;
		enemy_hp_[static_cast<int>(ENEMYTYPE::normal)] = 25.0f;
		enemy_speed_[static_cast<int>(ENEMYTYPE::normal)] = 1.0f;
		enemy_spawninterval_[static_cast<int>(ENEMYTYPE::chase)] = 7.0f;
		enemy_hp_[static_cast<int>(ENEMYTYPE::chase)] = 30.0f;
		enemy_speed_[static_cast<int>(ENEMYTYPE::chase)] = 2.0f;
		enemy_spawninterval_[static_cast<int>(ENEMYTYPE::big)] = 20.0f;
		enemy_hp_[static_cast<int>(ENEMYTYPE::big)] = 200.0f;
		enemy_speed_[static_cast<int>(ENEMYTYPE::big)] = 0.5f;
		//�^�C�~���O�ł̕ω��l�ݒ�
		change_spawninterval_[static_cast<int>(ENEMYTYPE::normal)] = 0.15f;
		change_hp_[static_cast<int>(ENEMYTYPE::normal)] = 15.0f;
		change_speed_[static_cast<int>(ENEMYTYPE::normal)] = 0.3f;
		change_spawninterval_[static_cast<int>(ENEMYTYPE::chase)] = 1.2f;
		change_hp_[static_cast<int>(ENEMYTYPE::chase)] = 15.0f;
		change_speed_[static_cast<int>(ENEMYTYPE::chase)] = 0.5f;
		change_spawninterval_[static_cast<int>(ENEMYTYPE::big)] = 3.0f;
		change_hp_[static_cast<int>(ENEMYTYPE::big)] = 70.0f;
		change_speed_[static_cast<int>(ENEMYTYPE::big)] = 0.2f;
		//�G�̃X�e�[�^�X�ύX�^�C�~���O
		status_change_timing_.insert(status_change_timing_.end(), std::begin(changetiming_normal_), std::end(changetiming_normal_));
		//�ύX�񐔏���ݒ�
		status_change_max_ = status_change_timing_.size();
		//�Q�[���������ԕύX
		gametime_ = 121.0f;
		break;
	case FINALCLASS_NAME::play_hard:
		//�G�̏����l�ݒ�
		enemy_spawninterval_[static_cast<int>(ENEMYTYPE::normal)] = 1.0f;
		enemy_hp_[static_cast<int>(ENEMYTYPE::normal)] = 25.0f;
		enemy_speed_[static_cast<int>(ENEMYTYPE::normal)] = 1.5f;
		enemy_spawninterval_[static_cast<int>(ENEMYTYPE::chase)] = 7.0f;
		enemy_hp_[static_cast<int>(ENEMYTYPE::chase)] = 30.0f;
		enemy_speed_[static_cast<int>(ENEMYTYPE::chase)] = 2.0f;
		enemy_spawninterval_[static_cast<int>(ENEMYTYPE::big)] = 15.0f;
		enemy_hp_[static_cast<int>(ENEMYTYPE::big)] = 300.0f;
		enemy_speed_[static_cast<int>(ENEMYTYPE::big)] = 0.5f;
		//�^�C�~���O�ł̕ω��l�ݒ�
		change_spawninterval_[static_cast<int>(ENEMYTYPE::normal)] = 0.09f;
		change_hp_[static_cast<int>(ENEMYTYPE::normal)] = 12.0f;
		change_speed_[static_cast<int>(ENEMYTYPE::normal)] = 0.2f;
		change_spawninterval_[static_cast<int>(ENEMYTYPE::chase)] = 0.5f;
		change_hp_[static_cast<int>(ENEMYTYPE::chase)] = 20.0f;
		change_speed_[static_cast<int>(ENEMYTYPE::chase)] = 0.6f;
		change_spawninterval_[static_cast<int>(ENEMYTYPE::big)] = 1.0f;
		change_hp_[static_cast<int>(ENEMYTYPE::big)] = 80.0f;
		change_speed_[static_cast<int>(ENEMYTYPE::big)] = 0.5f;
		//�G�̃X�e�[�^�X�ύX�^�C�~���O
		status_change_timing_.insert(status_change_timing_.end(), std::begin(changetiming_hard_), std::end(changetiming_hard_));
		//�ύX�񐔏���ݒ�
		status_change_max_ = status_change_timing_.size();
		//�Q�[���������ԕύX
		gametime_ = 181.0f;
		break;
	default:
		break;
	}
	//�G�̏����l�ݒ�
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
	//�J�������s						
	camera_->Update(player_->GetterPos());

	//�V�[�P���X���s
	play_sequence_.update(delta_time);

	//UI�X�V
	ui_->UI_Update_PlayScene(delta_time, protectobject_->Getter_Hp());
}

void PlayScene::Draw(const float& delta_time) {
	//�v���C�V�[���̃}�b�v�`��
	map_->Map_Draw(camera_);
	//�U���̕`��
	player_->AttackDraw(camera_);
	//�G�`��
	spawner_->Draw(camera_);
	//�v���C���[�\��
	player_->Draw(delta_time, camera_);
	//�G�̖ڕW�I�u�W�F�N�g�`��
	protectobject_->Draw(camera_);

	//�V�[�P���X�ɍ��킹��ui��\��
	switch (nowsequence_) {
	case NOWSEQUENCE::explanation:
		ui_->Draw_PlayGuid();
		break;
	case NOWSEQUENCE::play:
		//�D��hp�ቺ���̉��effect�\��
		ui_->Draw_ScreenEffect();
		//�������ԕ\��
		ui_->Draw_timer(gametime_);
		//hp�o�[�\��
		ui_->Draw_hpbar();
		//�v���C���[�����A�C�e���\��
		ui_->Draw_PlayerItem(player_->Getter_statusup_itemlist_());
		//�v���C���[�������j�U���\��
		ui_->Draw_Bombstock(player_->Getter_BombStock());
		//esc���j���[�ē�
		DrawStringEx(esc_guid_pos_.x, esc_guid_pos_.y, -1, "ESC : ���j���[���");
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

	//�v���C���[�ƈꏏ�ɓ_��
	if (player_->Getter_is_flash_()) {
		//�}�E�X�`��
		MouseDraw();
	}
}

bool PlayScene::Seq_Explanation(float delat_time) {
	nowsequence_ = NOWSEQUENCE::explanation;

	ui_->Update_PlayGuid();

	//�V�[�P���X�ړ�����
	//�Q�[�����s�V�[�P���X�Ɉړ�
	if (ui_->IsCursor_Button(static_cast<int>(BUTTONNAME::close_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		play_sequence_.change(&PlayScene::Seq_Update);
	}

	return true;
}

bool PlayScene::Seq_Update(float delta_time) {
	nowsequence_ = NOWSEQUENCE::play;
	//�������Ԃ̃J�E���g
	gametime_ -= delta_time;

	//�G�X�e�[�^�X�ύX
	//�X�e�[�^�X�ύX�񐔏���ȉ��Ȃ�Ύ��s
	if (status_change_num_ < status_change_max_) {
		//�ύX�^�C�~���O�ɂȂ��is_status_change_��true�ɂ��A�ύX
		if (play_sequence_.getProgressTime() >= status_change_timing_[status_change_num_]) {
			is_status_change_ = true;
		}
		if (is_status_change_) {		
			is_status_change_ = false;
			//�ύX�^�C�~���O�����ɐi�߂�
			status_change_num_++;

			tnl::DebugTrace("�G�X�e�[�^�X�ύX ");
			tnl::DebugTrace("%d���\n", status_change_num_);

			//�G�̃X�e�[�^�X�ύX
			spawner_->Enemy_SpawnStatusChange(ENEMYTYPE::normal, change_spawninterval_[static_cast<int>(ENEMYTYPE::normal)], change_hp_[static_cast<int>(ENEMYTYPE::normal)], change_speed_[static_cast<int>(ENEMYTYPE::normal)]);
			spawner_->Enemy_SpawnStatusChange(ENEMYTYPE::chase, change_spawninterval_[static_cast<int>(ENEMYTYPE::chase)], change_hp_[static_cast<int>(ENEMYTYPE::chase)], change_speed_[static_cast<int>(ENEMYTYPE::chase)]);
			spawner_->Enemy_SpawnStatusChange(ENEMYTYPE::big, change_spawninterval_[static_cast<int>(ENEMYTYPE::big)], change_hp_[static_cast<int>(ENEMYTYPE::big)], change_speed_[static_cast<int>(ENEMYTYPE::big)]);
		}
	}
	
	//�G�̃X�|�i�[���s
	spawner_->Update(delta_time);
	//�v���C���[���s
	player_->Update(delta_time);
	//�D���s
	protectobject_->Update(delta_time);

	//�e�ƓG�̓����蔻��
	collision_->Attack_Enemy_HitCheck(player_->Getter_Aattack_list(), spawner_->Getter_enemy_list());
	//�v���C���[�ƓG�̓����蔻��
	collision_->Player_Enemy_HitChack(player_, spawner_->Getter_enemy_list());
	//�v���C���[�ƃA�C�e���̓����蔻��
	collision_->Player_Item_HitChack(player_, spawner_->Getter_Items());

	//�V�[�P���X�ړ�����
	//�D�̗̑͂�0�ȉ��ɂȂ�����Q�[���I�[�o�[
	if (protectobject_->Getter_Hp() <= 0) {
		play_sequence_.change(&PlayScene::Seq_Gameover);

		//bgm��~
		int sound_check = CheckSoundMem(bgm_hdl_);
		if (sound_check == 1) {
			StopSoundMem(bgm_hdl_);
		}
	}
	//�������Ԃ�0�ɂȂ�΃N���A
	else if (gametime_ <= 0.0f) {
		play_sequence_.change(&PlayScene::Seq_GameClear);

		//bgm��~
		int sound_check = CheckSoundMem(bgm_hdl_);
		if (sound_check == 1) {
			StopSoundMem(bgm_hdl_);
		}
	}
	//esc�L�[�Ń��j���[���
	else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE)) {
		play_sequence_.change(&PlayScene::Seq_Menu);
	}

	return true;
}

bool PlayScene::Seq_Gameover(float delta_time) {
	nowsequence_ = NOWSEQUENCE::gameover;

	//bgm�Đ�
	if (play_sequence_.isStart()) {
		PlaySoundMem(gameover_bgm_, DX_PLAYTYPE_LOOP);
	}

	//�V�[���ړ�
	if (!is_scene_change_ && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		//bgm��~
		StopSoundMem(gameover_bgm_);

		/*GameManager* mgr = GameManager::GetInstance_GameManager();
		mgr->ChangeScene(new (TitleScene)(ENDCLASS_NAME::title));*/

		//�V�[���J��
		GameManager::GetInstance_GameManager()->ChangeScene(new(TitleScene)(FINALCLASS_NAME::title));

		is_scene_change_ = true;
	}

	return true;
}

bool PlayScene::Seq_GameClear(float delta_time) {
	nowsequence_ = NOWSEQUENCE::gameclear;

	//bgm�Đ�
	if (play_sequence_.isStart()) {
		PlaySoundMem(gameclear_bgm_, DX_PLAYTYPE_LOOP);
	}

	//�V�[���ړ�
	if (!is_scene_change_ && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		//bgm��~
		StopSoundMem(gameclear_bgm_);

		/*GameManager* mgr = GameManager::GetInstance_GameManager();
		mgr->ChangeScene(new (TitleScene)(ENDCLASS_NAME::title));*/

		//�V�[���J��
		GameManager::GetInstance_GameManager()->ChangeScene(new(TitleScene)(FINALCLASS_NAME::title));

		is_scene_change_ = true;
	}

	return true;
}

bool PlayScene::Seq_Menu(float delta_time) {
	nowsequence_ = NOWSEQUENCE::menu;

	//�v���C�V�[�����j���[ui���s
	ui_->Update_PlayMenu(delta_time);

	if (!ui_->Getter_is_menu_()) {
		play_sequence_.change(&PlayScene::Seq_Update);
	}
	else if (ui_->Getter_is_amemidend_()) {
		play_sequence_.change(&PlayScene::Seq_Gameover);

		//bgm��~
		int sound_check = CheckSoundMem(bgm_hdl_);
		if (sound_check == 1) {
			StopSoundMem(bgm_hdl_);
		}
	}

	return true;
}
