#include "SceneBace.h"

void SceneBace::MouseDraw(const bool& flash, const bool& center) {
	//マウスカーソル座標取得
	float mouse_x = tnl::Input::GetMousePosition().x, mouse_y = tnl::Input::GetMousePosition().y;
	if (flash) {
		//マウスカーソル表示
		if (center) {
			DrawRotaGraph(static_cast<int>(mouse_x), (static_cast<int>(mouse_y) - mouse_pos_fix_), 1.0f, 0, mouse_graph_hdl_, true);
		}
		else {
			DrawGraph(static_cast<int>(mouse_x), static_cast<int>(mouse_y), mouse_graph_hdl_, true);
		}
	}
	else {
		//マウスカーソル画面外に表示、点滅して見えるようにする
		if (center) {
			DrawRotaGraph(-500, -500, 1.0f, 0, mouse_graph_hdl_, true);
		}
		else {
			DrawGraph(-500, -500, mouse_graph_hdl_, true);
		}
	}

}