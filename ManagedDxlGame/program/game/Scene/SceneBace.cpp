#include "SceneBace.h"

void SceneBace::MouseDraw(const bool& flash, const bool& center) {
	//�}�E�X�J�[�\�����W�擾
	float mouse_x = tnl::Input::GetMousePosition().x, mouse_y = tnl::Input::GetMousePosition().y;
	if (flash) {
		//�}�E�X�J�[�\���\��
		if (center) {
			DrawRotaGraph(static_cast<int>(mouse_x), (static_cast<int>(mouse_y) - mouse_pos_fix_), 1.0f, 0, mouse_graph_hdl_, true);
		}
		else {
			DrawGraph(static_cast<int>(mouse_x), static_cast<int>(mouse_y), mouse_graph_hdl_, true);
		}
	}
	else {
		//�}�E�X�J�[�\����ʊO�ɕ\���A�_�ł��Č�����悤�ɂ���
		if (center) {
			DrawRotaGraph(-500, -500, 1.0f, 0, mouse_graph_hdl_, true);
		}
		else {
			DrawGraph(-500, -500, mouse_graph_hdl_, true);
		}
	}

}