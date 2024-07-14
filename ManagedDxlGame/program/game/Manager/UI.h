#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../Manager/ResourceManager.h"
#include "../Object/Camera.h"
#include "../Object/Item/ItemBase.h"

//引数（hpバーの値、制限時間、プレイヤーのアイテムlist）
class UI {
protected:
	//シーケンス
	TNL_CO_SEQUENCE(UI, &UI::SEQ_Play)
	//プレイシーンシーケンス
	bool SEQ_Play(const float delta_time);
	//ゲーム終了シーケンス
	bool SEQ_END(const float delta_time);

	//hpバー左端からの距離
	const float leftend_ = 180.0f;
	//hpバー右端からの距離
	const float rightend_ = DXE_WINDOW_WIDTH - 30.0f;
	//hpバーの長さ
	const float barlength_ = rightend_ - leftend_;
	//hpバーの高さ
	const float barheight_ = 30.0f;
	//初期左上の座標
	const tnl::Vector3 upleft_pos_{ leftend_,50.0f,0.0f };
	//初期右下の座標
	const tnl::Vector3 lowright_pos_{ rightend_,(upleft_pos_.y + barheight_),0.0f };
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
	//hpの値
	const float& protectobj_hp_ = 0.0f;

	//hp20％以下でのスクリーンエフェクト
	int screeneffect_hdl_ = 0;
	//点滅用alpha値
	float screeneffect_alpha_ = 0.0f;
	//点滅にかかる時間
	float effecttime50_ = 1.5f, effecttime20_ = 0.8f;
	float screeneffect_time_ = effecttime50_;

	//点滅切り替え
	bool blink_change_ = true;
	float blink_count_ = 0.0f;

	//船が攻撃を受けた時のhpbarのブレ値
	tnl::Vector3 hpbar_blur_[4] = { {5,5,0},{3,-2,0},{-2,3,0},{-3,-3,0} };
	tnl::Vector3 hpbar_offset_ = {0,0,0};
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
	const float& gametime_ = 0.0f;
	//制限時間の座標
	tnl::Vector3 gametime_pos_{ leftend_,10,0 };
	const int fontsize_timer_ = 30;

	//ゲーム終了時の画像
	int gameend_graph_hdl_ = 0;
	//ゲームオーバーの画像
	int gameover_graph_hdl_ = 0;
	//ゲームクリアの画像
	int gameclear_graph_hdl_ = 0;
	//画像がでるまでの時間
	float trans_time_ = 0.5f;

	//プレイヤーが持ってるアイテムのリスト
	std::vector<ITEMTYPE>& playeritem_list_;
	//画像ハンドル
	int reditem_hdl_ = 0, blueitem_hdl_ = 0, grerenitem_hdl_ = 0, noneitem_hdl_ = 0;
	//画像サイズ
	const float itemdraw_size_ = 60.0f;
	//表示最大個数
	static const int itemdraw_max_ = 5;
	//表示座標
	tnl::Vector3 itemdraw_pos_[itemdraw_max_];

	//爆弾のストック数
	const int& bombstock_ = 0;
	//表示座標
	tnl::Vector3 bombstock_pos_ = {0,0,0};
	//ストック数のフォントサイズ
	const int fontsize_bombstock_ = 50;
	const std::string bombstock_name_ = "爆破攻撃ストック";
	int bombstock_str_len_ = 0, bombstock_str_wid_ = 0;

	//hpバーと所持アイテムの間
	const float ui_interval_ = 10.0f;

	//ガイドの画像ハンドル
	int playguid_page1_hdl_ = 0, playguid_page2_hdl_ = 0, arrow_left_hdl_ = 0, arrow_right_hdl_ = 0, close_hdl_ = 0;
	//表示するプレイガイド
	int draw_playguid_ = 0;
	//ガイド画像サイズ
	tnl::Vector3 playguid_size_{ 960.0f,540.0f,0.0f };
	//ガイド画像座標
	tnl::Vector3 playguid_pos_{ (DXE_WINDOW_WIDTH / 2),(DXE_WINDOW_HEIGHT / 2),0 };
	//矢印画像サイズ
	tnl::Vector3 arrow_size_{ 36.0f,72.0f,0.0f };
	//矢印画像座標
	tnl::Vector3 arrowleft_pos_{ playguid_pos_.x - (playguid_size_.x / 2) + (arrow_size_.x / 2) + 20.0f, playguid_pos_.y,0 },
		   		 arrowright_pos_{ playguid_pos_.x + (playguid_size_.x / 2) - (arrow_size_.x / 2) - 20.0f, playguid_pos_.y,0 };
	//閉じるボタンサイズ
	tnl::Vector3 close_size_{ 40.0f,40.0f,0 };
	//閉じるボタン座標
	tnl::Vector3 close_pos_{ playguid_pos_.x + (playguid_size_.x / 2) - (close_size_.x / 2) - 10.0f, playguid_pos_.y - (playguid_size_.y/2)+(close_size_.y/2)+10.0f,0};

	bool is_kabutta = false;

public:
	UI(const float& protectobj_hp, const float& gametime, std::vector<ITEMTYPE>& playeritem_list, const int& bombstock);
	~UI();

	void UI_Update(float delta_time);
	void UI_Draw(std::shared_ptr<Camera> camera);

	//hpバー表示
	void Draw_hpbar();
	void Hpbar_blur(float delta_time);
	//制限時間表示
	void Draw_timer();
	//ゲーム終了表示
	void Draw_gameend(int gameend_type);
	//プレイガイド表示
	void Draw_PlayGuid();
	//プレイガイド実行
	void Update_PlayGuid();
	//画像点滅
	//引数1 delta_time、引数2 点滅間隔
	float GraphBlink(float delta_time, float blink_time);
	//プレイヤーの所持アイテム表示
	void Draw_PlayerItem();
	//爆弾のストック表示
	void Draw_Bombstock();
	//プレイガイド閉じるボタンとマウスカーソルが被ってるか判定
	bool Is_Cursor_close();
	//プレイガイドのページめくるボタンとマウスカーソルが被ってるか判定
	bool Is_Cursor_LeftArrwo();
	bool Is_Cursor_RightArrow();
};