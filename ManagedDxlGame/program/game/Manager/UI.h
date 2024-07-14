#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
#include "../Manager/ResourceManager.h"
#include "../Object/Camera.h"
#include "../Object/Item/ItemBase.h"

//�����ihp�o�[�̒l�A�������ԁA�v���C���[�̃A�C�e��list�j
class UI {
protected:
	//�V�[�P���X
	TNL_CO_SEQUENCE(UI, &UI::SEQ_Play)
	//�v���C�V�[���V�[�P���X
	bool SEQ_Play(const float delta_time);
	//�Q�[���I���V�[�P���X
	bool SEQ_END(const float delta_time);

	//hp�o�[���[����̋���
	const float leftend_ = 180.0f;
	//hp�o�[�E�[����̋���
	const float rightend_ = DXE_WINDOW_WIDTH - 30.0f;
	//hp�o�[�̒���
	const float barlength_ = rightend_ - leftend_;
	//hp�o�[�̍���
	const float barheight_ = 30.0f;
	//��������̍��W
	const tnl::Vector3 upleft_pos_{ leftend_,50.0f,0.0f };
	//�����E���̍��W
	const tnl::Vector3 lowright_pos_{ rightend_,(upleft_pos_.y + barheight_),0.0f };
	//x���Whp�o�[�\���ʒu
	float hp_leftpos_x_ = 0.0f, hp_rightpos_x_ = barlength_;
	//�摜�n���h��
	int hpbar_graph_hdl_ = 0;
	int hpbar50_graph_hdl_ = 0;
	int hpbar20_graph_hdl_ = 0;
	int draw_graph_hdl_ = 0;
	//hp�o�[�̌��̉摜�n���h��
	int backgraph_hdl_ = 0;
	//�o�[�̒����̔{��
	float bar_rario_ = 1.0f;
	//hp�����l
	float hp_init_ = 0.0f;
	//hp�̒l
	const float& protectobj_hp_ = 0.0f;

	//hp20���ȉ��ł̃X�N���[���G�t�F�N�g
	int screeneffect_hdl_ = 0;
	//�_�ŗpalpha�l
	float screeneffect_alpha_ = 0.0f;
	//�_�łɂ����鎞��
	float effecttime50_ = 1.5f, effecttime20_ = 0.8f;
	float screeneffect_time_ = effecttime50_;

	//�_�Ő؂�ւ�
	bool blink_change_ = true;
	float blink_count_ = 0.0f;

	//�D���U�����󂯂�����hpbar�̃u���l
	tnl::Vector3 hpbar_blur_[4] = { {5,5,0},{3,-2,0},{-2,3,0},{-3,-3,0} };
	tnl::Vector3 hpbar_offset_ = {0,0,0};
	float hpblur_interval_ = 0.1f, hpblur_count_ = 0.0f;
	int blur_index_ = 0;
	//hp��������p
	float hpblur_dec_jud_ = 0.0f;
	bool is_hpblur_ = false;
	
	//hp�o�[�̖��O�֌W
	const int fontsize_hpbar_name_ = 30;
	const std::string hpbar_name_ = "�D�̑ϋv�l";
	int str_len_ = 0, str_wid_ = 0;

	//��������
	const float& gametime_ = 0.0f;
	//�������Ԃ̍��W
	tnl::Vector3 gametime_pos_{ leftend_,10,0 };
	const int fontsize_timer_ = 30;

	//�Q�[���I�����̉摜
	int gameend_graph_hdl_ = 0;
	//�Q�[���I�[�o�[�̉摜
	int gameover_graph_hdl_ = 0;
	//�Q�[���N���A�̉摜
	int gameclear_graph_hdl_ = 0;
	//�摜���ł�܂ł̎���
	float trans_time_ = 0.5f;

	//�v���C���[�������Ă�A�C�e���̃��X�g
	std::vector<ITEMTYPE>& playeritem_list_;
	//�摜�n���h��
	int reditem_hdl_ = 0, blueitem_hdl_ = 0, grerenitem_hdl_ = 0, noneitem_hdl_ = 0;
	//�摜�T�C�Y
	const float itemdraw_size_ = 60.0f;
	//�\���ő��
	static const int itemdraw_max_ = 5;
	//�\�����W
	tnl::Vector3 itemdraw_pos_[itemdraw_max_];

	//���e�̃X�g�b�N��
	const int& bombstock_ = 0;
	//�\�����W
	tnl::Vector3 bombstock_pos_ = {0,0,0};
	//�X�g�b�N���̃t�H���g�T�C�Y
	const int fontsize_bombstock_ = 50;
	const std::string bombstock_name_ = "���j�U���X�g�b�N";
	int bombstock_str_len_ = 0, bombstock_str_wid_ = 0;

	//hp�o�[�Ə����A�C�e���̊�
	const float ui_interval_ = 10.0f;

	//�K�C�h�̉摜�n���h��
	int playguid_page1_hdl_ = 0, playguid_page2_hdl_ = 0, arrow_left_hdl_ = 0, arrow_right_hdl_ = 0, close_hdl_ = 0;
	//�\������v���C�K�C�h
	int draw_playguid_ = 0;
	//�K�C�h�摜�T�C�Y
	tnl::Vector3 playguid_size_{ 960.0f,540.0f,0.0f };
	//�K�C�h�摜���W
	tnl::Vector3 playguid_pos_{ (DXE_WINDOW_WIDTH / 2),(DXE_WINDOW_HEIGHT / 2),0 };
	//���摜�T�C�Y
	tnl::Vector3 arrow_size_{ 36.0f,72.0f,0.0f };
	//���摜���W
	tnl::Vector3 arrowleft_pos_{ playguid_pos_.x - (playguid_size_.x / 2) + (arrow_size_.x / 2) + 20.0f, playguid_pos_.y,0 },
		   		 arrowright_pos_{ playguid_pos_.x + (playguid_size_.x / 2) - (arrow_size_.x / 2) - 20.0f, playguid_pos_.y,0 };
	//����{�^���T�C�Y
	tnl::Vector3 close_size_{ 40.0f,40.0f,0 };
	//����{�^�����W
	tnl::Vector3 close_pos_{ playguid_pos_.x + (playguid_size_.x / 2) - (close_size_.x / 2) - 10.0f, playguid_pos_.y - (playguid_size_.y/2)+(close_size_.y/2)+10.0f,0};

	bool is_kabutta = false;

public:
	UI(const float& protectobj_hp, const float& gametime, std::vector<ITEMTYPE>& playeritem_list, const int& bombstock);
	~UI();

	void UI_Update(float delta_time);
	void UI_Draw(std::shared_ptr<Camera> camera);

	//hp�o�[�\��
	void Draw_hpbar();
	void Hpbar_blur(float delta_time);
	//�������ԕ\��
	void Draw_timer();
	//�Q�[���I���\��
	void Draw_gameend(int gameend_type);
	//�v���C�K�C�h�\��
	void Draw_PlayGuid();
	//�v���C�K�C�h���s
	void Update_PlayGuid();
	//�摜�_��
	//����1 delta_time�A����2 �_�ŊԊu
	float GraphBlink(float delta_time, float blink_time);
	//�v���C���[�̏����A�C�e���\��
	void Draw_PlayerItem();
	//���e�̃X�g�b�N�\��
	void Draw_Bombstock();
	//�v���C�K�C�h����{�^���ƃ}�E�X�J�[�\��������Ă邩����
	bool Is_Cursor_close();
	//�v���C�K�C�h�̃y�[�W�߂���{�^���ƃ}�E�X�J�[�\��������Ă邩����
	bool Is_Cursor_LeftArrwo();
	bool Is_Cursor_RightArrow();
};