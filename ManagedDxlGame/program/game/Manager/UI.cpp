#include "UI.h"

UI::UI(const float& protectobj_hp, const float& gametime, std::vector<ITEMTYPE>& playeritem_list, const int& bombstock) :
		protectobj_hp_(protectobj_hp), gametime_(gametime), playeritem_list_(playeritem_list), bombstock_(bombstock){
	//hp初期値設定
	hp_init_ = protectobj_hp_;
	//hp減衰時のブレ用
	hpblur_dec_jud_ = protectobj_hp_;
	//hpバーの画像読み込み
	hpbar_graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("HPBAR");
	hpbar50_graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("HPBAR_50");
	hpbar20_graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("HPBAR_20");
	//hpバーの後ろの画像読み込み
	backgraph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("HPBAR_BACK");
	//ゲームオーバーの画像読み込み
	gameover_graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("GAMEOVER");
	gameend_graph_hdl_ = gameover_graph_hdl_;
	//ゲームクリアの画像読み込み
	gameclear_graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("GAMECLEAR");

	screeneffect_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("HitEffect_Screen");

	//表示するhpbarの画像初期設定
	draw_graph_hdl_ = hpbar_graph_hdl_;

	//プレイヤー所持アイテム画像読み込み  
	reditem_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("ItemRed");
	blueitem_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("ItemBlue");
	grerenitem_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("ItemGreen");
	noneitem_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("ItemNone");
	//プレイヤー所持アイテム表示座標
	for (int i = 0; i < itemdraw_max_; i++) {
		itemdraw_pos_[i] = { (leftend_ + (itemdraw_size_ / 2)) + (itemdraw_size_ * i), (lowright_pos_.y + (itemdraw_size_ / 2) + ui_interval_), 0 };
	}

	//爆破ストック表示座標
	bombstock_pos_ = { leftend_, (itemdraw_pos_[0].y + (itemdraw_size_ / 2) + ui_interval_), 0 };

	//ガイド関係
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
	//hp_50%以下でスリーンエフェクト表示
	if (bar_rario_ <= 0.5f) {
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, static_cast<int>(screeneffect_alpha_));
		DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, screeneffect_hdl_, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	
	//hpバー表示
	Draw_hpbar();
	//制限時間表示
	Draw_timer();
	//プレイヤー所持アイテム表示
	Draw_PlayerItem();
	//爆破ストック表示
	Draw_Bombstock();
}

void UI::Draw_hpbar() {
	//hpバーの後ろの画像描画
	DrawExtendGraph(static_cast<int>(upleft_pos_.x + hpbar_offset_.x), static_cast<int>(upleft_pos_.y + hpbar_offset_.y),
		static_cast<int>(lowright_pos_.x + hpbar_offset_.x), static_cast<int>(lowright_pos_.y + hpbar_offset_.y),backgraph_hdl_, false);

	//hpバー描画
	float left_draw_pos = hp_leftpos_x_ + leftend_, right_draw_pos = hp_rightpos_x_ + leftend_;
	if (right_draw_pos >= left_draw_pos) {
		DrawExtendGraph(static_cast<int>(left_draw_pos + hpbar_offset_.x), static_cast<int>(upleft_pos_.y + hpbar_offset_.y), 
			static_cast<int>(right_draw_pos + hpbar_offset_.x), static_cast<int>(lowright_pos_.y + hpbar_offset_.y),draw_graph_hdl_, false);
	}
	
	//外枠の線描画
	DrawBox(static_cast<int>(upleft_pos_.x + hpbar_offset_.x), static_cast<int>(upleft_pos_.y + hpbar_offset_.y), 
		static_cast<int>(lowright_pos_.x + hpbar_offset_.x), static_cast<int>(lowright_pos_.y + hpbar_offset_.y), -1, false);
	
	int orifontsize = GetFontSize();
	SetFontSize(fontsize_hpbar_name_);
	DrawStringEx(10, 50, -1, "%s", "船の耐久値");
	SetFontSize(orifontsize);
}

void UI::Hpbar_blur(float delta_time){
	//hpが減ったかを判定
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
			//カウントリセット
			hpblur_count_ = 0;
			//４回ブレたら終了
			if (blur_index_ >= 4) {
				blur_index_ = 0;
				is_hpblur_ = false;
				//ブレの値リセット
				hpbar_offset_ = { 0,0,0 };
				return;
			}
			//ブレの値をセット
			hpbar_offset_ = hpbar_blur_[blur_index_];
			//ブレの回数カウント
			blur_index_++;
		}
	}
}

void UI::Draw_timer() {
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
	//プレイガイド表示
	DrawRotaGraph(static_cast<int>(playguid_pos_.x), static_cast<int>(playguid_pos_.y), 1.0f, 0, draw_playguid_, false);
	//閉じるボタン表示
	DrawRotaGraph(static_cast<int>(close_pos_.x), static_cast<int>(close_pos_.y), 1.0f, 0, close_hdl_, false);
	//矢印左画像表示
	DrawRotaGraph(static_cast<int>(arrowleft_pos_.x), static_cast<int>(arrowleft_pos_.y), 1.0f, 0, arrow_left_hdl_, false);
	//矢印右画像表示
	DrawRotaGraph(static_cast<int>(arrowright_pos_.x), static_cast<int>(arrowright_pos_.y), 1.0f, 0, arrow_right_hdl_, false);
}

void UI::Update_PlayGuid(){
	//ページ切り替え
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
	//徐々に濃く
	if (blink_change_) {
		alpha = (blink_count_ / blink_time * 255.0f);
		if (alpha >= 255) {
			blink_change_ = false;
			blink_count_ = 0.0f;
		}
	}
	//徐々に薄く
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
	//アイテムの枠表示
	for (int i = 0; i < itemdraw_max_; i++) {
		DrawRotaGraph(static_cast<int>(itemdraw_pos_[i].x), static_cast<int>(itemdraw_pos_[i].y), 1.0f, 0, noneitem_hdl_, true);
	}

	//所持アイテム表示
	for (int i = 0; i < playeritem_list_.size(); i++) {
		//赤表示
		if (playeritem_list_[i] == ITEMTYPE::Red) {
			DrawRotaGraph(static_cast<int>(itemdraw_pos_[i].x), static_cast<int>(itemdraw_pos_[i].y), 1.0f, 0, reditem_hdl_, true);
		}
		//青表示
		else if (playeritem_list_[i] == ITEMTYPE::Blue) {
			DrawRotaGraph(static_cast<int>(itemdraw_pos_[i].x), static_cast<int>(itemdraw_pos_[i].y), 1.0f, 0, blueitem_hdl_, true);
		}
		//緑表示
		else if (playeritem_list_[i] == ITEMTYPE::Green) {
			DrawRotaGraph(static_cast<int>(itemdraw_pos_[i].x), static_cast<int>(itemdraw_pos_[i].y), 1.0f, 0, grerenitem_hdl_, true);
		}
	}

	int orifontsize = GetFontSize();
	SetFontSize(fontsize_hpbar_name_);
	DrawStringEx(10, static_cast<int>(itemdraw_pos_[0].y - ui_interval_), -1, "%s", "所持アイテム");
	SetFontSize(orifontsize);
}

void UI::Draw_Bombstock(){
	//爆破ストック表示
	int orifontsize = GetFontSize();

	SetFontSize(fontsize_hpbar_name_);
	DrawStringEx(10, static_cast<int>(bombstock_pos_.y + ui_interval_), -1, bombstock_name_.c_str() );
	bombstock_str_len_ = static_cast<int>(strlen(bombstock_name_.c_str()));
	bombstock_str_wid_ = GetDrawStringWidth(bombstock_name_.c_str(), bombstock_str_len_);

	SetFontSize(fontsize_bombstock_);
	DrawStringEx((bombstock_str_wid_ + static_cast<int>(ui_interval_)), static_cast<int>(bombstock_pos_.y), -1, "×%d", bombstock_);

	SetFontSize(orifontsize);
}

bool UI::Is_Cursor_close(){
	//閉じるボタンとマウスカーソルが被っていれば true を返す
	if (tnl::IsIntersectPointRect(static_cast<int>(tnl::Input::GetMousePosition().x), static_cast<int>(tnl::Input::GetMousePosition().y),
		static_cast<int>(close_pos_.x), static_cast<int>(close_pos_.y), static_cast<int>(close_size_.x), static_cast<int>(close_size_.y))) {
		return true;
	}

	return false;
}

bool UI::Is_Cursor_LeftArrwo(){
	//ページめくり左をマウスカーソルが被っていれば true を返す
	if (tnl::IsIntersectPointRect(static_cast<int>(tnl::Input::GetMousePosition().x), static_cast<int>(tnl::Input::GetMousePosition().y),
		static_cast<int>(arrowleft_pos_.x), static_cast<int>(arrowleft_pos_.y), static_cast<int>(arrow_size_.x), static_cast<int>(arrow_size_.y))) {
		return true;
	}

	return false;
}

bool UI::Is_Cursor_RightArrow(){
	//ページめくり右をマウスカーソルが被っていれば true を返す
	if (tnl::IsIntersectPointRect(static_cast<int>(tnl::Input::GetMousePosition().x), static_cast<int>(tnl::Input::GetMousePosition().y),
		static_cast<int>(arrowright_pos_.x), static_cast<int>(arrowright_pos_.y), static_cast<int>(arrow_size_.x), static_cast<int>(arrow_size_.y))) {
		return true;
	}

	return false;
}

bool UI::SEQ_Play(const float delta_time) {
	//hpバーの長さ比率計算
	bar_rario_ = protectobj_hp_ / hp_init_;
	//hpバーの長さ更新
	hp_rightpos_x_ = barlength_ * bar_rario_;

	//hpバーのブレ
	Hpbar_blur(delta_time);

	//hpbarの画像変更
	//50%以上で青
	if (bar_rario_ > 0.5f) {
		draw_graph_hdl_ = hpbar_graph_hdl_;
	}
	//50%~20%で黄色
	else if (bar_rario_ <= 0.5f && bar_rario_ > 0.2f) {
		draw_graph_hdl_ = hpbar50_graph_hdl_;

		//スクリーンエフェクトの時間をセット
		screeneffect_time_ = effecttime50_;
	}
	//20%以下で赤
	else if (bar_rario_ <= 0.2f) {
		draw_graph_hdl_ = hpbar20_graph_hdl_;

		//スクリーンエフェクトの時間を変更
		screeneffect_time_ = effecttime20_;
	}
	else {
		draw_graph_hdl_ = hpbar_graph_hdl_;
	}

	//スクリーンエフェクトのalpha値設定
	screeneffect_alpha_ = GraphBlink(delta_time, screeneffect_time_);

	//シーケンス移動条件
	if (bar_rario_ <= 0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		tnl_sequence_.change(&UI::SEQ_END);
	}
	TNL_SEQ_CO_END
}

bool UI::SEQ_END(const float delta_time) {


	TNL_SEQ_CO_END
}