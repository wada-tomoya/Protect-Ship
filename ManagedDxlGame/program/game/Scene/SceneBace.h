#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

//継承の末端シーン名
enum class ENDCLASS_NAME {
	title,
	play_easy,
	play_normal,
	play_hard
};

class SceneBace{
protected:
	//シーン切り替えフラグ
	bool is_scene_change_ = false;
	//BGMハンドル
	int bgm_hdl_ = 0;
	//マウスカーソル画像
	int mouse_graph_hdl_ = 0;
	//マウスカーソル画像の位置誤差修正
	const int mouse_pos_fix_ = 7;

	//継承の末端シーン名
	ENDCLASS_NAME scenename_ = ENDCLASS_NAME::title;

public:
	SceneBace(ENDCLASS_NAME classname) { scenename_ = classname; };

	virtual void Update(float delta_time) {};
	virtual void Draw(float delta_time) {};

	//マウスカーソル描画
	//引数１ true...画像の中心が中心座標
	//	false..画像の左上が中心座標
	//通常はtrue
	void MouseDraw(bool center = true) {
		//マウスカーソル描画
		float mouse_x = tnl::Input::GetMousePosition().x, mouse_y = tnl::Input::GetMousePosition().y;
		if (center) {
			DrawRotaGraph(static_cast<int>(mouse_x), (static_cast<int>(mouse_y) - mouse_pos_fix_), 1.0f, 0, mouse_graph_hdl_, true);
		}
		else {
			DrawGraph(static_cast<int>(mouse_x), static_cast<int>(mouse_y), mouse_graph_hdl_, true);
		}
	};
};
