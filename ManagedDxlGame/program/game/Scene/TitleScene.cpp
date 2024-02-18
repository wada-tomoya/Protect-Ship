#include "TitleScene.h"

TitleScene::TitleScene() {
	background_hdl = ResourceManager::GetInstance_ResourceManager()->LoadGraph_("Title_BackGround");

}

void TitleScene::Update(float delta_time) {
	sequence_.update(delta_time);
}

void TitleScene::Draw(float delta_time) {
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, background_hdl, false);
}

bool TitleScene::SeqIdle(float delta_time) {
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		GameManager* mgr = GameManager::GetInstance_GameManager();
		mgr->ChangeScene(new (PlayScene));
	}
	return true;
}
