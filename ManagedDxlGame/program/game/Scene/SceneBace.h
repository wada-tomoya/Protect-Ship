#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

//�p���̖��[�V�[����
enum class FINALCLASS_NAME {
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
	FINALCLASS_NAME scenename_ = FINALCLASS_NAME::title;

public:
	SceneBace() = default;

	//�����P�F�V�[���N���X��
	SceneBace(const FINALCLASS_NAME& classname) { scenename_ = classname; };

	//���s�֐�
	//�����P�F����
	virtual void Update(const float& delta_time) {};
	//�`��֐�
	//�����P�F����
	virtual void Draw(const float& delta_time) {};

	//�}�E�X�J�[�\���`��
	//�����P�Ftrue...�摜�̒��S�����S���W�Afalse..�摜�̍��オ���S���W
	//�ʏ��true
	void MouseDraw(const bool& center = true) {
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
