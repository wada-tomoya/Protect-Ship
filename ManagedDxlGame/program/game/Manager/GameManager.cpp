#include "../../dxlib_ext/dxlib_ext.h"
#include "GameManager.h"

GameManager::GameManager(SceneBace* startscene) : nowscene_(startscene){
	
}

GameManager* GameManager::GetInstance_GameManager(SceneBace* startscene) {
	static GameManager* instance = nullptr;
	if (!instance) {
		instance = new GameManager(startscene);
	}
	return instance;
}

void GameManager::Update(float delta_time) {
	if (nowscene_) {
		nowscene_->Update(delta_time);
		nowscene_->Draw(delta_time);
	}
}