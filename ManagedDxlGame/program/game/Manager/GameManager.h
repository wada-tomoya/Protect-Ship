#pragma once
#include "../Scene/SceneBace.h"

class GameManager {
private:
	SceneBace* nowscene_ = nullptr;

	GameManager(SceneBace* startscene);
public:
	
	static GameManager* GetInstance_GameManager(SceneBace* startscene = nullptr);
	void Update(float delta_time);
};
