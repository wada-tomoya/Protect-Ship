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
	//hp�o�[���[����̋���
	const int leftend_ = 180;
	//hp�o�[�E�[����̋���
	const int rightend_ = DXE_WINDOW_WIDTH - 30;
	//hp�o�[�̒���
	const int barlength_ = rightend_ - leftend_;
	//hp�o�[�̍���
	const int barheight_ = 30;
	//��������̍��W
	const tnl::Vector2i upleft_pos_{ leftend_,50 };
	//�����E���̍��W
	const tnl::Vector2i lowright_pos_{ rightend_,static_cast<float>(upleft_pos_.y + barheight_) };
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

	//hp20���ȉ��ł̃X�N���[���G�t�F�N�g
	int screeneffect_hdl_ = 0;
	//�_�ŗpalpha�l
	float screeneffect_alpha_ = 0.0f;
	//�_�łɂ����鎞��
	float effecttime50_ = 1.5f, effecttime20_ = 0.8f;
	float screeneffect_time_ = effecttime50_;
	//hp�o�[�������Ƃ̐F�A5���F���F�@2���F��
	const float hpbar_yellow_ = 0.5f, hpbar_red_ = 0.2f;
	//���l��max
	const float alpha_max_ = 255.0f;

	//�_�Ő؂�ւ�
	bool blink_change_ = true;
	float blink_count_ = 0.0f;

	//�D���U�����󂯂�����hpbar�̃u���l
	static const int blur_num_ = 4;
	const tnl::Vector2i hpbar_blur_[blur_num_] = { {5,5},{3,-2},{-2,3},{-3,-3} };
	tnl::Vector2i hpbar_offset_ = { 0,0 };
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
	float gametime_ = 0.0f;
	//�������Ԃ̍��W
	tnl::Vector2i gametime_pos_{ leftend_,10 };
	const int fontsize_timer_ = 30;

	enum class ENDTYPE {
		gameover = 1,
		gameclear = 2,
	};

	//�Q�[���I�����̉摜
	int gameend_graph_hdl_ = 0;
	//�Q�[���I�[�o�[�̉摜
	int gameover_graph_hdl_ = 0;
	//�Q�[���N���A�̉摜
	int gameclear_graph_hdl_ = 0;
	//�摜���ł�܂ł̎���
	float trans_time_ = 0.5f;

	//�v���C���[�������Ă�A�C�e���̃��X�g
	std::vector<ITEMTYPE> playeritem_list_;
	//�摜�n���h��
	int reditem_hdl_ = 0, blueitem_hdl_ = 0, grerenitem_hdl_ = 0, noneitem_hdl_ = 0;
	//�摜�T�C�Y
	const int itemdraw_size_ = 60;
	//�\���ő��
	static const int itemdraw_max_ = 5;
	//�\�����W
	tnl::Vector2i itemdraw_pos_[itemdraw_max_];

	//���e�̃X�g�b�N��
	int bombstock_ = 0;
	//�\�����W
	tnl::Vector2i bombstock_pos_ = { 0,0 };
	//�X�g�b�N���̃t�H���g�T�C�Y
	const int fontsize_bombstock_ = 50;
	const std::string bombstock_name_ = "���j�U���X�g�b�N";
	int bombstock_str_len_ = 0, bombstock_str_wid_ = 0;

	//hp�o�[�Ə����A�C�e���̊�
	const int ui_interval_ = 10;

	struct BUTTON {
		//�摜�n���h��
		int graph_hdl_ = 0;
		//���W
		tnl::Vector2i pos_{ 0,0 };
		//��{�T�C�Y�o�Ȃ��ꍇ�̃{�^���T�C�Y
		tnl::Vector2i size_{ 0,0 };

		//�}�E�X�����������se�Đ��t���O
		bool is_se_buttonchoice_ = false;

		//�摜�ƃ}�E�X���d�Ȃ������̊g�嗦
		const float graph_overlapext_ = 2.0f;
		//�ʏ펞�̉摜�g�嗦
		const float graph_nomalext_ = 1.0f;
		//�摜�\���̊g�嗦
		float graph_ext_ = graph_nomalext_;
	};
	//�{�^���錾
	BUTTON arrow_left_, arrow_right_, close_, gameguid_draw_, gameminend_draw_, gamemidend_no_, gamemidend_yes_,
		return_, game_start_, game_easy_, game_normal_, game_hard_;
	//�z��ɑ}��
	BUTTON button_[static_cast<int>(BUTTONNAME::max)]{ arrow_left_, arrow_right_, close_, gameguid_draw_, gameminend_draw_, gamemidend_no_, gamemidend_yes_,
		return_, game_start_, game_easy_, game_normal_, game_hard_ };

	//�{�^����{�T�C�Y
	tnl::Vector2i button_normal_size_{ 300,50 }, button_mini_size_{ 200,50 };
	//�^�C�g���ł̖߂�{�^�����W
	tnl::Vector2i title_button_return_{ DXE_WINDOW_WIDTH / 2, 500, };
	//�^�C�g���̃{�^��y����W
	const int title_butotn_pos_y_ = 400;
	//�}�E�X�ƃ{�^�������������se
	int se_buttonchoice_ = 0;
	//�{�^�����N���b�N��������se
	int se_buttonclick_ = 0;
	//�{�^���̏c���W��
	const int button_heispace_ = 100;
	//�{�^���̉����W��
	const int button_widspace_ = 20;
	//�^�C�g���ł̃K�C�h�\���{�^���̍��W
	tnl::Vector2i guid_pos_title_{ (DXE_WINDOW_WIDTH / 2), title_butotn_pos_y_ + (button_heispace_ / 2) };
	//�K�C�h�̉摜�n���h��
	int playguid_page1_hdl_ = 0, playguid_page2_hdl_ = 0;
	//�\������v���C�K�C�h
	int draw_playguid_ = 0;
	//�K�C�h�摜�T�C�Y
	tnl::Vector2i playguid_size_{ 960,540 };
	//�K�C�h�摜���W
	tnl::Vector2i playguid_pos_{ (DXE_WINDOW_WIDTH / 2),(DXE_WINDOW_HEIGHT / 2) };

	//���j���[��ʔw�i�摜�n���h��
	int menu_background_ = 0;

	//�Q�[���r���I���{�^���摜�n���h��
	int game_midend_conf_hdl_ = 0;
	//�Q�[���r���I���m�F�摜�T�C�Y�A���W
	tnl::Vector2i game_midend_conf_size_{ 600,300 };
	tnl::Vector2i game_midend_conf_pos_{ (DXE_WINDOW_WIDTH / 2), (DXE_WINDOW_HEIGHT / 2) };

	//�^�C�g��UI�\���V�[�P���X
	tnl::Sequence<UIManager> title_sequence_ = tnl::Sequence<UIManager>(this, &UIManager::seq_title);
	//�^�C�g��
	bool seq_title(float delta_time);
	//�K�C�h
	bool seq_title_guid(float delta_time);
	//�Q�[���X�^�[�g
	bool seq_title_start(float delta_time);

	//���j���[��ʃV�[�P���X
	tnl::Sequence<UIManager> menu_sequence_ = tnl::Sequence<UIManager>(this, &UIManager::seq_playscene_menu);
	//���j���[
	bool seq_playscene_menu(float delta_time);
	//�Q�[���r���I��
	bool seq_playscene_midend(float delta_time);
	//�K�C�h
	bool seq_playscene_guid(float delta_time);

	//���j���[��ʃt���O
	bool is_menu_ = false;
	//�Q�[���r���I���t���O
	bool is_gamemidend_ = false;

	//�e��Փx�̃Q�[���Ɉړ��t���O
	bool is_game_easy_ = false, is_game_normal_ = false, is_game_hard_ = false;

public:
	UIManager();
	~UIManager();

	//�^�C�g���V�[��UI
	void UI_init_TitleScene();
	void UI_Update_TitleScene(float delta_tiem);

	//�v���C�V�[����UI
	void UI_init_PlayScene(float protectobj_hp, const std::vector<ITEMTYPE>& playeritem_list);
	void UI_Update_PlayScene(float delta_time, const float& protectobj_hp);

	//hp�o�[�\��
	void Draw_hpbar();
	//hp���o�[�h�炷
	void Hpbar_blur(float delta_time, const float& protectobj_hp);

	//�D�̗͒ቺ���̃X�N���[���G�t�F�N�g�\��
	void Draw_ScreenEffect();
	//�摜�_��
	float GraphBlink(float delta_time, float blink_time);

	//�������ԕ\��
	void Draw_timer(const float& gametime);

	//�Q�[���I���\��
	void Draw_gameend(int gameend_type);

	//�v���C�K�C�h�\��
	void Draw_PlayGuid();
	//�v���C�K�C�h�X�V
	void Update_PlayGuid();

	//�^�C�g����ʃ{�^���\��
	void Draw_TitleUI();
	//�Q�[�����x���I���{�^���\��
	void Draw_GameLevel();

	//�e�{�^���\��
	void Draw_Button(int buttonname);

	//�v���C���[�̏����A�C�e���\��
	void Draw_PlayerItem(const std::vector<ITEMTYPE>& playeritem_list);

	//���e�̃X�g�b�N�\��
	void Draw_Bombstock(const int& bombstock);

	//���j���[��ʍX�V
	void Update_PlayMenu(float delta_time);
	//���j���[��ʕ\��
	void Draw_PlayMenu();
	//�r���Q�[���I���m�F�\��
	void Draw_MidEndConf();
	//�Q�[���K�C�h�\���{�^���\��
	void Draw_PlayGuid_Button(tnl::Vector2i pos);

	//�e�{�^���ƃ}�E�X�J�[�\��������Ă��邩����
	bool IsCursor_Button(int buttonname);

	//���j���[��ʏI���t���O
	bool Getter_is_menu_()const { return is_menu_; };
	//�Q�[���r���t���O�Q�b�^�[
	bool Getter_is_amemidend_()const { return is_gamemidend_; };
	//�Q�[���̓�Փx�t���O�Q�b�^�[
	bool Getter_is_game_level(std::string levelname)const {
		if (levelname == "easy") { return is_game_easy_; }
		else if (levelname == "normal") { return is_game_normal_; }
		else if (levelname == "hard") { return is_game_hard_; }
	}
};