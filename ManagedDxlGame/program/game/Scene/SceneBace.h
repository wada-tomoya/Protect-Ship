#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

//�p���̖��[�V�[����
enum class ENDCLASS_NAME {
	title,
	play_easy,
	play_normal,
	play_hard
};

class SceneBace{
protected:
	//�V�[���؂�ւ��t���O
	bool is_scene_change_ = false;
	//BGM�n���h��
	int bgm_hdl_ = 0;
	//�}�E�X�J�[�\���摜
	int mouse_graph_hdl_ = 0;
	//�}�E�X�J�[�\���摜�̈ʒu�덷�C��
	const int mouse_pos_fix_ = 7;

	//�p���̖��[�V�[����
	ENDCLASS_NAME scenename_ = ENDCLASS_NAME::title;

public:
	SceneBace(ENDCLASS_NAME classname) { scenename_ = classname; };

	virtual void Update(float delta_time) {};
	virtual void Draw(float delta_time) {};

	//�}�E�X�J�[�\���`��
	//�����P true...�摜�̒��S�����S���W
	//	false..�摜�̍��オ���S���W
	//�ʏ��true
	void MouseDraw(bool center = true) {
		//�}�E�X�J�[�\���`��
		float mouse_x = tnl::Input::GetMousePosition().x, mouse_y = tnl::Input::GetMousePosition().y;
		if (center) {
			DrawRotaGraph(static_cast<int>(mouse_x), (static_cast<int>(mouse_y) - mouse_pos_fix_), 1.0f, 0, mouse_graph_hdl_, true);
		}
		else {
			DrawGraph(static_cast<int>(mouse_x), static_cast<int>(mouse_y), mouse_graph_hdl_, true);
		}
	};
};
