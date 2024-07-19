#include "../../dxlib_ext/dxlib_ext.h"
#include "GameManager.h"
#include "ResourceManager.h"

GameManager::GameManager(SceneBace* startscene) : nowscene_(startscene){
	trans_garph_hdl_ = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("Trans_Graph");
}

GameManager* GameManager::GetInstance_GameManager(SceneBace* startscene) {
	static GameManager* instance = nullptr;
	if (!instance) {
		instance = new GameManager(startscene);
	}
	return instance;
}

void GameManager::Destroy() {
	delete GetInstance_GameManager();
}

void GameManager::Update(float delta_time) {
	//nowscene_に入っているシーンのUpdateとDrawを実行
	if (nowscene_) {
		nowscene_->Update(delta_time);
		nowscene_->Draw(delta_time);
	}
	//シーケンス実行
	sequence_.update(delta_time);
}

void GameManager::ChangeScene(SceneBace* nextscene, float trans_time) {
	nextscene_ = nextscene;
	trans_time_ = trans_time;
	sequence_.change(&GameManager::seqTransOut);
}

bool GameManager::seqTransIn(const float delta_time) {
	int alpha = static_cast<int>(alpha_max_) - static_cast<int>((sequence_.getProgressTime() / trans_time_ * alpha_max_));
	if (alpha <= 0) {
		//シーン切り替え
		sequence_.change(&GameManager::seqRunScene);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, trans_garph_hdl_, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, static_cast<int>(alpha_max_));
	return true;
}

bool GameManager::seqTransOut(const float delta_time) {
	int alpha = static_cast<int>((sequence_.getProgressTime() / trans_time_ * alpha_max_));
	if (alpha >= static_cast<int>(alpha_max_)) {
		//ここでシーンの切り替え
		sequence_.change(&GameManager::seqTransIn);
		delete nowscene_;
		nowscene_ = nullptr;
		nowscene_ = nextscene_;
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, trans_garph_hdl_, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, static_cast<int>(alpha_max_));
	return true;
}

bool GameManager::seqRunScene(const float delta_time) {
	return true;
}
