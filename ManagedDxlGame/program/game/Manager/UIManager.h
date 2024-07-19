#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../Object/Item/ItemBase.h"

enum class BUTTONNAME {
	arrow_left_,
	arrow_right_,
	close_,
	gameguid_draw_,
	gameminend_draw_,
	gamemidend_no_,
	gamemidend_yes_,
	return_,
	game_start_,
	game_easy_,
	game_normal_,
	game_hard_,
	max
};

class UIManager {
private:
	//hpバー左端からの距離
	const int leftend_ = 180;
	//hpバー右端からの距離
	const int rightend_ = DXE_WINDOW_WIDTH - 30;
	//hpバーの長さ
	const int barlength_ = rightend_ - leftend_;
	//hpバーの高さ
	const int barheight_ = 30;
	//初期左上の座標
	const tnl::Vector2i upleft_pos_{ leftend_,50 };
	//初期右下の座標
	const tnl::Vector2i lowright_pos_{ rightend_,static_cast<float>(upleft_pos_.y + barheight_) };
	//x座標hpバー表示位置
	float hp_leftpos_x_ = 0.0f, hp_rightpos_x_ = barlength_;
	//画像ハンドル
	int hpbar_graph_hdl_ = 0;
	int hpbar50_graph_hdl_ = 0;
	int hpbar20_graph_hdl_ = 0;
	int draw_graph_hdl_ = 0;
	//hpバーの後ろの画像ハンドル
	int backgraph_hdl_ = 0;
	//バーの長さの倍率
	float bar_rario_ = 1.0f;
	//hp初期値
	float hp_init_ = 0.0f;

	//hp20％以下でのスクリーンエフェクト
	int screeneffect_hdl_ = 0;
	//点滅用alpha値
	float screeneffect_alpha_ = 0.0f;
	//点滅にかかる時間
	float effecttime50_ = 1.5f, effecttime20_ = 0.8f;
	float screeneffect_time_ = effecttime50_;
	//hpバー割合ごとの色、5割：黄色　2割：赤
	const float hpbar_yellow_ = 0.5f, hpbar_red_ = 0.2f;
	//α値のmax
	const float alpha_max_ = 255.0f;

	//点滅切り替え
	bool blink_change_ = true;
	float blink_count_ = 0.0f;

	//船が攻撃を受けた時のhpbarのブレ値
	static const int blur_num_ = 4;
	const tnl::Vector2i hpbar_blur_[blur_num_] = { {5,5},{3,-2},{-2,3},{-3,-3} };
	tnl::Vector2i hpbar_offset_ = { 0,0 };
	float hpblur_interval_ = 0.1f, hpblur_count_ = 0.0f;
	int blur_index_ = 0;
	//hp減少判定用
	float hpblur_dec_jud_ = 0.0f;
	bool is_hpblur_ = false;

	//hpバーの名前関係
	const int fontsize_hpbar_name_ = 30;
	const std::string hpbar_name_ = "船の耐久値";
	int str_len_ = 0, str_wid_ = 0;

	//制限時間
	float gametime_ = 0.0f;
	//制限時間の座標
	tnl::Vector2i gametime_pos_{ leftend_,10 };
	const int fontsize_timer_ = 30;

	enum class ENDTYPE {
		gameover = 1,
		gameclear = 2,
	};

	//ゲーム終了時の画像
	int gameend_graph_hdl_ = 0;
	//ゲームオーバーの画像
	int gameover_graph_hdl_ = 0;
	//ゲームクリアの画像
	int gameclear_graph_hdl_ = 0;
	//画像がでるまでの時間
	float trans_time_ = 0.5f;

	//プレイヤーが持ってるアイテムのリスト
	std::vector<ITEMTYPE> playeritem_list_;
	//画像ハンドル
	int reditem_hdl_ = 0, blueitem_hdl_ = 0, grerenitem_hdl_ = 0, noneitem_hdl_ = 0;
	//画像サイズ
	const int itemdraw_size_ = 60;
	//表示最大個数
	static const int itemdraw_max_ = 5;
	//表示座標
	tnl::Vector2i itemdraw_pos_[itemdraw_max_];

	//爆弾のストック数
	int bombstock_ = 0;
	//表示座標
	tnl::Vector2i bombstock_pos_ = { 0,0 };
	//ストック数のフォントサイズ
	const int fontsize_bombstock_ = 50;
	const std::string bombstock_name_ = "爆破攻撃ストック";
	int bombstock_str_len_ = 0, bombstock_str_wid_ = 0;

	//hpバーと所持アイテムの間
	const int ui_interval_ = 10;

	struct BUTTON {
		//画像ハンドル
		int graph_hdl_ = 0;
		//座標
		tnl::Vector2i pos_{ 0,0 };
		//基本サイズ出ない場合のボタンサイズ
		tnl::Vector2i size_{ 0,0 };

		//マウスが被った時のse再生フラグ
		bool is_se_buttonchoice_ = false;

		//画像とマウスが重なった時の拡大率
		const float graph_overlapext_ = 2.0f;
		//通常時の画像拡大率
		const float graph_nomalext_ = 1.0f;
		//画像表示の拡大率
		float graph_ext_ = graph_nomalext_;
	};
	//ボタン宣言
	BUTTON arrow_left_, arrow_right_, close_, gameguid_draw_, gameminend_draw_, gamemidend_no_, gamemidend_yes_,
		return_, game_start_, game_easy_, game_normal_, game_hard_;
	//配列に挿入
	BUTTON button_[static_cast<int>(BUTTONNAME::max)]{ arrow_left_, arrow_right_, close_, gameguid_draw_, gameminend_draw_, gamemidend_no_, gamemidend_yes_,
		return_, game_start_, game_easy_, game_normal_, game_hard_ };

	//ボタン基本サイズ
	tnl::Vector2i button_normal_size_{ 300,50 }, button_mini_size_{ 200,50 };
	//タイトルでの戻るボタン座標
	tnl::Vector2i title_button_return_{ DXE_WINDOW_WIDTH / 2, 500, };
	//タイトルのボタンy基準座標
	const int title_butotn_pos_y_ = 400;
	//マウスとボタンが被った時のse
	int se_buttonchoice_ = 0;
	//ボタンをクリックした時のse
	int se_buttonclick_ = 0;
	//ボタンの縦座標幅
	const int button_heispace_ = 100;
	//ボタンの横座標幅
	const int button_widspace_ = 20;
	//タイトルでのガイド表示ボタンの座標
	tnl::Vector2i guid_pos_title_{ (DXE_WINDOW_WIDTH / 2), title_butotn_pos_y_ + (button_heispace_ / 2) };
	//ガイドの画像ハンドル
	int playguid_page1_hdl_ = 0, playguid_page2_hdl_ = 0;
	//表示するプレイガイド
	int draw_playguid_ = 0;
	//ガイド画像サイズ
	tnl::Vector2i playguid_size_{ 960,540 };
	//ガイド画像座標
	tnl::Vector2i playguid_pos_{ (DXE_WINDOW_WIDTH / 2),(DXE_WINDOW_HEIGHT / 2) };

	//メニュー画面背景画像ハンドル
	int menu_background_ = 0;

	//ゲーム途中終了ボタン画像ハンドル
	int game_midend_conf_hdl_ = 0;
	//ゲーム途中終了確認画像サイズ、座標
	tnl::Vector2i game_midend_conf_size_{ 600,300 };
	tnl::Vector2i game_midend_conf_pos_{ (DXE_WINDOW_WIDTH / 2), (DXE_WINDOW_HEIGHT / 2) };

	//タイトルUI表示シーケンス
	tnl::Sequence<UIManager> title_sequence_ = tnl::Sequence<UIManager>(this, &UIManager::seq_title);
	//タイトル
	bool seq_title(float delta_time);
	//ガイド
	bool seq_title_guid(float delta_time);
	//ゲームスタート
	bool seq_title_start(float delta_time);

	//メニュー画面シーケンス
	tnl::Sequence<UIManager> menu_sequence_ = tnl::Sequence<UIManager>(this, &UIManager::seq_playscene_menu);
	//メニュー
	bool seq_playscene_menu(float delta_time);
	//ゲーム途中終了
	bool seq_playscene_midend(float delta_time);
	//ガイド
	bool seq_playscene_guid(float delta_time);

	//メニュー画面フラグ
	bool is_menu_ = false;
	//ゲーム途中終了フラグ
	bool is_gamemidend_ = false;

	//各難易度のゲームに移動フラグ
	bool is_game_easy_ = false, is_game_normal_ = false, is_game_hard_ = false;

public:
	UIManager();
	~UIManager();

	//タイトルシーンUI
	void UI_init_TitleScene();
	void UI_Update_TitleScene(float delta_tiem);

	//プレイシーンのUI
	void UI_init_PlayScene(float protectobj_hp, const std::vector<ITEMTYPE>& playeritem_list);
	void UI_Update_PlayScene(float delta_time, const float& protectobj_hp);

	//hpバー表示
	void Draw_hpbar();
	//hpをバー揺らす
	void Hpbar_blur(float delta_time, const float& protectobj_hp);

	//船体力低下時のスクリーンエフェクト表示
	void Draw_ScreenEffect();
	//画像点滅
	float GraphBlink(float delta_time, float blink_time);

	//制限時間表示
	void Draw_timer(const float& gametime);

	//ゲーム終了表示
	void Draw_gameend(int gameend_type);

	//プレイガイド表示
	void Draw_PlayGuid();
	//プレイガイド更新
	void Update_PlayGuid();

	//タイトル画面ボタン表示
	void Draw_TitleUI();
	//ゲームレベル選択ボタン表示
	void Draw_GameLevel();

	//各ボタン表示
	void Draw_Button(int buttonname);

	//プレイヤーの所持アイテム表示
	void Draw_PlayerItem(const std::vector<ITEMTYPE>& playeritem_list);

	//爆弾のストック表示
	void Draw_Bombstock(const int& bombstock);

	//メニュー画面更新
	void Update_PlayMenu(float delta_time);
	//メニュー画面表示
	void Draw_PlayMenu();
	//途中ゲーム終了確認表示
	void Draw_MidEndConf();
	//ゲームガイド表示ボタン表示
	void Draw_PlayGuid_Button(tnl::Vector2i pos);

	//各ボタンとマウスカーソルが被っているか判定
	bool IsCursor_Button(int buttonname);

	//メニュー画面終了フラグ
	bool Getter_is_menu_()const { return is_menu_; };
	//ゲーム途中フラグゲッター
	bool Getter_is_amemidend_()const { return is_gamemidend_; };
	//ゲームの難易度フラグゲッター
	bool Getter_is_game_level(std::string levelname)const {
		if (levelname == "easy") { return is_game_easy_; }
		else if (levelname == "normal") { return is_game_normal_; }
		else if (levelname == "hard") { return is_game_hard_; }
	}
};