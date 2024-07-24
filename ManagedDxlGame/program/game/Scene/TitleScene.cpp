#include "../Manager/ResourceManager.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "../Manager/UIManager.h"

TitleScene::TitleScene(const FINALCLASS_NAME& classname) : SceneBace(classname) {

	//uiインスタンス
	ui_ = std::make_shared<UIManager>();

	//背景読み込み
	background_hdl = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("Title_BackGround");
	//bgm読み込み
	bgm_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("TitleScene_BGM");
	click_se_ = ResourceManager::GetInstance_ResourceManager()->LoadSound_("Decision_SE");
	//bgm再生
	PlaySoundMem(bgm_hdl_, DX_PLAYTYPE_LOOP);

	//ui情報初期化
	ui_->UI_init_TitleScene();

	//マウス画像読み込み
	mouse_graph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("Mouse_Title");

	tnl::DebugTrace("%d", scenename_);
}

TitleScene::~TitleScene() {
	DeleteSoundMem(bgm_hdl_);
	DeleteSoundMem(click_se_);
}

void TitleScene::Update(const float& delta_time) {
	//タイトルシーンui実行
	ui_->UI_Update_TitleScene(delta_time);

	//選択した難易度のプレイシーンに移動
	//easyに移動
	if (ui_->Getter_is_game_level("easy")) {
		scenechange_time_ -= delta_time;
		if (scenechange_time_ <= 0.0f) {
			//bgm停止
			StopSoundMem(bgm_hdl_);

			//シーン移動
			if (!is_scene_change_) {
				GameManager* mgr = GameManager::GetInstance_GameManager();
				mgr->ChangeScene(new (PlayScene)(FINALCLASS_NAME::play_easy));

				is_scene_change_ = true;
			}
		}
	}
	//normalに移動
	if (ui_->Getter_is_game_level("normal")) {
		scenechange_time_ -= delta_time;
		if (scenechange_time_ <= 0.0f) {
			//bgm停止
			StopSoundMem(bgm_hdl_);

			//シーン移動
			if (!is_scene_change_) {
				GameManager* mgr = GameManager::GetInstance_GameManager();
				mgr->ChangeScene(new (PlayScene)(FINALCLASS_NAME::play_normal));

				is_scene_change_ = true;
			}
		}
	}
	//hardに移動
	if (ui_->Getter_is_game_level("hard")) {
		scenechange_time_ -= delta_time;
		if (scenechange_time_ <= 0.0f) {
			//bgm停止
			StopSoundMem(bgm_hdl_);

			//シーン移動
			if (!is_scene_change_) {
				GameManager* mgr = GameManager::GetInstance_GameManager();
				mgr->ChangeScene(new (PlayScene)(FINALCLASS_NAME::play_hard));

				is_scene_change_ = true;
			}
		}
	}
}

void TitleScene::Draw(const float& delta_time) {
	//背景表示
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, background_hdl, false);

	//タイトル表示
	int orifontsize = GetFontSize();
	SetFontSize(fontsize_title_);
	DrawStringEx(title_pos_.x, title_pos_.y, -1, "%s", title_name_.c_str());
	//中央揃えにする
	Centered(title_name_, title_pos_.x);

	SetFontSize(orifontsize);

	//ui表示
	ui_->Draw_TitleUI();

	//マウス描画
	MouseDraw(false);
}

void TitleScene::Centered(const std::string& str, int& x_pos) {
	str_len_ = static_cast<int>(strlen(str.c_str()));
	str_wid_ = GetDrawStringWidth(str.c_str(), str_len_);
	x_pos = static_cast<float>((DXE_WINDOW_WIDTH / 2) - (str_wid_ / 2));
}
