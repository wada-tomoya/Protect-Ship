#include "UI.h"

UI::UI(const float& protectobj_hp, const float& gametime, std::vector<ITEMTYPE>& playeritem_list, const int& bombstock) :
		protectobj_hp_(protectobj_hp), gametime_(gametime), playeritem_list_(playeritem_list), bombstock_(bombstock){
	//hp�����l�ݒ�
	hp_init_ = protectobj_hp_;
	//hp�������̃u���p
	hpblur_dec_jud_ = protectobj_hp_;
	//hp�o�[�̉摜�ǂݍ���
	hpbar_graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("HPBAR");
	hpbar50_graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("HPBAR_50");
	hpbar20_graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("HPBAR_20");
	//hp�o�[�̌��̉摜�ǂݍ���
	backgraph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("HPBAR_BACK");
	//�Q�[���I�[�o�[�̉摜�ǂݍ���
	gameover_graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("GAMEOVER");
	gameend_graph_hdl_ = gameover_graph_hdl_;
	//�Q�[���N���A�̉摜�ǂݍ���
	gameclear_graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("GAMECLEAR");

	screeneffect_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("HitEffect_Screen");

	//�\������hpbar�̉摜�����ݒ�
	draw_graph_hdl_ = hpbar_graph_hdl_;

	//�v���C���[�����A�C�e���摜�ǂݍ���  
	reditem_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("ItemRed");
	blueitem_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("ItemBlue");
	grerenitem_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("ItemGreen");
	noneitem_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("ItemNone");
	//�v���C���[�����A�C�e���\�����W
	for (int i = 0; i < itemdraw_max_; i++) {
		itemdraw_pos_[i] = { (leftend_ + (itemdraw_size_ / 2)) + (itemdraw_size_ * i), (lowright_pos_.y + (itemdraw_size_ / 2) + ui_interval_), 0 };
	}

	//���j�X�g�b�N�\�����W
	bombstock_pos_ = { leftend_, (itemdraw_pos_[0].y + (itemdraw_size_ / 2) + ui_interval_), 0 };

	//�K�C�h�֌W
	playguid_page1_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("PlayGuide_Page1");
	playguid_page2_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("PlayGuide_Page2");
	arrow_left_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("Arrow_Left");
	arrow_right_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("Arrow_Right");
	close_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("Close");
	draw_playguid_ = playguid_page1_hdl_;
}

UI::~UI() {

}

void UI::UI_Update(float delta_time) {
	tnl_sequence_.update(delta_time);
}

void UI::UI_Draw(std::shared_ptr<Camera> camera) {
	//hp_50%�ȉ��ŃX���[���G�t�F�N�g�\��
	if (bar_rario_ <= 0.5f) {
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, static_cast<int>(screeneffect_alpha_));
		DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, screeneffect_hdl_, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	
	//hp�o�[�\��
	Draw_hpbar();
	//�������ԕ\��
	Draw_timer();
	//�v���C���[�����A�C�e���\��
	Draw_PlayerItem();
	//���j�X�g�b�N�\��
	Draw_Bombstock();
}

void UI::Draw_hpbar() {
	//hp�o�[�̌��̉摜�`��
	DrawExtendGraph(static_cast<int>(upleft_pos_.x + hpbar_offset_.x), static_cast<int>(upleft_pos_.y + hpbar_offset_.y),
		static_cast<int>(lowright_pos_.x + hpbar_offset_.x), static_cast<int>(lowright_pos_.y + hpbar_offset_.y),backgraph_hdl_, false);

	//hp�o�[�`��
	float left_draw_pos = hp_leftpos_x_ + leftend_, right_draw_pos = hp_rightpos_x_ + leftend_;
	if (right_draw_pos >= left_draw_pos) {
		DrawExtendGraph(static_cast<int>(left_draw_pos + hpbar_offset_.x), static_cast<int>(upleft_pos_.y + hpbar_offset_.y), 
			static_cast<int>(right_draw_pos + hpbar_offset_.x), static_cast<int>(lowright_pos_.y + hpbar_offset_.y),draw_graph_hdl_, false);
	}
	
	//�O�g�̐��`��
	DrawBox(static_cast<int>(upleft_pos_.x + hpbar_offset_.x), static_cast<int>(upleft_pos_.y + hpbar_offset_.y), 
		static_cast<int>(lowright_pos_.x + hpbar_offset_.x), static_cast<int>(lowright_pos_.y + hpbar_offset_.y), -1, false);
	
	int orifontsize = GetFontSize();
	SetFontSize(fontsize_hpbar_name_);
	DrawStringEx(10, 50, -1, "%s", "�D�̑ϋv�l");
	SetFontSize(orifontsize);
}

void UI::Hpbar_blur(float delta_time){
	//hp�����������𔻒�
	if (hpblur_dec_jud_ != protectobj_hp_ && !is_hpblur_) {
		hpblur_dec_jud_ = protectobj_hp_;

		is_hpblur_ = true;
	}
	else {
		hpblur_dec_jud_ = protectobj_hp_;
	}

	if (is_hpblur_) {
;		hpblur_count_ += delta_time;

		if (hpblur_count_ >= hpblur_interval_) {
			//�J�E���g���Z�b�g
			hpblur_count_ = 0;
			//�S��u������I��
			if (blur_index_ >= 4) {
				blur_index_ = 0;
				is_hpblur_ = false;
				//�u���̒l���Z�b�g
				hpbar_offset_ = { 0,0,0 };
				return;
			}
			//�u���̒l���Z�b�g
			hpbar_offset_ = hpbar_blur_[blur_index_];
			//�u���̉񐔃J�E���g
			blur_index_++;
		}
	}
}

void UI::Draw_timer() {
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
	gametime_pos_.x = static_cast<float>((DXE_WINDOW_WIDTH / 2) - (str_wid_ / 2));
}

void UI::Draw_gameend(int gameend_type) {
	if (gameend_type == 1) {
		gameend_graph_hdl_ = gameover_graph_hdl_;
	}
	else if (gameend_type == 2) {
		gameend_graph_hdl_ = gameclear_graph_hdl_;
	}

	DrawRotaGraph((DXE_WINDOW_WIDTH / 2), (DXE_WINDOW_HEIGHT / 2), 1.0f, 0, gameend_graph_hdl_, true);
}

void UI::Draw_PlayGuid(){
	//�v���C�K�C�h�\��
	DrawRotaGraph(static_cast<int>(playguid_pos_.x), static_cast<int>(playguid_pos_.y), 1.0f, 0, draw_playguid_, false);
	//����{�^���\��
	DrawRotaGraph(static_cast<int>(close_pos_.x), static_cast<int>(close_pos_.y), 1.0f, 0, close_hdl_, false);
	//��󍶉摜�\��
	DrawRotaGraph(static_cast<int>(arrowleft_pos_.x), static_cast<int>(arrowleft_pos_.y), 1.0f, 0, arrow_left_hdl_, false);
	//���E�摜�\��
	DrawRotaGraph(static_cast<int>(arrowright_pos_.x), static_cast<int>(arrowright_pos_.y), 1.0f, 0, arrow_right_hdl_, false);
}

void UI::Update_PlayGuid(){
	//�y�[�W�؂�ւ�
	if (Is_Cursor_LeftArrwo() && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		if (draw_playguid_ == playguid_page1_hdl_) {
			draw_playguid_ = playguid_page2_hdl_;
		}
		else if (draw_playguid_ == playguid_page2_hdl_) {
			draw_playguid_ = playguid_page1_hdl_;
		}
	}

	if (Is_Cursor_RightArrow() && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		if (draw_playguid_ == playguid_page1_hdl_) {
			draw_playguid_ = playguid_page2_hdl_;
		}
		else if (draw_playguid_ == playguid_page2_hdl_) {
			draw_playguid_ = playguid_page1_hdl_;
		}
	}

}

float UI::GraphBlink(float delta_time, float blink_time) {
	blink_count_ += delta_time;
	float alpha = 0.0f;
	//���X�ɔZ��
	if (blink_change_) {
		alpha = (blink_count_ / blink_time * 255.0f);
		if (alpha >= 255) {
			blink_change_ = false;
			blink_count_ = 0.0f;
		}
	}
	//���X�ɔ���
	if (!blink_change_) {
		alpha = 255 - (blink_count_ / blink_time * 255.0f);
		if (alpha <= 0) {
			blink_change_ = true;
			blink_count_ = 0.0f;
		}
	}

	return alpha;
}

void UI::Draw_PlayerItem(){
	//�A�C�e���̘g�\��
	for (int i = 0; i < itemdraw_max_; i++) {
		DrawRotaGraph(static_cast<int>(itemdraw_pos_[i].x), static_cast<int>(itemdraw_pos_[i].y), 1.0f, 0, noneitem_hdl_, true);
	}

	//�����A�C�e���\��
	for (int i = 0; i < playeritem_list_.size(); i++) {
		//�ԕ\��
		if (playeritem_list_[i] == ITEMTYPE::Red) {
			DrawRotaGraph(static_cast<int>(itemdraw_pos_[i].x), static_cast<int>(itemdraw_pos_[i].y), 1.0f, 0, reditem_hdl_, true);
		}
		//�\��
		else if (playeritem_list_[i] == ITEMTYPE::Blue) {
			DrawRotaGraph(static_cast<int>(itemdraw_pos_[i].x), static_cast<int>(itemdraw_pos_[i].y), 1.0f, 0, blueitem_hdl_, true);
		}
		//�Ε\��
		else if (playeritem_list_[i] == ITEMTYPE::Green) {
			DrawRotaGraph(static_cast<int>(itemdraw_pos_[i].x), static_cast<int>(itemdraw_pos_[i].y), 1.0f, 0, grerenitem_hdl_, true);
		}
	}

	int orifontsize = GetFontSize();
	SetFontSize(fontsize_hpbar_name_);
	DrawStringEx(10, static_cast<int>(itemdraw_pos_[0].y - ui_interval_), -1, "%s", "�����A�C�e��");
	SetFontSize(orifontsize);
}

void UI::Draw_Bombstock(){
	//���j�X�g�b�N�\��
	int orifontsize = GetFontSize();

	SetFontSize(fontsize_hpbar_name_);
	DrawStringEx(10, static_cast<int>(bombstock_pos_.y + ui_interval_), -1, bombstock_name_.c_str() );
	bombstock_str_len_ = static_cast<int>(strlen(bombstock_name_.c_str()));
	bombstock_str_wid_ = GetDrawStringWidth(bombstock_name_.c_str(), bombstock_str_len_);

	SetFontSize(fontsize_bombstock_);
	DrawStringEx((bombstock_str_wid_ + static_cast<int>(ui_interval_)), static_cast<int>(bombstock_pos_.y), -1, "�~%d", bombstock_);

	SetFontSize(orifontsize);
}

bool UI::Is_Cursor_close(){
	//����{�^���ƃ}�E�X�J�[�\��������Ă���� true ��Ԃ�
	if (tnl::IsIntersectPointRect(static_cast<int>(tnl::Input::GetMousePosition().x), static_cast<int>(tnl::Input::GetMousePosition().y),
		static_cast<int>(close_pos_.x), static_cast<int>(close_pos_.y), static_cast<int>(close_size_.x), static_cast<int>(close_size_.y))) {
		return true;
	}

	return false;
}

bool UI::Is_Cursor_LeftArrwo(){
	//�y�[�W�߂��荶���}�E�X�J�[�\��������Ă���� true ��Ԃ�
	if (tnl::IsIntersectPointRect(static_cast<int>(tnl::Input::GetMousePosition().x), static_cast<int>(tnl::Input::GetMousePosition().y),
		static_cast<int>(arrowleft_pos_.x), static_cast<int>(arrowleft_pos_.y), static_cast<int>(arrow_size_.x), static_cast<int>(arrow_size_.y))) {
		return true;
	}

	return false;
}

bool UI::Is_Cursor_RightArrow(){
	//�y�[�W�߂���E���}�E�X�J�[�\��������Ă���� true ��Ԃ�
	if (tnl::IsIntersectPointRect(static_cast<int>(tnl::Input::GetMousePosition().x), static_cast<int>(tnl::Input::GetMousePosition().y),
		static_cast<int>(arrowright_pos_.x), static_cast<int>(arrowright_pos_.y), static_cast<int>(arrow_size_.x), static_cast<int>(arrow_size_.y))) {
		return true;
	}

	return false;
}

bool UI::SEQ_Play(const float delta_time) {
	//hp�o�[�̒����䗦�v�Z
	bar_rario_ = protectobj_hp_ / hp_init_;
	//hp�o�[�̒����X�V
	hp_rightpos_x_ = barlength_ * bar_rario_;

	//hp�o�[�̃u��
	Hpbar_blur(delta_time);

	//hpbar�̉摜�ύX
	//50%�ȏ�Ő�
	if (bar_rario_ > 0.5f) {
		draw_graph_hdl_ = hpbar_graph_hdl_;
	}
	//50%~20%�ŉ��F
	else if (bar_rario_ <= 0.5f && bar_rario_ > 0.2f) {
		draw_graph_hdl_ = hpbar50_graph_hdl_;

		//�X�N���[���G�t�F�N�g�̎��Ԃ��Z�b�g
		screeneffect_time_ = effecttime50_;
	}
	//20%�ȉ��Ő�
	else if (bar_rario_ <= 0.2f) {
		draw_graph_hdl_ = hpbar20_graph_hdl_;

		//�X�N���[���G�t�F�N�g�̎��Ԃ�ύX
		screeneffect_time_ = effecttime20_;
	}
	else {
		draw_graph_hdl_ = hpbar_graph_hdl_;
	}

	//�X�N���[���G�t�F�N�g��alpha�l�ݒ�
	screeneffect_alpha_ = GraphBlink(delta_time, screeneffect_time_);

	//�V�[�P���X�ړ�����
	if (bar_rario_ <= 0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		tnl_sequence_.change(&UI::SEQ_END);
	}
	TNL_SEQ_CO_END
}

bool UI::SEQ_END(const float delta_time) {


	TNL_SEQ_CO_END
}