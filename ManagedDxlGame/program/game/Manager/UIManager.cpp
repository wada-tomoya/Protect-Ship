#include "UIManager.h"
#include "../Manager/ResourceManager.h"

UIManager::UIManager() {
	//ガイド関係画像読み込み
	playguid_page1_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("PlayGuide_Page1");
	playguid_page2_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("PlayGuide_Page2");
	button_[static_cast<int>(BUTTONNAME::arrow_left_)].graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("Arrow_Left");
	button_[static_cast<int>(BUTTONNAME::arrow_right_)].graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("Arrow_Right");
	button_[static_cast<int>(BUTTONNAME::close_)].graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("Close");
	button_[static_cast<int>(BUTTONNAME::gameguid_draw_)].graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("GameHelp_Button");
	//ボタン座標、サイズ設定
	button_[static_cast<int>(BUTTONNAME::close_)].size_ = { 40,40 };
	button_[static_cast<int>(BUTTONNAME::close_)].pos_ = { playguid_pos_.x + (playguid_size_.x / 2) - (button_[static_cast<int>(BUTTONNAME::close_)].size_.x / 2) - button_widspace_,
		playguid_pos_.y - (playguid_size_.y / 2) + (button_[static_cast<int>(BUTTONNAME::close_)].size_.y / 2) + button_widspace_ };
	button_[static_cast<int>(BUTTONNAME::arrow_left_)].size_ = { 36,72 };
	button_[static_cast<int>(BUTTONNAME::arrow_left_)].pos_ = { playguid_pos_.x - (playguid_size_.x / 2) + (button_[static_cast<int>(BUTTONNAME::arrow_left_)].size_.x / 2) + (button_widspace_ * 2), playguid_pos_.y };
	button_[static_cast<int>(BUTTONNAME::arrow_right_)].size_ = { 36,72 };
	button_[static_cast<int>(BUTTONNAME::arrow_right_)].pos_ = { playguid_pos_.x + (playguid_size_.x / 2) - (button_[static_cast<int>(BUTTONNAME::arrow_right_)].size_.x / 2) - (button_widspace_ * 2), playguid_pos_.y };
	button_[static_cast<int>(BUTTONNAME::gameguid_draw_)].size_ = button_normal_size_;
	button_[static_cast<int>(BUTTONNAME::gameguid_draw_)].pos_ = { DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2 };

	//マウスとボタンが被った時のse読み込み
	se_buttonchoice_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("ButtonChoice");
	//ボタンをクリックした時のse読み込み
	se_buttonclick_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("ButtonClick");
}

UIManager::~UIManager() {
	DeleteSoundMem(se_buttonchoice_);
	DeleteSoundMem(se_buttonclick_);
}

void UIManager::UI_init_TitleScene() {
	//ゲームスタート、難易度選択画像読み込み
	button_[static_cast<int>(BUTTONNAME::game_start_)].graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("Game_Start");
	button_[static_cast<int>(BUTTONNAME::game_easy_)].graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("Game_Easy");
	button_[static_cast<int>(BUTTONNAME::game_normal_)].graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("Game_Normal");
	button_[static_cast<int>(BUTTONNAME::game_hard_)].graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("Game_Hard");
	button_[static_cast<int>(BUTTONNAME::return_)].graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("GameMenu_Return");
	//サイズ設定
	button_[static_cast<int>(BUTTONNAME::game_start_)].size_ = button_normal_size_;
	button_[static_cast<int>(BUTTONNAME::game_easy_)].size_ = button_mini_size_;
	button_[static_cast<int>(BUTTONNAME::game_normal_)].size_ = button_mini_size_;
	button_[static_cast<int>(BUTTONNAME::game_hard_)].size_ = button_mini_size_;
	button_[static_cast<int>(BUTTONNAME::return_)].size_ = button_normal_size_;
	//座標設定
	button_[static_cast<int>(BUTTONNAME::game_start_)].pos_ = { (DXE_WINDOW_WIDTH / 2), title_butotn_pos_y_ - (button_heispace_ / 2) };
	button_[static_cast<int>(BUTTONNAME::game_easy_)].pos_ = { (DXE_WINDOW_WIDTH / 2) - (button_[static_cast<int>(BUTTONNAME::game_easy_)].size_.x + button_widspace_), title_butotn_pos_y_ };
	button_[static_cast<int>(BUTTONNAME::game_normal_)].pos_ = { DXE_WINDOW_WIDTH / 2,title_butotn_pos_y_ };
	button_[static_cast<int>(BUTTONNAME::game_hard_)].pos_ = { (DXE_WINDOW_WIDTH / 2) + (button_[static_cast<int>(BUTTONNAME::game_hard_)].size_.x + button_widspace_), title_butotn_pos_y_ };
	button_[static_cast<int>(BUTTONNAME::return_)].pos_ = title_button_return_;
	button_[static_cast<int>(BUTTONNAME::gameguid_draw_)].pos_ = guid_pos_title_;
	//始めに表示する
	draw_playguid_ = playguid_page1_hdl_;
}

void UIManager::UI_Update_TitleScene(float delta_time) {
	//タイトルuiシーケンス
	title_sequence_.update(delta_time);
}

void UIManager::UI_init_PlayScene(float protectobj_hp, const std::vector<ITEMTYPE>& playeritem_list) {
	playeritem_list_ = playeritem_list;

	//hp初期値設定
	hp_init_ = protectobj_hp;
	//hp減衰時のブレ用
	hpblur_dec_jud_ = protectobj_hp;
	//hpバーの画像読み込み
	hpbar_graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("HPBAR");
	hpbar50_graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("HPBAR_50");
	hpbar20_graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("HPBAR_20");
	//hpバーの後ろの画像読み込み
	backgraph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("HPBAR_BACK");
	//表示するhpbarの画像初期設定
	draw_graph_hdl_ = hpbar_graph_hdl_;
	//ゲームオーバーの画像読み込み
	gameover_graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("GAMEOVER");
	gameend_graph_hdl_ = gameover_graph_hdl_;
	//ゲームクリアの画像読み込み
	gameclear_graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("GAMECLEAR");
	//船の耐久値50％以下のスクリーンエフェクト
	screeneffect_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("HitEffect_Screen");

	//メニュー画面背景読み込み
	menu_background_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("GameMenu_Back");
	//メニュー終了ボタン読み込み
	button_[static_cast<int>(BUTTONNAME::return_)].graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("GameMenu_Return");
	//ゲーム途中終了確認画像
	game_midend_conf_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("GameMidEnd_Conf");
	//ゲーム途中終了ボタン画像読み込み
	button_[static_cast<int>(BUTTONNAME::gameminend_draw_)].graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("GameMidEnd_Button");
	button_[static_cast<int>(BUTTONNAME::gamemidend_no_)].graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("GameMidEnd_No");
	button_[static_cast<int>(BUTTONNAME::gamemidend_yes_)].graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("GameMidEnd_Yes");
	//ボタンサイズ設定
	button_[static_cast<int>(BUTTONNAME::return_)].size_ = button_normal_size_;
	button_[static_cast<int>(BUTTONNAME::gameminend_draw_)].size_ = button_normal_size_;
	button_[static_cast<int>(BUTTONNAME::gamemidend_no_)].size_ = button_mini_size_;
	button_[static_cast<int>(BUTTONNAME::gamemidend_yes_)].size_ = button_mini_size_;
	//ボタン座標設定
	button_[static_cast<int>(BUTTONNAME::return_)].pos_ = { (DXE_WINDOW_WIDTH / 2), (DXE_WINDOW_HEIGHT / 2) + button_heispace_ };
	button_[static_cast<int>(BUTTONNAME::gameminend_draw_)].pos_ = { (DXE_WINDOW_WIDTH / 2), (DXE_WINDOW_HEIGHT / 2) - button_heispace_ };
	button_[static_cast<int>(BUTTONNAME::gamemidend_no_)].pos_ = { game_midend_conf_pos_.x - (button_[static_cast<int>(BUTTONNAME::gamemidend_no_)].size_.x / 2) - button_widspace_,
		game_midend_conf_pos_.y + (game_midend_conf_size_.y / 2) - button_[static_cast<int>(BUTTONNAME::gamemidend_no_)].size_.y - (button_widspace_ * 2) };
	button_[static_cast<int>(BUTTONNAME::gamemidend_yes_)].pos_ = { game_midend_conf_pos_.x + (button_[static_cast<int>(BUTTONNAME::gamemidend_yes_)].size_.x / 2) + button_widspace_,
		game_midend_conf_pos_.y + (game_midend_conf_size_.y / 2) - button_[static_cast<int>(BUTTONNAME::gamemidend_yes_)].size_.y - (button_widspace_ * 2) };

	//プレイヤー所持アイテム画像読み込み  
	reditem_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("ItemRed");
	blueitem_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("ItemBlue");
	grerenitem_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("ItemGreen");
	noneitem_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("ItemNone");
	//プレイヤー所持アイテム表示座標
	for (int i = 0; i < itemdraw_max_; i++) {
		itemdraw_pos_[i] = { (leftend_ + (itemdraw_size_ / 2)) + (itemdraw_size_ * i), (lowright_pos_.y + (itemdraw_size_ / 2) + ui_interval_) };
	}
	//爆破ストック表示座標
	bombstock_pos_ = { leftend_, (itemdraw_pos_[0].y + (itemdraw_size_ / 2) + ui_interval_) };

	//始めに表示する
	draw_playguid_ = playguid_page1_hdl_;
}

void UIManager::UI_Update_PlayScene(float delta_time, const float& protectobj_hp) {
	//hpバーの長さ比率計算
	bar_rario_ = protectobj_hp / hp_init_;
	//hpバーの長さ更新
	hp_rightpos_x_ = barlength_ * bar_rario_;

	//hpバーのブレ
	Hpbar_blur(delta_time, protectobj_hp);

	//hpbarの画像変更
	//50%以上で青
	if (bar_rario_ > hpbar_yellow_) {
		draw_graph_hdl_ = hpbar_graph_hdl_;
	}
	//50%~20%で黄色
	else if (bar_rario_ <= hpbar_yellow_ && bar_rario_ > hpbar_red_) {
		draw_graph_hdl_ = hpbar50_graph_hdl_;

		//スクリーンエフェクトの時間をセット
		screeneffect_time_ = effecttime50_;
	}
	//20%以下で赤
	else if (bar_rario_ <= hpbar_red_) {
		draw_graph_hdl_ = hpbar20_graph_hdl_;

		//スクリーンエフェクトの時間を変更
		screeneffect_time_ = effecttime20_;
	}
	else {
		draw_graph_hdl_ = hpbar_graph_hdl_;
	}

	//スクリーンエフェクトのalpha値設定
	screeneffect_alpha_ = GraphBlink(delta_time, screeneffect_time_);
}

void UIManager::Draw_hpbar() {
	//hpバーの後ろの画像描画
	DrawExtendGraph((upleft_pos_.x + hpbar_offset_.x), (upleft_pos_.y + hpbar_offset_.y),
		(lowright_pos_.x + hpbar_offset_.x), (lowright_pos_.y + hpbar_offset_.y), backgraph_hdl_, false);

	//hpバー描画
	int left_draw_pos = static_cast<int>(hp_leftpos_x_) + leftend_, right_draw_pos = hp_rightpos_x_ + leftend_;
	if (right_draw_pos >= left_draw_pos) {
		DrawExtendGraph((left_draw_pos + hpbar_offset_.x), (upleft_pos_.y + hpbar_offset_.y),
			(right_draw_pos + hpbar_offset_.x), (lowright_pos_.y + hpbar_offset_.y), draw_graph_hdl_, false);
	}

	//外枠の線描画
	DrawBox((upleft_pos_.x + hpbar_offset_.x), (upleft_pos_.y + hpbar_offset_.y),
		(lowright_pos_.x + hpbar_offset_.x), (lowright_pos_.y + hpbar_offset_.y), -1, false);

	int orifontsize = GetFontSize();
	SetFontSize(fontsize_hpbar_name_);
	DrawStringEx(10, 50, -1, "%s", "船の耐久値");
	SetFontSize(orifontsize);
}

void UIManager::Hpbar_blur(float delta_time, const float& protectobj_hp) {
	//hpが減ったかを判定
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
			//カウントリセット
			hpblur_count_ = 0;
			//４回ブレたら終了
			if (blur_index_ >= blur_num_) {
				blur_index_ = 0;
				is_hpblur_ = false;
				//ブレの値リセット
				hpbar_offset_ = { 0,0 };
				return;
			}
			//ブレの値をセット
			hpbar_offset_ = hpbar_blur_[blur_index_];
			//ブレの回数カウント
			blur_index_++;
		}
	}
}

void UIManager::Draw_ScreenEffect() {
	//hp_50%以下でスリーンエフェクト表示
	if (bar_rario_ <= hpbar_yellow_) {
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, static_cast<int>(screeneffect_alpha_));
		DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, screeneffect_hdl_, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha_max_);
	}
}

void UIManager::Draw_timer(const float& gametime) {
	gametime_ = gametime;

	int orifontsize = GetFontSize();
	//フォントサイズ設定
	SetFontSize(fontsize_timer_);
	int timer_min = static_cast<int>(gametime_ / 60);
	int	timer_sec = (int)gametime_ % 60;

	//秒のゼロパディング
	std::ostringstream timestream;
	timestream << std::setw(2) << std::setfill('0') << timer_sec;
	std::string sec = timestream.str();

	//描画
	DrawStringEx(gametime_pos_.x, gametime_pos_.y, -1, "%d:%s", timer_min, sec.c_str());
	//元のフォントサイズに戻す
	SetFontSize(orifontsize);

	//文字列の長さを取得して中央に揃える
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
	//プレイガイド表示
	DrawRotaGraph(playguid_pos_.x, playguid_pos_.y, 1.0f, 0, draw_playguid_, false);
	//閉じるボタン表示
	DrawRotaGraph(button_[static_cast<int>(BUTTONNAME::close_)].pos_.x, button_[static_cast<int>(BUTTONNAME::close_)].pos_.y,
		button_[static_cast<int>(BUTTONNAME::close_)].graph_ext_, 0, button_[static_cast<int>(BUTTONNAME::close_)].graph_hdl_, false);
	//矢印左画像表示
	DrawRotaGraph(button_[static_cast<int>(BUTTONNAME::arrow_left_)].pos_.x, button_[static_cast<int>(BUTTONNAME::arrow_left_)].pos_.y,
		button_[static_cast<int>(BUTTONNAME::arrow_left_)].graph_ext_, 0, button_[static_cast<int>(BUTTONNAME::arrow_left_)].graph_hdl_, false);
	//矢印右画像表示
	DrawRotaGraph(button_[static_cast<int>(BUTTONNAME::arrow_right_)].pos_.x, button_[static_cast<int>(BUTTONNAME::arrow_right_)].pos_.y,
		button_[static_cast<int>(BUTTONNAME::arrow_right_)].graph_ext_, 0, button_[static_cast<int>(BUTTONNAME::arrow_right_)].graph_hdl_, false);
}

void UIManager::Update_PlayGuid() {
	//ページ切り替え
	if (IsCursor_Button(static_cast<int>(BUTTONNAME::arrow_left_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		if (draw_playguid_ == playguid_page1_hdl_) {
			draw_playguid_ = playguid_page2_hdl_;
		}
		else if (draw_playguid_ == playguid_page2_hdl_) {
			draw_playguid_ = playguid_page1_hdl_;
		}

		//se再生
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}
	if (IsCursor_Button(static_cast<int>(BUTTONNAME::arrow_right_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		if (draw_playguid_ == playguid_page1_hdl_) {
			draw_playguid_ = playguid_page2_hdl_;
		}
		else if (draw_playguid_ == playguid_page2_hdl_) {
			draw_playguid_ = playguid_page1_hdl_;
		}

		//se再生
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}
}

float UIManager::GraphBlink(float delta_time, float blink_time) {
	blink_count_ += delta_time;
	float alpha = 0.0f;
	//徐々に濃く
	if (blink_change_) {
		alpha = (blink_count_ / blink_time * alpha_max_);
		if (alpha >= static_cast<int>(alpha_max_)) {
			blink_change_ = false;
			blink_count_ = 0.0f;
		}
	}
	//徐々に薄く
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
	//アイテムの枠表示
	for (int i = 0; i < itemdraw_max_; i++) {
		DrawRotaGraph(itemdraw_pos_[i].x, itemdraw_pos_[i].y, 1.0f, 0, noneitem_hdl_, true);
	}

	//所持アイテム表示
	for (int i = 0; i < playeritem_list.size(); i++) {
		//赤表示
		if (playeritem_list[i] == ITEMTYPE::Red) {
			DrawRotaGraph(itemdraw_pos_[i].x, itemdraw_pos_[i].y, 1.0f, 0, reditem_hdl_, true);
		}
		//青表示
		else if (playeritem_list[i] == ITEMTYPE::Blue) {
			DrawRotaGraph(itemdraw_pos_[i].x, itemdraw_pos_[i].y, 1.0f, 0, blueitem_hdl_, true);
		}
		//緑表示
		else if (playeritem_list[i] == ITEMTYPE::Green) {
			DrawRotaGraph(itemdraw_pos_[i].x, itemdraw_pos_[i].y, 1.0f, 0, grerenitem_hdl_, true);
		}
	}

	int orifontsize = GetFontSize();
	SetFontSize(fontsize_hpbar_name_);
	DrawStringEx(10, (itemdraw_pos_[0].y - ui_interval_), -1, "%s", "所持アイテム");
	SetFontSize(orifontsize);
}

void UIManager::Draw_Bombstock(const int& bombstock) {
	bombstock_ = bombstock;

	int orifontsize = GetFontSize();

	//爆破ストック表示
	SetFontSize(fontsize_hpbar_name_);
	DrawStringEx(10, (bombstock_pos_.y + ui_interval_), -1, bombstock_name_.c_str());
	bombstock_str_len_ = static_cast<int>(strlen(bombstock_name_.c_str()));
	bombstock_str_wid_ = GetDrawStringWidth(bombstock_name_.c_str(), bombstock_str_len_);

	SetFontSize(fontsize_bombstock_);
	DrawStringEx((bombstock_str_wid_ + ui_interval_), bombstock_pos_.y, -1, "×%d", bombstock_);

	SetFontSize(orifontsize);
}

void UIManager::Update_PlayMenu(float delta_time) {
	//メニュー表示フラグtrue
	is_menu_ = true;

	//メニュー画面シーケンス
	menu_sequence_.update(delta_time);
}

void UIManager::Draw_PlayMenu() {
	//背景表示
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, menu_background_, true);
	if (menu_sequence_.isComparable(&UIManager::seq_playscene_menu)) {
		//途中終了ボタン表示
		Draw_Button(static_cast<int>(BUTTONNAME::gameminend_draw_));
		//ゲームガイドボタン表示
		Draw_PlayGuid_Button(button_[static_cast<int>(BUTTONNAME::gameguid_draw_)].pos_);
		//メニュー終了ボタン表示
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
		//ゲームガイド表示ボタン
		Draw_PlayGuid_Button(guid_pos_title_);
		//ゲームスタート、レベル選択ボタン
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
	//easy表示
	Draw_Button(static_cast<int>(BUTTONNAME::game_easy_));
	//normal表示
	Draw_Button(static_cast<int>(BUTTONNAME::game_normal_));
	//hard表示
	Draw_Button(static_cast<int>(BUTTONNAME::game_hard_));
}

void UIManager::Draw_Button(int buttonname) {
	DrawRotaGraph(button_[buttonname].pos_.x, button_[buttonname].pos_.y, button_[buttonname].graph_ext_, 0, button_[buttonname].graph_hdl_, true);
}

void UIManager::Draw_MidEndConf() {
	//途中終了確認表示
	DrawRotaGraph(game_midend_conf_pos_.x, game_midend_conf_pos_.y, 1.0f, 0, game_midend_conf_hdl_, true);
	//yesボタン表示
	DrawRotaGraph(button_[static_cast<int>(BUTTONNAME::gamemidend_yes_)].pos_.x, button_[static_cast<int>(BUTTONNAME::gamemidend_yes_)].pos_.y,
		button_[static_cast<int>(BUTTONNAME::gamemidend_yes_)].graph_ext_, 0, button_[static_cast<int>(BUTTONNAME::gamemidend_yes_)].graph_hdl_, true);
	//noボタン表示
	DrawRotaGraph(button_[static_cast<int>(BUTTONNAME::gamemidend_no_)].pos_.x, button_[static_cast<int>(BUTTONNAME::gamemidend_no_)].pos_.y,
		button_[static_cast<int>(BUTTONNAME::gamemidend_no_)].graph_ext_, 0, button_[static_cast<int>(BUTTONNAME::gamemidend_no_)].graph_hdl_, true);
}

void UIManager::Draw_PlayGuid_Button(tnl::Vector2i pos) {
	DrawRotaGraph(pos.x, pos.y, button_[static_cast<int>(BUTTONNAME::gameguid_draw_)].graph_ext_, 0, button_[static_cast<int>(BUTTONNAME::gameguid_draw_)].graph_hdl_, true);
}

bool UIManager::IsCursor_Button(int buttonname) {
	//マウスカーソルが被っていれば true を返す
	if (tnl::IsIntersectPointRect(static_cast<int>(tnl::Input::GetMousePosition().x), static_cast<int>(tnl::Input::GetMousePosition().y),
		button_[buttonname].pos_.x, button_[buttonname].pos_.y, button_[buttonname].size_.x, button_[buttonname].size_.y)) {
		//ボタンを大きく表示する
		button_[buttonname].graph_ext_ = button_[buttonname].graph_overlapext_;

		//se再生
		if (!button_[buttonname].is_se_buttonchoice_) {
			PlaySoundMem(se_buttonchoice_, DX_PLAYTYPE_BACK);
		}
		button_[buttonname].is_se_buttonchoice_ = true;

		return true;
	}
	else {
		//ボタンサイズを通常に戻す
		button_[buttonname].graph_ext_ = button_[buttonname].graph_nomalext_;

		//se再生フラグをfalseに
		button_[buttonname].is_se_buttonchoice_ = false;

		return false;
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------
//タイトルシーンのuiシーケンス

bool UIManager::seq_title(float delta_time) {
	//ゲームレベル選択に移動
	if (IsCursor_Button(static_cast<int>(BUTTONNAME::game_start_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		title_sequence_.change(&UIManager::seq_title_start);

		//se再生
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}
	//プレイガイドシーケンス移動
	else if (IsCursor_Button(static_cast<int>(BUTTONNAME::gameguid_draw_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		title_sequence_.change(&UIManager::seq_title_guid);

		//se再生
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}

	return true;
}

bool UIManager::seq_title_guid(float delta_title) {
	//ページ切り替え
	Update_PlayGuid();

	//プレイガイドを閉じる
	if (IsCursor_Button(static_cast<int>(BUTTONNAME::close_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		title_sequence_.change(&UIManager::seq_title);

		//se再生
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}

	return true;
}

bool UIManager::seq_title_start(float delta_title) {
	//レベル選択を閉じる
	if (IsCursor_Button(static_cast<int>(BUTTONNAME::return_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		title_sequence_.change(&UIManager::seq_title);

		//se再生
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}
	//easyゲームに移動
	else if (IsCursor_Button(static_cast<int>(BUTTONNAME::game_easy_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		is_game_easy_ = true;

		//se再生
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}
	//normalゲームに移動
	else if (IsCursor_Button(static_cast<int>(BUTTONNAME::game_normal_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		is_game_normal_ = true;

		//se再生
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}
	//hardゲームに移動
	else if (IsCursor_Button(static_cast<int>(BUTTONNAME::game_hard_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		is_game_hard_ = true;

		//se再生
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------------------------------
//プレイシーンのメニュー画面シーケンス

bool UIManager::seq_playscene_menu(float delta_time) {
	//ゲームメニューを終了し、ゲームプレイに戻る
	if (IsCursor_Button(static_cast<int>(BUTTONNAME::return_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		is_menu_ = false;

		//se再生
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}
	//プレイガイドシーケンス移動
	else if (IsCursor_Button(static_cast<int>(BUTTONNAME::gameguid_draw_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		menu_sequence_.change(&UIManager::seq_playscene_guid);

		//se再生
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}
	//途中終了シーケンス移動
	else if (IsCursor_Button(static_cast<int>(BUTTONNAME::gameminend_draw_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		menu_sequence_.change(&UIManager::seq_playscene_midend);

		//se再生
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}

	return true;
}

bool UIManager::seq_playscene_midend(float delta_time) {
	//ゲーム途中終了
	if (IsCursor_Button(static_cast<int>(BUTTONNAME::gamemidend_yes_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		is_gamemidend_ = true;

		//se再生
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}
	//メニュー始めの画面に戻る
	else if (IsCursor_Button(static_cast<int>(BUTTONNAME::gamemidend_no_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		menu_sequence_.change(&UIManager::seq_playscene_menu);

		//se再生
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}

	return true;
}

bool UIManager::seq_playscene_guid(float delta_time) {
	//ページ切り替え
	Update_PlayGuid();

	//プレイガイドを閉じる
	if (IsCursor_Button(static_cast<int>(BUTTONNAME::close_)) && tnl::Input::IsMouseTrigger(eMouseTrigger::IN_LEFT)) {
		menu_sequence_.change(&UIManager::seq_playscene_menu);

		//se再生
		PlaySoundMem(se_buttonclick_, DX_PLAYTYPE_BACK);
	}

	return true;
}