#include "UIManager.h"
#include "../Manager/ResourceManager.h"

UIManager::UIManager() {
	//�K�C�h�֌W�摜�ǂݍ���
	playguid_page1_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("PlayGuide_Page1");
	playguid_page2_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("PlayGuide_Page2");
	button_[static_cast<int>(BUTTONNAME::arrow_left_)].graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("Arrow_Left");
	button_[static_cast<int>(BUTTONNAME::arrow_right_)].graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("Arrow_Right");
	button_[static_cast<int>(BUTTONNAME::close_)].graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("Close");
	button_[static_cast<int>(BUTTONNAME::gameguid_draw_)].graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("GameHelp_Button");
	//�{�^�����W�A�T�C�Y�ݒ�
	button_[static_cast<int>(BUTTONNAME::close_)].size_ = { 40,40 };
	button_[static_cast<int>(BUTTONNAME::close_)].pos_ = { playguid_pos_.x + (playguid_size_.x / 2) - (button_[static_cast<int>(BUTTONNAME::close_)].size_.x / 2) - button_widspace_,
		playguid_pos_.y - (playguid_size_.y / 2) + (button_[static_cast<int>(BUTTONNAME::close_)].size_.y / 2) + button_widspace_ };
	button_[static_cast<int>(BUTTONNAME::arrow_left_)].size_ = { 36,72 };
	button_[static_cast<int>(BUTTONNAME::arrow_left_)].pos_ = { playguid_pos_.x - (playguid_size_.x / 2) + (button_[static_cast<int>(BUTTONNAME::arrow_left_)].size_.x / 2) + (button_widspace_ * 2), playguid_pos_.y };
	button_[static_cast<int>(BUTTONNAME::arrow_right_)].size_ = { 36,72 };
	button_[static_cast<int>(BUTTONNAME::arrow_right_)].pos_ = { playguid_pos_.x + (playguid_size_.x / 2) - (button_[static_cast<int>(BUTTONNAME::arrow_right_)].size_.x / 2) - (button_widspace_ * 2), playguid_pos_.y };
	button_[static_cast<int>(BUTTONNAME::gameguid_draw_)].size_ = button_normal_size_;
	button_[static_cast<int>(BUTTONNAME::gameguid_draw_)].pos_ = { DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2 };

	//�}�E�X�ƃ{�^�������������se�ǂݍ���
	se_buttonchoice_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("ButtonChoice");
	//�{�^�����N���b�N��������se�ǂݍ���
	se_buttonclick_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("ButtonClick");
}

UIManager::~UIManager() {
	DeleteSoundMem(se_buttonchoice_);
	DeleteSoundMem(se_buttonclick_);
}

void UIManager::UI_init_TitleScene() {
	//�Q�[���X�^�[�g�A��Փx�I���摜�ǂݍ���
	button_[static_cast<int>(BUTTONNAME::game_start_)].graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("Game_Start");
	button_[static_cast<int>(BUTTONNAME::game_easy_)].graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("Game_Easy");
	button_[static_cast<int>(BUTTONNAME::game_normal_)].graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("Game_Normal");
	button_[static_cast<int>(BUTTONNAME::game_hard_)].graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("Game_Hard");
	button_[static_cast<int>(BUTTONNAME::return_)].graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("GameMenu_Return");
	//�T�C�Y�ݒ�
	button_[static_cast<int>(BUTTONNAME::game_start_)].size_ = button_normal_size_;
	button_[static_cast<int>(BUTTONNAME::game_easy_)].size_ = button_mini_size_;
	button_[static_cast<int>(BUTTONNAME::game_normal_)].size_ = button_mini_size_;
	button_[static_cast<int>(BUTTONNAME::game_hard_)].size_ = button_mini_size_;
	button_[static_cast<int>(BUTTONNAME::return_)].size_ = button_normal_size_;
	//���W�ݒ�
	button_[static_cast<int>(BUTTONNAME::game_start_)].pos_ = { (DXE_WINDOW_WIDTH / 2), title_butotn_pos_y_ - (button_heispace_ / 2) };
	button_[static_cast<int>(BUTTONNAME::game_easy_)].pos_ = { (DXE_WINDOW_WIDTH / 2) - (button_[static_cast<int>(BUTTONNAME::game_easy_)].size_.x + button_widspace_), title_butotn_pos_y_ };
	button_[static_cast<int>(BUTTONNAME::game_normal_)].pos_ = { DXE_WINDOW_WIDTH / 2,title_butotn_pos_y_ };
	button_[static_cast<int>(BUTTONNAME::game_hard_)].pos_ = { (DXE_WINDOW_WIDTH / 2) + (button_[static_cast<int>(BUTTONNAME::game_hard_)].size_.x + button_widspace_), title_butotn_pos_y_ };
	button_[static_cast<int>(BUTTONNAME::return_)].pos_ = title_button_return_;
	button_[static_cast<int>(BUTTONNAME::gameguid_draw_)].pos_ = guid_pos_title_;
	//�n�߂ɕ\������
	draw_playguid_ = playguid_page1_hdl_;
}

void UIManager::UI_Update_TitleScene(float delta_time) {
	//�^�C�g��ui�V�[�P���X
	title_sequence_.update(delta_time);
}

void UIManager::UI_init_PlayScene(float protectobj_hp, const std::vector<ITEMTYPE>& playeritem_list) {
	playeritem_list_ = playeritem_list;

	//hp�����l�ݒ�
	hp_init_ = protectobj_hp;
	//hp�������̃u���p
	hpblur_dec_jud_ = protectobj_hp;
	//hp�o�[�̉摜�ǂݍ���
	hpbar_graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("HPBAR");
	hpbar50_graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("HPBAR_50");
	hpbar20_graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("HPBAR_20");
	//hp�o�[�̌��̉摜�ǂݍ���
	backgraph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("HPBAR_BACK");
	//�\������hpbar�̉摜�����ݒ�
	draw_graph_hdl_ = hpbar_graph_hdl_;
	//�Q�[���I�[�o�[�̉摜�ǂݍ���
	gameover_graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("GAMEOVER");
	gameend_graph_hdl_ = gameover_graph_hdl_;
	//�Q�[���N���A�̉摜�ǂݍ���
	gameclear_graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("GAMECLEAR");
	//�D�̑ϋv�l50���ȉ��̃X�N���[���G�t�F�N�g
	screeneffect_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("HitEffect_Screen");

	//���j���[��ʔw�i�ǂݍ���
	menu_background_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("GameMenu_Back");
	//���j���[�I���{�^���ǂݍ���
	button_[static_cast<int>(BUTTONNAME::return_)].graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("GameMenu_Return");
	//�Q�[���r���I���m�F�摜
	game_midend_conf_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("GameMidEnd_Conf");
	//�Q�[���r���I���{�^���摜�ǂݍ���
	button_[static_cast<int>(BUTTONNAME::gameminend_draw_)].graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("GameMidEnd_Button");
	button_[static_cast<int>(BUTTONNAME::gamemidend_no_)].graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("GameMidEnd_No");
	button_[static_cast<int>(BUTTONNAME::gamemidend_yes_)].graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("GameMidEnd_Yes");
	//�{�^���T�C�Y�ݒ�
	button_[static_cast<int>(BUTTONNAME::return_)].size_ = button_normal_size_;
	button_[static_cast<int>(BUTTONNAME::gameminend_draw_)].size_ = button_normal_size_;
	button_[static_cast<int>(BUTTONNAME::gamemidend_no_)].size_ = button_mini_size_;
	button_[static_cast<int>(BUTTONNAME::gamemidend_yes_)].size_ = button_mini_size_;
	//�{�^�����W�ݒ�
	button_[static_cast<int>(BUTTONNAME::return_)].pos_ = { (DXE_WINDOW_WIDTH / 2), (DXE_WINDOW_HEIGHT / 2) + button_heispace_ };
	button_[static_cast<int>(BUTTONNAME::gameminend_draw_)].pos_ = { (DXE_WINDOW_WIDTH / 2), (DXE_WINDOW_HEIGHT / 2) - button_heispace_ };
	button_[static_cast<int>(BUTTONNAME::gamemidend_no_)].pos_ = { game_midend_conf_pos_.x - (button_[static_cast<int>(BUTTONNAME::gamemidend_no_)].size_.x / 2) - button_widspace_,
		game_midend_conf_pos_.y + (game_midend_conf_size_.y / 2) - button_[static_cast<int>(BUTTONNAME::gamemidend_no_)].size_.y - (button_widspace_ * 2) };
	button_[static_cast<int>(BUTTONNAME::gamemidend_yes_)].pos_ = { game_midend_conf_pos_.x + (button_[static_cast<int>(BUTTONNAME::gamemidend_yes_)].size_.x / 2) + button_widspace_,
		game_midend_conf_pos_.y + (game_midend_conf_size_.y / 2) - button_[static_cast<int>(BUTTONNAME::gamemidend_yes_)].size_.y - (button_widspace_ * 2) };

	//�v���C���[�����A�C�e���摜�ǂݍ���  
	reditem_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("ItemRed");
	blueitem_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("ItemBlue");
	grerenitem_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("ItemGreen");
	noneitem_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("ItemNone");
	//�v���C���[�����A�C�e���\�����W
	for (int i = 0; i < itemdraw_max_; i++) {
		itemdraw_pos_[i] = { (leftend_ + (itemdraw_size_ / 2)) + (itemdraw_size_ * i), (lowright_pos_.y + (itemdraw_size_ / 2) + ui_interval_) };
	}
	//���j�X�g�b�N�\�����W
	bombstock_pos_ = { leftend_, (itemdraw_pos_[0].y + (itemdraw_size_ / 2) + ui_interval_) };

	//�n�߂ɕ\������
	draw_playguid_ = playguid_page1_hdl_;
}

void UIManager::UI_Update_PlayScene(float delta_time, const float& protectobj_hp) {
	//hp�o�[�̒����䗦�v�Z
	bar_rario_ = protectobj_hp / hp_init_;
	//hp�o�[�̒����X�V
	hp_rightpos_x_ = barlength_ * bar_rario_;

	//hp�o�[�̃u��
	Hpbar_blur(delta_time, protectobj_hp);

	//hpbar�̉摜�ύX
	//50%�ȏ�Ő�
	if (bar_rario_ > hpbar_yellow_) {
		draw_graph_hdl_ = hpbar_graph_hdl_;
	}
	//50%~20%�ŉ��F
	else if (bar_rario_ <= hpbar_yellow_ && bar_rario_ > hpbar_red_) {
		draw_graph_hdl_ = hpbar50_graph_hdl_;

		//�X�N���[���G�t�F�N�g�̎��Ԃ��Z�b�g
		screeneffect_time_ = effecttime50_;
	}
	//20%�ȉ��Ő�
	else if (bar_rario_ <= hpbar_red_) {
		draw_graph_hdl_ = hpbar20_graph_hdl_;

		//�X�N���[���G�t�F�N�g�̎��Ԃ�ύX
		screeneffect_time_ = effecttime20_;
	}
	else {
		draw_graph_hdl_ = hpbar_graph_hdl_;
	}

	//�X�N���[���G�t�F�N�g��alpha�l�ݒ�
	screeneffect_alpha_ = GraphBlink(delta_time, screeneffect_time_);
}

void UIManager::Draw_hpbar() {
	//hp�o�[�̌��̉摜�`��
	DrawExtendGraph((upleft_pos_.x + hpbar_offset_.x), (upleft_pos_.y + hpbar_offset_.y),
		(lowright_pos_.x + hpbar_offset_.x), (lowright_pos_.y + hpbar_offset_.y), backgraph_hdl_, false);

	//hp�o�[�`��
	int left_draw_pos = static_cast<int>(hp_leftpos_x_) + leftend_, right_draw_pos = hp_rightpos_x_ + leftend_;
	if (right_draw_pos >= left_draw_pos) {
		DrawExtendGraph((left_draw_pos + hpbar_offset_.x), (upleft_pos_.y + hpbar_offset_.y),
			(right_draw_pos + hpbar_offset_.x), (lowright_pos_.y + hpbar_offset_.y), draw_graph_hdl_, false);
	}

	//�O�g�̐��`��
	DrawBox((upleft_pos_.x + hpbar_offset_.x), (upleft_pos_.y + hpbar_offset_.y),
		(lowright_pos_.x + hpbar_offset_.x), (lowright_pos_.y + hpbar_offset_.y), -1, false);

	int orifontsize = GetFontSize();
	SetFontSize(fontsize_hpbar_name_);
	DrawStringEx(10, 50, -1, "%s", "�D�̑ϋv�l");
	SetFontSize(orifontsize);
}

void UIManager::Hpbar_blur(float delta_time, const float& protectobj_hp) {
	//hp�����������𔻒�
	if (hpblur_dec_jud_ != protectobj_hp && !is_hpblur_) {
		hpblur_dec_jud_ = protectobj_hp;

		is_hpblur_ = true;
	}
	else {
		hpblur_dec_jud_ = protectobj_hp;
	}

	if (is_hpblur_) {
		hpblur_count_ += delta_time;

		if (hpblur_count_ >= hpblur_interval_) {
			//�J�E���g���Z�b�g
			hpblur_count_ = 0;
			//�S��u������I��
			if (blur_index_ >= blur_num_) {
				blur_index_ = 0;
				is_hpblur_ = false;
				//�u���̒l���Z�b�g
				hpbar_offset_ = { 0,0 };
				return;
			}
			//�u���̒l���Z�b�g
			hpbar_offset_ = hpbar_blur_[blur_index_];
			//�u���̉񐔃J�E���g
			blur_index_++;
		}
	}
}

void UIManager::Draw_ScreenEffect() {
	//hp_50%�ȉ��ŃX���[���G�t�F�N�g�\��
	if (bar_rario_ <= hpbar_yellow_) {
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, static_cast<int>(screeneffect_alpha_));
		DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, screeneffect_hdl_, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha_max_);
	}
}

void UIManager::Draw_timer(const float& gametime) {
	gametime_ = gametime;

	int orifontsize = GetFontSize();
	//�t�H���g�T�C�Y�ݒ�
	SetFontSize(fontsize_timer_);
	int timer_min = static_cast<int>(gametime_ / 60);
	int	timer_sec = (int)gametime_ % 60;

	//�b�̃[���p�f�B���O
	std::ostringstream timestream;
	timestream << std::setw(2) << std::setfill('0') << timer_sec;
	std::string sec = timestream.str();

	//�`��
	DrawStringEx(gametime_pos_.x, gametime_pos_.y, -1, "%d:%s", timer_min, sec.c_str());
	//���̃t�H���g�T�C�Y�ɖ߂�
	SetFontSize(orifontsize);

	//������̒������擾���Ē����ɑ�����
	str_len_ = static_cast<int>(strlen("%d:%d"));
	str_wid_ = GetDrawStringWidth("%d:%d", str_len_);
	gametime_pos_.x = ((DXE_WINDOW_WIDTH / 2) - (str_wid_ / 2));
}

void UIManager::Draw_gameend(int gameend_type) {
	if (gameend_type == static_cast<int>(ENDTYPE::gameover)) {
		gameend_graph_hdl_ = gameover_graph_hdl_;
	}
	else if (gameend_type == static_cast<int>(ENDTYPE::gameclear)) {
		gameend_graph_hdl_ = gameclear_graph_hdl_;
	}

	DrawRotaGraph((DXE_WINDOW_WIDTH / 2), (DXE_WINDOW_HEIGHT / 2), 1.0f, 0, gameend_graph_hdl_, true);
}

void UIManager::Draw_PlayGuid() {
	//�v���C�K�C�h�\��
	DrawRotaGraph(playguid_pos_.x, playguid_pos_.y, 1.0f, 0, draw_playguid_, false);
	//����{�^���\��
	DrawRotaGraph(button_[static_cast<int>(BUTTONNAME::close_)].pos_.x, button_[static_cast<int>(BUTTONNAME::close_)].pos_.y,
		button_[static_cast<int>(BUTTONNAME::close_)].graph_ext_, 0, button_[static_cast<int>(BUTTONNAME::close_)].graph_hdl_, false);
	//��󍶉摜�\��
	DrawRotaGraph(button_[static_cast<int>(BUTTONNAME::arrow_left_)].pos_.x, button_[static_cast<int>(BUTTONNAME::arrow_left_)].pos_.y,
		button_[static_cast<int>(BUTTONNAME::arrow_left_)].graph_ext_, 0, button_[static_cast<int>(BUTTONNAME::arrow_left_)].graph_hdl_, false);
	//���E�摜�\��
	DrawRotaGraph(button_[static_cast<int>(BUTTONNAME::arrow_right_)].pos_.x, button_[static_cast<int>(BUTTONNAME::arrow_right_)].pos_.y,
		button_[static_cast<int>(BUTTONNAME::arrow_right_)].graph_ext_, 0, button_[static_cast<int>(BUTTONNAME::arrow_right_)].graph_hdl_, false);
}

void UIManager::Update_PlayGuid() {
	//�y�[�W�؂�ւ�
	if (IsCursor_Button(static_cast<int>(BUTTONNAME::arrow_left_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		if (draw_playguid_ == playguid_page1_hdl_) {
			draw_playguid_ = playguid_page2_hdl_;
		}
		else if (draw_playguid_ == playguid_page2_hdl_) {
			draw_playguid_ = playguid_page1_hdl_;
		}

		//se�Đ�
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}
	if (IsCursor_Button(static_cast<int>(BUTTONNAME::arrow_right_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		if (draw_playguid_ == playguid_page1_hdl_) {
			draw_playguid_ = playguid_page2_hdl_;
		}
		else if (draw_playguid_ == playguid_page2_hdl_) {
			draw_playguid_ = playguid_page1_hdl_;
		}

		//se�Đ�
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}
}

float UIManager::GraphBlink(float delta_time, float blink_time) {
	blink_count_ += delta_time;
	float alpha = 0.0f;
	//���X�ɔZ��
	if (blink_change_) {
		alpha = (blink_count_ / blink_time * alpha_max_);
		if (alpha >= static_cast<int>(alpha_max_)) {
			blink_change_ = false;
			blink_count_ = 0.0f;
		}
	}
	//���X�ɔ���
	if (!blink_change_) {
		alpha = static_cast<int>(alpha_max_) - (blink_count_ / blink_time * alpha_max_);
		if (alpha <= 0) {
			blink_change_ = true;
			blink_count_ = 0.0f;
		}
	}

	return alpha;
}

void UIManager::Draw_PlayerItem(const std::vector<ITEMTYPE>& playeritem_list) {
	//�A�C�e���̘g�\��
	for (int i = 0; i < itemdraw_max_; i++) {
		DrawRotaGraph(itemdraw_pos_[i].x, itemdraw_pos_[i].y, 1.0f, 0, noneitem_hdl_, true);
	}

	//�����A�C�e���\��
	for (int i = 0; i < playeritem_list.size(); i++) {
		//�ԕ\��
		if (playeritem_list[i] == ITEMTYPE::Red) {
			DrawRotaGraph(itemdraw_pos_[i].x, itemdraw_pos_[i].y, 1.0f, 0, reditem_hdl_, true);
		}
		//�\��
		else if (playeritem_list[i] == ITEMTYPE::Blue) {
			DrawRotaGraph(itemdraw_pos_[i].x, itemdraw_pos_[i].y, 1.0f, 0, blueitem_hdl_, true);
		}
		//�Ε\��
		else if (playeritem_list[i] == ITEMTYPE::Green) {
			DrawRotaGraph(itemdraw_pos_[i].x, itemdraw_pos_[i].y, 1.0f, 0, grerenitem_hdl_, true);
		}
	}

	int orifontsize = GetFontSize();
	SetFontSize(fontsize_hpbar_name_);
	DrawStringEx(10, (itemdraw_pos_[0].y - ui_interval_), -1, "%s", "�����A�C�e��");
	SetFontSize(orifontsize);
}

void UIManager::Draw_Bombstock(const int& bombstock) {
	bombstock_ = bombstock;

	int orifontsize = GetFontSize();

	//���j�X�g�b�N�\��
	SetFontSize(fontsize_hpbar_name_);
	DrawStringEx(10, (bombstock_pos_.y + ui_interval_), -1, bombstock_name_.c_str());
	bombstock_str_len_ = static_cast<int>(strlen(bombstock_name_.c_str()));
	bombstock_str_wid_ = GetDrawStringWidth(bombstock_name_.c_str(), bombstock_str_len_);

	SetFontSize(fontsize_bombstock_);
	DrawStringEx((bombstock_str_wid_ + ui_interval_), bombstock_pos_.y, -1, "�~%d", bombstock_);

	SetFontSize(orifontsize);
}

void UIManager::Update_PlayMenu(float delta_time) {
	//���j���[�\���t���Otrue
	is_menu_ = true;

	//���j���[��ʃV�[�P���X
	menu_sequence_.update(delta_time);
}

void UIManager::Draw_PlayMenu() {
	//�w�i�\��
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, menu_background_, true);
	if (menu_sequence_.isComparable(&UIManager::seq_playscene_menu)) {
		//�r���I���{�^���\��
		Draw_Button(static_cast<int>(BUTTONNAME::gameminend_draw_));
		//�Q�[���K�C�h�{�^���\��
		Draw_PlayGuid_Button(button_[static_cast<int>(BUTTONNAME::gameguid_draw_)].pos_);
		//���j���[�I���{�^���\��
		Draw_Button(static_cast<int>(BUTTONNAME::return_));
	}
	else if (menu_sequence_.isComparable(&UIManager::seq_playscene_midend)) {
		Draw_MidEndConf();
	}
	else if (menu_sequence_.isComparable(&UIManager::seq_playscene_guid)) {
		Draw_PlayGuid();
	}
}

void UIManager::Draw_TitleUI() {
	if (title_sequence_.isComparable(&UIManager::seq_title)) {
		//�Q�[���K�C�h�\���{�^��
		Draw_PlayGuid_Button(guid_pos_title_);
		//�Q�[���X�^�[�g�A���x���I���{�^��
		Draw_Button(static_cast<int>(BUTTONNAME::game_start_));
	}
	else if (title_sequence_.isComparable(&UIManager::seq_title_guid)) {
		Draw_PlayGuid();
	}
	else if (title_sequence_.isComparable(&UIManager::seq_title_start)) {
		Draw_GameLevel();
		Draw_Button(static_cast<int>(BUTTONNAME::return_));
	}
}

void UIManager::Draw_GameLevel() {
	//easy�\��
	Draw_Button(static_cast<int>(BUTTONNAME::game_easy_));
	//normal�\��
	Draw_Button(static_cast<int>(BUTTONNAME::game_normal_));
	//hard�\��
	Draw_Button(static_cast<int>(BUTTONNAME::game_hard_));
}

void UIManager::Draw_Button(int buttonname) {
	DrawRotaGraph(button_[buttonname].pos_.x, button_[buttonname].pos_.y, button_[buttonname].graph_ext_, 0, button_[buttonname].graph_hdl_, true);
}

void UIManager::Draw_MidEndConf() {
	//�r���I���m�F�\��
	DrawRotaGraph(game_midend_conf_pos_.x, game_midend_conf_pos_.y, 1.0f, 0, game_midend_conf_hdl_, true);
	//yes�{�^���\��
	DrawRotaGraph(button_[static_cast<int>(BUTTONNAME::gamemidend_yes_)].pos_.x, button_[static_cast<int>(BUTTONNAME::gamemidend_yes_)].pos_.y,
		button_[static_cast<int>(BUTTONNAME::gamemidend_yes_)].graph_ext_, 0, button_[static_cast<int>(BUTTONNAME::gamemidend_yes_)].graph_hdl_, true);
	//no�{�^���\��
	DrawRotaGraph(button_[static_cast<int>(BUTTONNAME::gamemidend_no_)].pos_.x, button_[static_cast<int>(BUTTONNAME::gamemidend_no_)].pos_.y,
		button_[static_cast<int>(BUTTONNAME::gamemidend_no_)].graph_ext_, 0, button_[static_cast<int>(BUTTONNAME::gamemidend_no_)].graph_hdl_, true);
}

void UIManager::Draw_PlayGuid_Button(tnl::Vector2i pos) {
	DrawRotaGraph(pos.x, pos.y, button_[static_cast<int>(BUTTONNAME::gameguid_draw_)].graph_ext_, 0, button_[static_cast<int>(BUTTONNAME::gameguid_draw_)].graph_hdl_, true);
}

bool UIManager::IsCursor_Button(int buttonname) {
	//�}�E�X�J�[�\��������Ă���� true ��Ԃ�
	if (tnl::IsIntersectPointRect(static_cast<int>(tnl::Input::GetMousePosition().x), static_cast<int>(tnl::Input::GetMousePosition().y),
		button_[buttonname].pos_.x, button_[buttonname].pos_.y, button_[buttonname].size_.x, button_[buttonname].size_.y)) {
		//�{�^����傫���\������
		button_[buttonname].graph_ext_ = button_[buttonname].graph_overlapext_;

		//se�Đ�
		if (!button_[buttonname].is_se_buttonchoice_) {
			PlaySoundMem(se_buttonchoice_, DX_PLAYTYPE_BACK);
		}
		button_[buttonname].is_se_buttonchoice_ = true;

		return true;
	}
	else {
		//�{�^���T�C�Y��ʏ�ɖ߂�
		button_[buttonname].graph_ext_ = button_[buttonname].graph_nomalext_;

		//se�Đ��t���O��false��
		button_[buttonname].is_se_buttonchoice_ = false;

		return false;
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------
//�^�C�g���V�[����ui�V�[�P���X

bool UIManager::seq_title(float delta_time) {
	//�Q�[�����x���I���Ɉړ�
	if (IsCursor_Button(static_cast<int>(BUTTONNAME::game_start_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		title_sequence_.change(&UIManager::seq_title_start);

		//se�Đ�
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}
	//�v���C�K�C�h�V�[�P���X�ړ�
	else if (IsCursor_Button(static_cast<int>(BUTTONNAME::gameguid_draw_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		title_sequence_.change(&UIManager::seq_title_guid);

		//se�Đ�
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}

	return true;
}

bool UIManager::seq_title_guid(float delta_title) {
	//�y�[�W�؂�ւ�
	Update_PlayGuid();

	//�v���C�K�C�h�����
	if (IsCursor_Button(static_cast<int>(BUTTONNAME::close_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		title_sequence_.change(&UIManager::seq_title);

		//se�Đ�
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}

	return true;
}

bool UIManager::seq_title_start(float delta_title) {
	//���x���I�������
	if (IsCursor_Button(static_cast<int>(BUTTONNAME::return_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		title_sequence_.change(&UIManager::seq_title);

		//se�Đ�
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}
	//easy�Q�[���Ɉړ�
	else if (IsCursor_Button(static_cast<int>(BUTTONNAME::game_easy_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		is_game_easy_ = true;

		//se�Đ�
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}
	//normal�Q�[���Ɉړ�
	else if (IsCursor_Button(static_cast<int>(BUTTONNAME::game_normal_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		is_game_normal_ = true;

		//se�Đ�
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}
	//hard�Q�[���Ɉړ�
	else if (IsCursor_Button(static_cast<int>(BUTTONNAME::game_hard_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		is_game_hard_ = true;

		//se�Đ�
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------------------------------
//�v���C�V�[���̃��j���[��ʃV�[�P���X

bool UIManager::seq_playscene_menu(float delta_time) {
	//�Q�[�����j���[���I�����A�Q�[���v���C�ɖ߂�
	if (IsCursor_Button(static_cast<int>(BUTTONNAME::return_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		is_menu_ = false;

		//se�Đ�
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}
	//�v���C�K�C�h�V�[�P���X�ړ�
	else if (IsCursor_Button(static_cast<int>(BUTTONNAME::gameguid_draw_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		menu_sequence_.change(&UIManager::seq_playscene_guid);

		//se�Đ�
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}
	//�r���I���V�[�P���X�ړ�
	else if (IsCursor_Button(static_cast<int>(BUTTONNAME::gameminend_draw_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		menu_sequence_.change(&UIManager::seq_playscene_midend);

		//se�Đ�
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}

	return true;
}

bool UIManager::seq_playscene_midend(float delta_time) {
	//�Q�[���r���I��
	if (IsCursor_Button(static_cast<int>(BUTTONNAME::gamemidend_yes_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		is_gamemidend_ = true;

		//se�Đ�
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}
	//���j���[�n�߂̉�ʂɖ߂�
	else if (IsCursor_Button(static_cast<int>(BUTTONNAME::gamemidend_no_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		menu_sequence_.change(&UIManager::seq_playscene_menu);

		//se�Đ�
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}

	return true;
}

bool UIManager::seq_playscene_guid(float delta_time) {
	//�y�[�W�؂�ւ�
	Update_PlayGuid();

	//�v���C�K�C�h�����
	if (IsCursor_Button(static_cast<int>(BUTTONNAME::close_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		menu_sequence_.change(&UIManager::seq_playscene_menu);

		//se�Đ�
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}

	return true;
}