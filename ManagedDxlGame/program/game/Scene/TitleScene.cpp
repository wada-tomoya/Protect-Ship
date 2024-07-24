#include "../Manager/ResourceManager.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "../Manager/UIManager.h"

TitleScene::TitleScene(const FINALCLASS_NAME& classname) : SceneBace(classname) {

	//ui�C���X�^���X
	ui_ = std::make_shared<UIManager>();

	//�w�i�ǂݍ���
	background_hdl = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("Title_BackGround");
	//bgm�ǂݍ���
	bgm_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("TitleScene_BGM");
	click_se_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("Decision_SE");
	//bgm�Đ�
	PlaySoundMem(bgm_hdl_, DX_PLAYTYPE_LOOP);

	//ui��񏉊���
	ui_->UI_init_TitleScene();

	//�}�E�X�摜�ǂݍ���
	mouse_graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("Mouse_Title");

	tnl::DebugTrace("%d", scenename_);
}

TitleScene::~TitleScene() {
	DeleteSoundMem(bgm_hdl_);
	DeleteSoundMem(click_se_);
}

void TitleScene::Update(const float& delta_time) {
	//�^�C�g���V�[��ui���s
	ui_->UI_Update_TitleScene(delta_time);

	//�I��������Փx�̃v���C�V�[���Ɉړ�
	//easy�Ɉړ�
	if (ui_->Getter_is_game_level("easy")) {
		scenechange_time_ -= delta_time;
		if (scenechange_time_ <= 0.0f) {
			//bgm��~
			StopSoundMem(bgm_hdl_);

			//�V�[���ړ�
			if (!is_scene_change_) {
				GameManager* mgr = GameManager::GetInstance_GameManager();
				mgr->ChangeScene(new (PlayScene)(FINALCLASS_NAME::play_easy));

				is_scene_change_ = true;
			}
		}
	}
	//normal�Ɉړ�
	if (ui_->Getter_is_game_level("normal")) {
		scenechange_time_ -= delta_time;
		if (scenechange_time_ <= 0.0f) {
			//bgm��~
			StopSoundMem(bgm_hdl_);

			//�V�[���ړ�
			if (!is_scene_change_) {
				GameManager* mgr = GameManager::GetInstance_GameManager();
				mgr->ChangeScene(new (PlayScene)(FINALCLASS_NAME::play_normal));

				is_scene_change_ = true;
			}
		}
	}
	//hard�Ɉړ�
	if (ui_->Getter_is_game_level("hard")) {
		scenechange_time_ -= delta_time;
		if (scenechange_time_ <= 0.0f) {
			//bgm��~
			StopSoundMem(bgm_hdl_);

			//�V�[���ړ�
			if (!is_scene_change_) {
				GameManager* mgr = GameManager::GetInstance_GameManager();
				mgr->ChangeScene(new (PlayScene)(FINALCLASS_NAME::play_hard));

				is_scene_change_ = true;
			}
		}
	}
}

void TitleScene::Draw(const float& delta_time) {
	//�w�i�\��
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, background_hdl, false);

	//�^�C�g���\��
	int orifontsize = GetFontSize();
	SetFontSize(fontsize_title_);
	DrawStringEx(title_pos_.x, title_pos_.y, -1, "%s", title_name_.c_str());
	//���������ɂ���
	Centered(title_name_, title_pos_.x);

	SetFontSize(orifontsize);

	//ui�\��
	ui_->Draw_TitleUI();

	//�}�E�X�`��
	MouseDraw(false);
}

void TitleScene::Centered(const std::string& str, int& x_pos) {
	str_len_ = static_cast<int>(strlen(str.c_str()));
	str_wid_ = GetDrawStringWidth(str.c_str(), str_len_);
	x_pos = static_cast<float>((DXE_WINDOW_WIDTH / 2) - (str_wid_ / 2));
}
